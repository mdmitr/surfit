
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
 *	See COPYING file for copying and redistribution conditions.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; version 2 of the License.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	Contact info: surfit.sourceforge.net
 *----------------------------------------------------------------------------*/

#include "surfit_ie.h"

#include "fileio.h"
#include "datafile.h"
#include "vec.h"
#include "read_txt.h"

#include "cntr.h"
#include "cntr_internal.h"

namespace surfit {

d_cntr * _cntr_read(const char * filename, const char * cntrname,
		    int col1, int col2, int col3, int skip_lines,
		    int grow_by, const char * mask) 
{
	vec * vcol1;
	vec * vcol2;
	vec * vcol3;

	if (cntrname)
		writelog(LOG_MESSAGE,"reading contour \"%s\" from file %s", cntrname, filename);
	else 
		writelog(LOG_MESSAGE,"reading contour from file %s", filename);

	if (!three_columns_read(filename, col1, col2, col3, skip_lines, mask, grow_by,
		vcol1, vcol2, vcol3))
		return NULL;

	d_cntr * res = create_cntr(vcol1, vcol2, vcol3, cntrname);

	return res;
};

bool _cntr_write(const d_cntr * cntrline, const char * filename, const char * mask) {
	if (!cntrline)
		return false;
	return three_columns_write(filename, mask,
		                   cntrline->X, cntrline->Y, cntrline->Z);
};

bool _cntr_save(const d_cntr * contour, const char * filename) {
	if (!contour) {
		writelog(LOG_WARNING, "NULL pointer to cntr.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition())
		return false;

	bool res = _cntr_save_df(contour, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _cntr_save_df(const d_cntr * contour, datafile * df) {

	if (!contour->getName())
		writelog(LOG_MESSAGE,"saving cntr to file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"saving cntr \"%s\" to file %s", contour->getName(), df->get_filename());
	
	
	if (contour->size() == 0) {
		writelog(LOG_WARNING,"Empty contour");
		return false;
	}

	bool res = true;
	bool op;

	op = df->writeTag("cntr");				res = (op && res);
	if (contour->getName()) {
		op = df->writeString("name",contour->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", contour->X); res = (op && res);
	op = df->writeRealArray("y", contour->Y); res = (op && res);
	op = df->writeRealArray("z", contour->Z); res = (op && res);
	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

d_cntr * _cntr_load_df(datafile * df, const char * cntrname) {

	if (!cntrname)
		writelog(LOG_MESSAGE,"loading cntr from file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"loading cntr \"%s\" from file %s", cntrname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "cntr_load : wrong datafile format";

	d_cntr * cntrline = create_cntr(NULL, NULL, NULL);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("cntr")) {
			
			df->skipTagName();
			
			vec * X = NULL;
			vec * Y = NULL;
			vec * Z = NULL;
			
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord("array") ) {
					// read array type
					if (!df->readWord()) goto exit;
					
					if ( df->isWord(REAL_NAME) ) {
						
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("x") ) {
							if ( !df->readRealArray(X) ) goto exit;
							cntrline->X = X;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y) ) goto exit;
							cntrline->Y = Y;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z) ) goto exit;
							cntrline->Z = Z;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( !df->skipRealArray() ) goto exit;
						if ( !df->readWord() ) goto exit;		
						continue;
					}
					
					if ( !df->skipArray(false) ) goto exit;
				}
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						cntrline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(cntrline->X != NULL) &&
				(cntrline->Y != NULL) &&
				(cntrline->Z != NULL) &&
				((cntrline->X->size()) == (cntrline->Y->size())) &&
				((cntrline->X->size()) == (cntrline->Z->size()))
		           ) 
			{
				if (!cntrname) {
					return cntrline;
				} else {
					if (cntrline->getName()) {
						if ( strcmp(cntrline->getName(),cntrname) == 0 ) {
							return cntrline;
						} else {
							if (cntrline)
								cntrline->release();
							cntrline = create_cntr(NULL, NULL, NULL);
						}
					}
				}
			}
		} else {
			if (!cntrname)
				writelog(LOG_ERROR, "cntr_load : this file have no cntrs");
			else
				writelog(LOG_ERROR, "cntr_load : this file have no cntr with name %s", cntrname);
			if (cntrline)
				cntrline->release();
			return NULL;
		}
	};

exit:
	if (cntrline)
		cntrline->release(); 
	writelog(LOG_ERROR, error);
	return NULL;

};

d_cntr * _cntr_load(const char * filename, const char * cntrname) {

	datafile * df = new datafile(filename, DF_MODE_READ);
	
	d_cntr * cntrline = _cntr_load_df(df, cntrname);

	if (!cntrline)
		goto exit;

	delete df;
	return cntrline;
	
exit:
	if (cntrline)
		cntrline->release(); 
	delete df;
	return NULL;

};

void _cntr_info(const d_cntr * cntrline) {
	if (!cntrline) {
		writelog(LOG_WARNING, "_cntr_info : NULL pointer given");
		return;
	}
	writelog(LOG_MESSAGE,"cntr (%s)",cntrline->getName());
};

void _add_surfit_cntrs(d_cntr * contour) {
	if (!contour)
		return;
	surfit_cntrs->push_back(contour);
};

vec * _vec_smooth(const vec * data, const vec * mask, bool closed)
{
	bool interp_scheme = true; // leave source points unmodified
	size_t mask_size = mask->size();
	size_t mask_half = mask_size/2;
	size_t size = data->size();
	if (size < mask_size)
		return create_vec(*data);
	
	size_t res_size = size*2-1;
	if (closed == true)
		res_size--;

	//
	// Doubling vector
	//
	vec * res = create_vec(res_size, 0, false);
	size_t i;
	for (i = 0; i < res_size; i+=2) 
		(*res)(i) = (*data)(i/2);

	for (i = 1; i < res_size; i+=2) {
		if (closed && (i+1 > res_size-1))
			(*res)(i) = ((*res)(i-1) + (*res)(0))/REAL(2);
		else
			(*res)(i) = ((*res)(i-1) + (*res)(i+1))/REAL(2);
	}

	//
	//
	//  convolve res with mask
	//
	//

	size_t j;
	
	vec * buf = create_vec(mask_size, 0, 0);
	vec * res2 = create_vec(*res);
	
	for (i = 0; i < res_size; i++)
	{
		if (interp_scheme) // leave source points unmodified
		{
			if (i % 2 == 0)
				continue;
		}

		for (j = 0; j < mask_size; j++) 
		{
			// find element for convolving
			size_t pos = i+j-mask_half;
			if (closed == false)
			{
				if (i+j < mask_half)
					pos = 0;
				pos = MIN(res_size-1,pos);
			} else {
				if (i+j < mask_half) {
					pos = res_size+i+j-mask_half;
				}
				while (pos > res_size-1)
					pos -= res_size;
			}

			(*buf)(j) = (*res)( pos );
		}
		
		REAL val = 0;
		for (j = 0; j < mask_size; j++) 
			val += (*buf)(j)*(*mask)(j);

		(*res2)(i) = val;
	}

	if (closed) {
		REAL val = (*res2)(0);
		res2->push_back( val );
	}

	buf->release();
	res->release();
	return res2;
};

bool _cntr_smooth(d_cntr * contour)
{
	vec * X = contour->X, * Y = contour->Y, * Z = contour->Z;
	vec * newX = NULL, * newY = NULL, * newZ = NULL;

	vec * mask = create_vec();
	
	// this is DLG mask!
	mask->push_back(-2);
	mask->push_back( 5);
	mask->push_back(10);
	mask->push_back( 5);
	mask->push_back(-2);
	

	REAL mask_sum = 0;
	size_t i;
	for (i = 0; i < mask->size(); i++)
		mask_sum += (*mask)(i);
	for (i = 0; i < mask->size(); i++)
		(*mask)(i) /= mask_sum;


	bool closed = contour->is_closed();

	newX =_vec_smooth(X, mask, closed);
	if (newX == NULL)
		goto failed;

	newY =_vec_smooth(Y, mask, closed);
	if (newY == NULL)
		goto failed;

	newZ =_vec_smooth(Z, mask, closed);
	if (newZ == NULL)
		goto failed;

	contour->X->release();
	contour->Y->release();
	contour->Z->release();

	contour->X = newX;
	contour->Y = newY;
	contour->Z = newZ;

	mask->release();

	REAL minx, maxx, miny, maxy;
	contour->bounds(minx, maxx, miny, maxy);

	return true;

failed:

	if (X)
		X->release();
	if (Y)
		Y->release();
	if (Z)
		Z->release();

	if (newX)
		newX->release();
	if (newY)
		newY->release();
	if (newZ)
		newZ->release();

	mask->release();

	return false;
};

}; // namespace surfit;



/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "ie.h"
#include "cntr.h"
#include "cntr_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "wcntr.h"

#include "cntr_user.h"

namespace surfit {

bool _cntr_check() {
	if (surfit_cntr)
		return true;
	return false;
};

bool _cntr_unload() {
	if (!_cntr_check())
		return false;
	delete surfit_cntr;
	surfit_cntr = NULL;
	return true;
};

cntr * _cntr_read(const char * filename, const char * cntrname,
		  int columns, 
		  int col1, int col2, int col3, 
		  int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;
	REAL * col3_begin, * col3_end;

	if (cntrname)
		writelog(SURFIT_MESSAGE,"reading contour \"%s\" from file %s", cntrname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading contour from file %s", filename);

	if (!three_columns_read(filename, columns, col1, col2, col3, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end,
		col3_begin, col3_end))
		return NULL;

	cntr * res = new cntr(col1_begin, col1_end,
		                  col2_begin, col2_end,
						  col3_begin, col3_end,
                          cntrname);

	return res;
};

bool _cntr_write(cntr * cntrline, const char * filename, const char * mask) {
	if (!cntrline)
		return false;
	return three_columns_write(filename, mask,
		                   cntrline->X_begin, cntrline->X_end,
		                   cntrline->Y_begin, cntrline->Y_end,
				   cntrline->Z_begin, cntrline->Z_end);
};

bool _cntr_save(cntr * contour, const char * filename, int mode) {
	if (!contour) {
		writelog(SURFIT_WARNING, "NULL pointer to cntr.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _cntr_save_df(contour, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _cntr_save_df(cntr * contour, datafile * df) {

	if (!contour->getName())
		writelog(SURFIT_MESSAGE,"saving cntr to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving cntr \"%s\" to file %s", contour->getName(), df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("cntr");				res = (op && res);
	if (contour->getName()) {
		op = df->writeString("name",contour->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", contour->X_begin, contour->size()); res = (op && res);
	op = df->writeRealArray("y", contour->Y_begin, contour->size()); res = (op && res);
	op = df->writeRealArray("z", contour->Z_begin, contour->size()); res = (op && res);
	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

cntr * _cntr_load_df(datafile * df, const char * cntrname) {

	if (!cntrname)
		writelog(SURFIT_MESSAGE,"loading cntr from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading cntr \"%s\" from file %s", cntrname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "cntr_load : wrong datafile format";

	cntr * cntrline = new cntr(NULL, NULL, NULL, NULL, NULL, NULL);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("cntr")) {
			
			df->skipTagName();
			
			REAL * X_begin = NULL;
			REAL * X_end   = NULL;
			REAL * Y_begin = NULL;
			REAL * Y_end   = NULL;
			REAL * Z_begin = NULL;
			REAL * Z_end   = NULL;
            
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord("array") ) {
					// read array type
					if (!df->readWord()) goto exit;
					
					if ( df->isWord(REAL_NAME) ) {
						
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("x") ) {
							if ( !df->readRealArray(X_begin,X_end) ) goto exit;
							cntrline->X_begin = X_begin;
							cntrline->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							cntrline->Y_begin = Y_begin;
							cntrline->Y_end = Y_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z_begin,Z_end) ) goto exit;
							cntrline->Z_begin = Z_begin;
							cntrline->Z_end = Z_end;
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
				(cntrline->X_begin != NULL) &&
				(cntrline->X_end != NULL) &&
				(cntrline->Y_begin != NULL) &&
				(cntrline->Y_end != NULL) &&
				(cntrline->Z_begin != NULL) &&
				(cntrline->Z_end != NULL) &&
                		((cntrline->X_end - cntrline->X_begin) == (cntrline->Y_end - cntrline->Y_begin)) &&
				((cntrline->X_end - cntrline->X_begin) == (cntrline->Z_end - cntrline->Z_begin))
		           ) 
			{
				if (!cntrname) {
					return cntrline;
				} else {
					if (cntrline->getName()) {
						if ( strcmp(cntrline->getName(),cntrname) == 0 ) {
							return cntrline;
						} else {
							delete cntrline;
							cntrline = new cntr(NULL, NULL, NULL, NULL, NULL, NULL);
						}
					}
				}
			}
		} else {
			if (!cntrname)
				writelog(SURFIT_ERROR, "cntr_load : this file have no cntrs");
			else
				writelog(SURFIT_ERROR, "cntr_load : this file have no cntr with name %s", cntrname);
			delete cntrline;
			return NULL;
		}
	};

exit:
	delete cntrline; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

cntr * _cntr_load(const char * filename, const char * cntrname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode);
	
	cntr * cntrline = _cntr_load_df(df, cntrname);

	if (!cntrline)
		goto exit;

	delete df;
	return cntrline;
	
exit:
	delete cntrline; 
	delete df;
	return NULL;

};

void _cntr_info(cntr * cntrline) {
	if (!cntrline) {
		writelog(SURFIT_WARNING, "_cntr_info : NULL pointer given");
		return;
	}
	if (cntrline->getName()) {
		writelog(SURFIT_MESSAGE,"cntr (%s)",cntrline->getName());
	} else {
		writelog(SURFIT_MESSAGE,"cntr noname");	
	}
};

cntr * _get_surfit_cntr() {
	return surfit_cntr;
};

void _set_surfit_cntr(cntr * contour) {
	delete surfit_cntr;
	surfit_cntr = contour;
};

void _add_surfit_cntrs(cntr * contour) {
	if (!contour)
		return;
	surfit_cntrs->push_back(contour);
};

wcntr * _cntr_to_wcntr(cntr * contour, REAL weight) {
	if (!contour)
		return false;

	writelog(SURFIT_MESSAGE,"_cntr_to_wcntr : converting contour to contour with weight = %lf", weight);

	REAL * X_begin = (REAL*)malloc(contour->size()*sizeof(REAL));
	REAL * X_end = X_begin + contour->size();
	memcpy(X_begin, contour->X_begin, contour->size()*sizeof(REAL));
	
	REAL * Y_begin = (REAL*)malloc(contour->size()*sizeof(REAL));
	REAL * Y_end = Y_begin + contour->size();
	memcpy(Y_begin, contour->Y_begin, contour->size()*sizeof(REAL));

	REAL * Z_begin = (REAL*)malloc(contour->size()*sizeof(REAL));
	REAL * Z_end = Z_begin + contour->size();
	memcpy(Z_begin, contour->Z_begin, contour->size()*sizeof(REAL));
	
	wcntr * wcontour = new wcntr(X_begin, X_end,
		Y_begin, Y_end,
		Z_begin, Z_end,
		weight,
		contour->getName());

	return wcontour;
};

}; // namespace surfit;


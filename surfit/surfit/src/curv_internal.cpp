
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
#include "curv.h"
#include "curv_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"

#include "curv_user.h"

namespace surfit {

bool _curv_check() {
	if (surfit_curv)
		return true;
	return false;
};

bool _curv_unload() {
	if (!_curv_check())
		return false;
	delete surfit_curv;
	surfit_curv = NULL;
	return true;
};

curv * _curv_read(const char * filename, const char * curvname,
		  int columns, 
		  int col1, int col2,
		  int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (curvname)
		writelog(SURFIT_MESSAGE,"reading curve \"%s\" from file %s", curvname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading curve from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
			      col1_begin, col1_end,
			      col2_begin, col2_end))
		return NULL;

	curv * res = new curv(col1_begin, col1_end,
		              col2_begin, col2_end,
			      curvname);

	return res;
};

bool _curv_write(curv * curvline, const char * filename, const char * mask) {
	if (!curvline)
		return false;
	return two_columns_write(filename, mask,
				 curvline->X_begin, curvline->X_end,
				 curvline->Y_begin, curvline->Y_end);
};

bool _curv_save(curv * contour, const char * filename, int mode) {
	if (!contour) {
		writelog(SURFIT_WARNING, "NULL pointer to curv.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _curv_save_df(contour, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _curv_save_df(curv * contour, datafile * df) {

	if (!contour->getName())
		writelog(SURFIT_MESSAGE,"saving curv to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving curv \"%s\" to file %s", contour->getName(), df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("curv");				res = (op && res);
	if (contour->getName()) {
		op = df->writeString("name",contour->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", contour->X_begin, contour->size()); res = (op && res);
	op = df->writeRealArray("y", contour->Y_begin, contour->size()); res = (op && res);
	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

curv * _curv_load_df(datafile * df, const char * curvname) {

	if (!curvname)
		writelog(SURFIT_MESSAGE,"loading curv from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading curv \"%s\" from file %s", curvname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "curv_load : wrong datafile format";

	curv * curvline = new curv(NULL, NULL, NULL, NULL);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("curv")) {
			
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
							curvline->X_begin = X_begin;
							curvline->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							curvline->Y_begin = Y_begin;
							curvline->Y_end = Y_end;
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
						curvline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(curvline->X_begin != NULL) &&
				(curvline->X_end != NULL) &&
				(curvline->Y_begin != NULL) &&
				(curvline->Y_end != NULL) &&
				((curvline->X_end - curvline->X_begin) == (curvline->Y_end - curvline->Y_begin))
			   ) 
			{
				if (!curvname) {
					return curvline;
				} else {
					if (curvline->getName()) {
						if ( strcmp(curvline->getName(),curvname) == 0 ) {
							return curvline;
						} else {
							delete curvline;
							curvline = new curv(NULL, NULL, NULL, NULL);
						}
					}
				}
			}
		} else {
			if (!curvname)
				writelog(SURFIT_ERROR, "curv_load : this file have no curvs");
			else
				writelog(SURFIT_ERROR, "curv_load : this file have no curv with name %s", curvname);
			delete curvline;
			return NULL;
		}
	};

exit:
	delete curvline; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

curv * _curv_load(const char * filename, const char * curvname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode);
	
	curv * curvline = _curv_load_df(df, curvname);

	if (!curvline)
		goto exit;

	delete df;
	return curvline;
	
exit:
	delete curvline; 
	delete df;
	return NULL;

};

void _curv_info(curv * curvline) {
	if (!curvline) {
		writelog(SURFIT_WARNING, "_curv_info : NULL pointer given");
		return;
	}
	if (curvline->getName()) {
		writelog(SURFIT_MESSAGE,"curv (%s)",curvline->getName());
	} else {
		writelog(SURFIT_MESSAGE,"curv noname");	
	}
};

curv * _get_surfit_curv() {
	return surfit_curv;
};

void _set_surfit_curv(curv * contour) {
	delete surfit_curv;
	surfit_curv = contour;
};

void _add_surfit_curvs(curv * contour) {
	if (!contour)
		return;
	surfit_curvs->push_back(contour);
};

}; // namespace surfit;


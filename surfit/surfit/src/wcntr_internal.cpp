
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
#include "wcntr.h"
#include "wcntr_internal.h"
#include "cntr_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"

#include "wcntr_user.h"

namespace surfit {

bool _wcntr_check() {
	if (surfit_wcntr)
		return true;
	return false;
};

bool _wcntr_unload() {
	if (!_wcntr_check())
		return false;
	delete surfit_wcntr;
	surfit_wcntr = NULL;
	return true;
};

wcntr * _wcntr_read(const char * filename, const char * cntrname, REAL weight,
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

	wcntr * res = new wcntr(col1_begin, col1_end,
		                col2_begin, col2_end,
				col3_begin, col3_end,
				weight,
                                cntrname);

	return res;
};

bool _wcntr_save(wcntr * wcontour, const char * filename, int mode) {
	if (!wcontour) {
		writelog(SURFIT_WARNING, "NULL pointer to wcntr.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _wcntr_save_df(wcontour, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _wcntr_save_df(wcntr * wcontour, datafile * df) {

	if (!wcontour->getName())
		writelog(SURFIT_MESSAGE,"saving wcntr to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving wcntr \"%s\" to file %s", wcontour->getName(), df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("wcntr");				res = (op && res);
	if (wcontour->getName()) {
		op = df->writeString("name",wcontour->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", wcontour->X_begin, wcontour->size()); res = (op && res);
	op = df->writeRealArray("y", wcontour->Y_begin, wcontour->size()); res = (op && res);
	op = df->writeRealArray("z", wcontour->Z_begin, wcontour->size()); res = (op && res);
	op = df->writeReal("weight", wcontour->weight); res = (op && res);
	op = df->writeEndTag();						res = (op && res);
		
	return res;
};

wcntr * _wcntr_load_df(datafile * df, const char * wcntrname) {

	if (!wcntrname)
		writelog(SURFIT_MESSAGE,"loading wcntr from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading wcntr \"%s\" from file %s", wcntrname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "wcntr_load : wrong datafile format";

	wcntr * wcntrline = new wcntr(NULL, NULL, NULL, NULL, NULL, NULL, 0);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("wcntr")) {
			
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
							wcntrline->X_begin = X_begin;
							wcntrline->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							wcntrline->Y_begin = Y_begin;
							wcntrline->Y_end = Y_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z_begin,Z_end) ) goto exit;
							wcntrline->Z_begin = Z_begin;
							wcntrline->Z_end = Z_end;
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
						wcntrline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				if ( df->isWord( REAL_NAME ) ) {
					if (!df->readWord()) goto exit;
					
					if ( df->isWord("weight") ) {
						if ( !df->readReal(wcntrline->weight) ) goto exit;
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(wcntrline->X_begin != NULL) &&
				(wcntrline->X_end != NULL) &&
				(wcntrline->Y_begin != NULL) &&
				(wcntrline->Y_end != NULL) &&
				(wcntrline->Z_begin != NULL) &&
				(wcntrline->Z_end != NULL) &&
        		        ((wcntrline->X_end - wcntrline->X_begin) == (wcntrline->Y_end - wcntrline->Y_begin)) &&
				((wcntrline->X_end - wcntrline->X_begin) == (wcntrline->Z_end - wcntrline->Z_begin))
                	   ) 
			{
				if (!wcntrname) {
					return wcntrline;
				} else {
					if (wcntrline->getName()) {
						if ( strcmp(wcntrline->getName(),wcntrname) == 0 ) {
							return wcntrline;
						} else {
							delete wcntrline;
							wcntrline = new wcntr(NULL, NULL, NULL, NULL, NULL, NULL, 0);
						}
					}
				}
			}
		} else {
			if (!wcntrname)
				writelog(SURFIT_ERROR, "wcntr_load : this file have no wcntrs");
			else
				writelog(SURFIT_ERROR, "wcntr_load : this file have no wcntr with name %s", wcntrname);
			delete wcntrline;
			return NULL;
		}
	};

exit:
	delete wcntrline; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

wcntr * _wcntr_load(const char * filename, const char * cntrname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode);
	
	wcntr * wcntrline = _wcntr_load_df(df, cntrname);

	if (!wcntrline)
		goto exit;

	delete df;
	return wcntrline;
	
exit:
	delete wcntrline; 
	delete df;
	return NULL;

};

void _wcntr_info(wcntr * wcontour) {
	if (!wcontour) {
		writelog(SURFIT_WARNING, "_wcntr_info : NULL pointer given");
		return;
	}
	if (wcontour->getName()) {
		writelog(SURFIT_MESSAGE,"wcntr (%s)",wcontour->getName());
	} else {
		writelog(SURFIT_MESSAGE,"wcntr noname");	
	}
};

wcntr * _get_surfit_wcntr() {
	return surfit_wcntr;
};

void _set_surfit_wcntr(wcntr * contour) {
	delete surfit_wcntr;
	surfit_wcntr = contour;
};

void _add_surfit_wcntrs(wcntr * contour) {
	if (!contour)
		return;
	surfit_wcntrs->push_back(contour);
};

}; // namespace surfit;



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

#include "warea.h"
#include "warea_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "variables_tcl.h"

#include "warea_user.h"

namespace surfit {

bool _warea_check() {
	if (surfit_warea)
		return true;
	return false;
};

bool _warea_unload() {
	if (!_warea_check())
		return false;
	delete surfit_warea;
	surfit_warea = NULL;
	return true;
};

warea * _warea_read(const char * filename, const char * wareaname, REAL value, REAL weight,
		    int columns, int col1, int col2, int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (wareaname)
		writelog(SURFIT_MESSAGE,"reading warea \"%s\" from file %s", wareaname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading warea from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end))
		return NULL;

	warea * res = new warea(col1_begin, col1_end,
		                col2_begin, col2_end,
				value, weight,
				wareaname);

	return res;
};

bool _warea_write(warea * warealine, const char * filename, const char * mask) {
	if (!warealine)
		return false;
	return two_columns_write(filename, mask,
		                 warealine->X_begin, warealine->X_end,
		                 warealine->Y_begin, warealine->Y_end);
};

bool _warea_save(warea * warealine, const char * filename, int mode) {
	if (!warealine) {
		writelog(SURFIT_WARNING, "NULL pointer to warea.");
		return false;
	};
	
	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _warea_save_df(warealine, df);
	bool op;
	op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _warea_save_df(warea * ar, datafile * df) {

	if (!ar->getName())
		writelog(SURFIT_MESSAGE,"saving warea to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving warea \"%s\" to file %s", ar->getName(), df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("warea");				res = (op && res);
	if (ar->getName()) {
		op = df->writeString("name",ar->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", ar->X_begin, ar->size()); res = (op && res);
	op = df->writeRealArray("y", ar->Y_begin, ar->size()); res = (op && res);
	op = df->writeReal("value", ar->value);                res = (op && res);
	op = df->writeReal("weight", ar->weight);                res = (op && res);
	op = df->writeEndTag();						res = (op && res);
	
	return res;

};

warea * _warea_load_df(datafile * df, const char * wareaname) {

	if (!wareaname)
		writelog(SURFIT_MESSAGE,"loading warea from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading warea \"%s\" from file %s", wareaname, df->get_filename());


	if (!df->condition()) {
		return NULL;
	}

	char error[] = "warea_load : wrong datafile format";

	warea * warealine = new warea(NULL, NULL, NULL, NULL, REAL(0), REAL(0));
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("warea")) {
			
			df->skipTagName();
			
			REAL * X_begin = NULL;
			REAL * X_end = NULL;
			REAL * Y_begin = NULL;
			REAL * Y_end = NULL;
			REAL value = REAL(0);
			REAL weight = REAL(0);
            
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord(REAL_NAME) ) {
					// read variable name
					if (!df->readWord()) goto exit;
					if ( df->isWord("value") ) {
						if ( !df->readReal(value) ) goto exit;
						warealine->value = value;
						if ( !df->readWord() ) goto exit;
						continue;
					}
					if ( df->isWord("weight") ) {
						if ( !df->readReal(weight) ) goto exit;
						warealine->weight = weight;
						if ( !df->readWord() ) goto exit;
						continue;
					}
					if ( !df->skipReal(false) ) goto exit;
				}
				if ( df->isWord("array") ) {
					// read array type
					if (!df->readWord()) goto exit;
					
					if ( df->isWord(REAL_NAME) ) {
						
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("x") ) {
							if ( !df->readRealArray(X_begin,X_end) ) goto exit;
							warealine->X_begin = X_begin;
							warealine->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							warealine->Y_begin = Y_begin;
							warealine->Y_end = Y_end;
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
						warealine->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(warealine->X_begin != NULL) &&
				(warealine->X_end != NULL) &&
				(warealine->Y_begin != NULL) &&
				(warealine->Y_end != NULL) &&
                		((warealine->X_end - warealine->X_begin) == (warealine->Y_end - warealine->Y_begin))
		           ) 
			{
				if (!wareaname) {
					return warealine;
				} else {
					if (warealine->getName()) {
						if ( strcmp(warealine->getName(),wareaname) == 0 ) {
							return warealine;
						} else {
							delete warealine;
							warealine = new warea(NULL, NULL, NULL, NULL, REAL(0), REAL(0));
						}
					}
				}
			}
		} else {
			if (!wareaname)
				writelog(SURFIT_ERROR, "warea_load : this file have no wareas");
			else
				writelog(SURFIT_ERROR, "warea_load : this file have no warea with name %s", wareaname);
			delete warealine;
			return NULL;
		}
	};

exit:
	delete warealine; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

warea * _warea_load(const char * filename, const char * wareaname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	warea * warealine = _warea_load_df(df, wareaname);

	if (!warealine)
		goto exit;

	delete df;
	return warealine;

exit:
	delete warealine; 
	delete df;
	return NULL;

};

void _warea_info(warea * warealine) {
	if (!warealine) {
		writelog(SURFIT_WARNING, "_warea_info : NULL pointer given");
		return;
	}
	if (warealine->getName()) {
		if (warealine->value == undef_value)
			writelog(SURFIT_MESSAGE,"warea (%s) : value = \"undef\"",warealine->getName());
		else 
			writelog(SURFIT_MESSAGE,"warea (%s) : value = %g",warealine->getName(), warealine->value);

	} else {
		if (warealine->value == undef_value)
			writelog(SURFIT_MESSAGE,"warea noname : value = \"undef\"");
		else 
			writelog(SURFIT_MESSAGE,"warea noname : value = %g", warealine->value);
	}
};

warea * _get_surfit_warea() {
	return surfit_warea;
};

void _set_surfit_warea(warea * warealine) {
	delete surfit_warea;
	surfit_warea = warealine;
};

void _add_surfit_wareas(warea * warealine) {
	if (!warealine)
		return;
	surfit_wareas->push_back(warealine);
};

}; // namespace surfit;



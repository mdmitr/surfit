
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

#include "area.h"
#include "area_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "variables_tcl.h"

#include "area_user.h"

namespace surfit {

bool _area_check() {
	if (surfit_area)
		return true;
	return false;
};

bool _area_unload() {
	if (!_area_check())
		return false;
	delete surfit_area;
	surfit_area = NULL;
	return true;
};

area * _area_read(const char * filename, const char * areaname, REAL value,
	          int columns, int col1, int col2, int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (areaname)
		writelog(SURFIT_MESSAGE,"reading area \"%s\" from file %s", areaname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading area from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end))
		return NULL;

	area * res = new area(col1_begin, col1_end,
		              col2_begin, col2_end,
			      value,
			      areaname);

	return res;
};

bool _area_write(area * arealine, const char * filename, const char * mask) {
	if (!arealine)
		return false;
	return two_columns_write(filename, mask,
		                 arealine->X_begin, arealine->X_end,
		                 arealine->Y_begin, arealine->Y_end);
};

bool _area_save(area * arealine, const char * filename, int mode) {
	if (!arealine) {
		writelog(SURFIT_WARNING, "NULL pointer to area.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _area_save_df(arealine, df);
	bool op;
	op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _area_save_df(area * ar, datafile * df) {

	if (!ar->getName())
		writelog(SURFIT_MESSAGE,"saving area to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving area \"%s\" to file %s", ar->getName(), df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("area");				res = (op && res);
	if (ar->getName()) {
		op = df->writeString("name",ar->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", ar->X_begin, ar->size()); res = (op && res);
	op = df->writeRealArray("y", ar->Y_begin, ar->size()); res = (op && res);
	op = df->writeReal("value", ar->value);                res = (op && res);
        op = df->writeEndTag();				       res = (op && res);
	
	return res;

};

area * _area_load_df(datafile * df, const char * areaname) {

	if (!areaname)
		writelog(SURFIT_MESSAGE,"loading area from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading area \"%s\" from file %s", areaname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "area_load : wrong datafile format";

	area * arealine = new area(NULL, NULL, NULL, NULL, REAL(0));
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("area")) {
			
			df->skipTagName();
			
			REAL * X_begin = NULL;
			REAL * X_end = NULL;
			REAL * Y_begin = NULL;
			REAL * Y_end = NULL;
			REAL value = REAL(0);
            
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord(REAL_NAME) ) {
					// read variable name
					if (!df->readWord()) goto exit;
					if ( df->isWord("value") ) {
						if ( !df->readReal(value) ) goto exit;
						arealine->value = value;
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
							arealine->X_begin = X_begin;
							arealine->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							arealine->Y_begin = Y_begin;
							arealine->Y_end = Y_end;
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
						arealine->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(arealine->X_begin != NULL) &&
				(arealine->X_end != NULL) &&
				(arealine->Y_begin != NULL) &&
				(arealine->Y_end != NULL) &&
		                ((arealine->X_end - arealine->X_begin) == (arealine->Y_end - arealine->Y_begin))
                	   ) 
			{
				if (!areaname) {
					return arealine;
				} else {
					if (arealine->getName()) {
						if ( strcmp(arealine->getName(),areaname) == 0 ) {
							return arealine;
						} else {
							delete arealine;
							arealine = new area(NULL, NULL, NULL, NULL, REAL(0));
						}
					}
				}
			}
		} else {
			if (!areaname)
				writelog(SURFIT_ERROR, "area_load : this file have no areas");
			else
				writelog(SURFIT_ERROR, "area_load : this file have no area with name %s", areaname);
			delete arealine;
			return NULL;
		}
	};

exit:
	delete arealine; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

area * _area_load(const char * filename, const char * areaname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	area * arealine = _area_load_df(df, areaname);

	if (!arealine)
		goto exit;

	delete df;
	return arealine;

exit:
	delete arealine; 
	delete df;
	return NULL;

};

void _area_info(area * arealine) {
	if (!arealine) {
		writelog(SURFIT_WARNING, "_area_info : NULL pointer given");
		return;
	}
	if (arealine->getName()) {
		if (arealine->value == undef_value)
			writelog(SURFIT_MESSAGE,"area (%s) : value = \"undef\"",arealine->getName());
		else 
			writelog(SURFIT_MESSAGE,"area (%s) : value = %g",arealine->getName(), arealine->value);

	} else {
		if (arealine->value == undef_value)
			writelog(SURFIT_MESSAGE,"area noname : value = \"undef\"");
		else 
			writelog(SURFIT_MESSAGE,"area noname : value = %g", arealine->value);
	}
};

area * _get_surfit_area() {
	return surfit_area;
};

void _set_surfit_area(area * arealine) {
	delete surfit_area;
	surfit_area = arealine;
};

void _add_surfit_areas(area * arealine) {
	if (!arealine)
		return;
	surfit_areas->push_back(arealine);
};

}; // namespace surfit;



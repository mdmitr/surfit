
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
#include "iso.h"
#include "iso_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "variables_tcl.h"

#include "iso_user.h"

namespace surfit {

bool _iso_check() {
	if (surfit_iso)
		return true;
	return false;
};

bool _iso_unload() {
	if (!_iso_check())
		return false;
	delete surfit_iso;
	surfit_iso = NULL;
	return true;
};

iso * _iso_read(const char * filename, const char * isoname, REAL value,
		int columns, int col1, int col2, int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (isoname)
		writelog(SURFIT_MESSAGE,"reading iso \"%s\" from file %s", isoname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading iso from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
		              col1_begin, col1_end,
			      col2_begin, col2_end))
		return NULL;

	iso * res = new iso(col1_begin, col1_end,
		            col2_begin, col2_end,
			    value,
			    isoname);

	return res;
};

bool _iso_write(iso * isoline, const char * filename, const char * mask) {
	if (!isoline)
		return false;
	return two_columns_write(filename, mask,
		                 isoline->X_begin, isoline->X_end,
		                 isoline->Y_begin, isoline->Y_end);
};

bool _iso_save(iso * isoline, const char * filename, int mode) {
	if (!isoline) {
		writelog(SURFIT_WARNING, "NULL pointer to iso.");
		return false;
	};

	if (!isoline->getName())
		writelog(SURFIT_MESSAGE,"saving iso to file %s", filename);
	else
		writelog(SURFIT_MESSAGE,"saving iso \"%s\" to file %s", isoline->getName(), filename);

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _iso_save_df(isoline, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _iso_save_df(iso * isoline, datafile * df) {

	if (!isoline->getName()) 
		writelog(SURFIT_MESSAGE,"saving iso with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving iso \"%s\" to file %s",isoline->getName(),df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("iso");				res = (op && res);
	if (isoline->getName()) {
		op = df->writeString("name",isoline->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", isoline->X_begin, isoline->size()); res = (op && res);
	op = df->writeRealArray("y", isoline->Y_begin, isoline->size()); res = (op && res);
	op = df->writeReal("value", isoline->value);                 res = (op && res);
	op = df->writeEndTag();						res = (op && res);
		
	return res;
};

iso * _iso_load(const char * filename, const char * isoname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	iso * isoline = _iso_load_df(df, isoname);
	if (!isoline)
		goto exit;

	delete df;
	return isoline;
	
exit:
	delete isoline; 
	delete df;
	return NULL;

};

iso * _iso_load_df(datafile * df, const char * isoname) {

	if (!isoname)
		writelog(SURFIT_MESSAGE,"loading iso from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading iso \"%s\" from file %s", isoname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "iso_load : wrong datafile format";

	iso * isoline = new iso(NULL, NULL, NULL, NULL, REAL(0));
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("iso")) {
			
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
						isoline->value = value;
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
							isoline->X_begin = X_begin;
							isoline->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							isoline->Y_begin = Y_begin;
							isoline->Y_end = Y_end;
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
						isoline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(isoline->X_begin != NULL) &&
				(isoline->X_end != NULL) &&
				(isoline->Y_begin != NULL) &&
				(isoline->Y_end != NULL) &&
        		        ((isoline->X_end - isoline->X_begin) == (isoline->Y_end - isoline->Y_begin))
                	   ) 
			{
				if (!isoname) {
					return isoline;
				} else {
					if (isoline->getName()) {
						if ( strcmp(isoline->getName(),isoname) == 0 ) {
							return isoline;
						} else {
							delete isoline;
							isoline = new iso(NULL, NULL, NULL, NULL, REAL(0));
						}
					}
				}
			}
		} else {
			if (!isoname)
				writelog(SURFIT_ERROR, "iso_load : this file have no iso");
			else
				writelog(SURFIT_ERROR, "iso_load : this file have no iso with name %s", isoname);
			delete isoline;
			return NULL;
		}
	};

exit:
	delete isoline; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

void _iso_info(iso * isoline) {
	if (!isoline) {
		writelog(SURFIT_WARNING, "_iso_info : NULL pointer given");
		return;
	}
	if (isoline->getName()) {
		if (isoline->value == undef_value)
			writelog(SURFIT_MESSAGE,"iso (%s) : value = \"undef\"",isoline->getName());
		else 
			writelog(SURFIT_MESSAGE,"iso (%s) : value = %g",isoline->getName(), isoline->value);

	} else {
		if (isoline->value == undef_value)
			writelog(SURFIT_MESSAGE,"iso noname : value = \"undef\"");
		else 
			writelog(SURFIT_MESSAGE,"iso noname : value = %g", isoline->value);
	}
};

iso * _get_surfit_iso() {
	return surfit_iso;
};

void _set_surfit_iso(iso * isoline) {
	delete surfit_iso;
	surfit_iso = isoline;
};

void _add_surfit_isos(iso * isoline) {
	if (!isoline)
		return;
	surfit_isos->push_back(isoline);
};

}; // namespace surfit;



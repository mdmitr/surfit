
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
#include "wiso.h"
#include "wiso_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "variables_tcl.h"

#include "wiso_user.h"

namespace surfit {

bool _wiso_check() {
	if (surfit_wiso)
		return true;
	return false;
};

bool _wiso_unload() {
	if (!_wiso_check())
		return false;
	delete surfit_wiso;
	surfit_wiso = NULL;
	return true;
};

wiso * _wiso_read(const char * filename, const char * isoname, REAL value, REAL weight,
		  int columns, int col1, int col2, int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (isoname)
		writelog(SURFIT_MESSAGE,"reading wiso \"%s\" from file %s", isoname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading wiso from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end))
		return NULL;

	wiso * res = new wiso(col1_begin, col1_end,
		              col2_begin, col2_end,
			      value, weight,
			      isoname);

	return res;
};

bool _wiso_write(wiso * wisoline, const char * filename, const char * mask) {
	if (!_wiso_check())
		return false;
	return two_columns_write(filename, mask,
		                 wisoline->X_begin, wisoline->X_end,
		                 wisoline->Y_begin, wisoline->Y_end);
};

bool _wiso_save(wiso * wisoline, const char * filename, int mode) {

	if (!wisoline) {
		writelog(SURFIT_WARNING, "NULL pointer to wiso.");
		return false;
	};

	if (!wisoline->getName())
		writelog(SURFIT_MESSAGE,"saving wiso to file %s", filename);
	else
		writelog(SURFIT_MESSAGE,"saving wiso \"%s\" to file %s", wisoline->getName(), filename);

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _wiso_save_df(wisoline, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _wiso_save_df(wiso * wisoline, datafile * df) {

	if (!wisoline->getName()) 
		writelog(SURFIT_MESSAGE,"saving wiso with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving wiso \"%s\" to file %s",wisoline->getName(),df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("wiso");				res = (op && res);
	if (wisoline->getName()) {
		op = df->writeString("name",wisoline->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", wisoline->X_begin, wisoline->size()); res = (op && res);
	op = df->writeRealArray("y", wisoline->Y_begin, wisoline->size()); res = (op && res);
	op = df->writeReal("value", wisoline->value);			   res = (op && res);
	op = df->writeReal("weight", wisoline->weight);                    res = (op && res);
	op = df->writeEndTag();						   res = (op && res);
		
	return res;
};

wiso * _wiso_load(const char * filename, const char * wisoname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	wiso * wisoline = _wiso_load_df(df, wisoname);
	if (!wisoline)
		goto exit;

	delete df;
	return wisoline;
	
exit:
	delete wisoline; 
	delete df;
	return NULL;

};

wiso * _wiso_load_df(datafile * df, const char * isoname) {

	if (!isoname)
		writelog(SURFIT_MESSAGE,"loading wiso from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading wiso \"%s\" from file %s", isoname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "wiso_load : wrong datafile format";

	wiso * wisoline = new wiso(NULL, NULL, NULL, NULL, REAL(0), REAL(0));
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("wiso")) {
			
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
						wisoline->value = value;
						if ( !df->readWord() ) goto exit;
						continue;
					}
					if ( df->isWord("weight") ) {
						if ( !df->readReal(weight) ) goto exit;
						wisoline->weight = weight;
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
							wisoline->X_begin = X_begin;
							wisoline->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							wisoline->Y_begin = Y_begin;
							wisoline->Y_end = Y_end;
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
						wisoline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(wisoline->X_begin != NULL) &&
				(wisoline->X_end != NULL) &&
				(wisoline->Y_begin != NULL) &&
				(wisoline->Y_end != NULL) &&
		                ((wisoline->X_end - wisoline->X_begin) == (wisoline->Y_end - wisoline->Y_begin))
                	   ) 
			{
				if (!isoname) {
					return wisoline;
				} else {
					if (wisoline->getName()) {
						if ( strcmp(wisoline->getName(),isoname) == 0 ) {
							return wisoline;
						} else {
							delete wisoline;
							wisoline = new wiso(NULL, NULL, NULL, NULL, REAL(0), REAL(0));
						}
					}
				}
			}
		} else {
			if (!isoname)
				writelog(SURFIT_ERROR, "wiso_load : this file have no wiso");
			else
				writelog(SURFIT_ERROR, "wiso_load : this file have no wiso with name %s", isoname);
			delete wisoline;
			return NULL;
		}
	};

exit:
	delete wisoline; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

void _wiso_info(wiso * wisoline) {
	if (!wisoline) {
		writelog(SURFIT_WARNING, "_wiso_info : NULL pointer given");
		return;
	}
	if (wisoline->getName()) {
		if (wisoline->value == undef_value)
			writelog(SURFIT_MESSAGE,"wiso (%s) : value = \"undef\"",wisoline->getName());
		else 
			writelog(SURFIT_MESSAGE,"wiso (%s) : value = %g",wisoline->getName(), wisoline->value);

	} else {
		if (wisoline->value == undef_value)
			writelog(SURFIT_MESSAGE,"wiso noname : value = \"undef\"");
		else 
			writelog(SURFIT_MESSAGE,"wiso noname : value = %g", wisoline->value);
	}
};

wiso * _get_surfit_wiso() {
	return surfit_wiso;
};

void _set_surfit_wiso(wiso * wisoline) {
	delete surfit_wiso;
	surfit_wiso = wisoline;
};

void _add_surfit_wisos(wiso * wisoline) {
	if (!wisoline)
		return;
	surfit_wisos->push_back(wisoline);
};

}; // namespace surfit;




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

#include "flow_ie.h"
#include "piso.h"
#include "piso_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "variables_tcl.h"

#include "piso_user.h"

namespace surfit {

bool _piso_check() {
	if (flow_piso)
		return true;
	return false;
};

bool _piso_unload() {
	if (!_piso_check())
		return false;
	delete flow_piso;
	flow_piso = NULL;
	return true;
};

piso * _piso_read(const char * filename, const char * pisoname, REAL value,
		  int columns, int col1, int col2, int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (pisoname)
		writelog(SURFIT_MESSAGE,"reading piso \"%s\" from file %s", pisoname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading piso from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end))
		return NULL;

	piso * res = new piso(col1_begin, col1_end,
		              col2_begin, col2_end,
			      value,
			      pisoname);

	return res;
};

bool _piso_write(piso * pisoline, const char * filename, const char * mask) {
	if (!pisoline)
		return false;
	return two_columns_write(filename, mask,
		                 pisoline->X_begin, pisoline->X_end,
		                 pisoline->Y_begin, pisoline->Y_end);
};

bool _piso_save(piso * pisoline, const char * filename, int mode) {
	if (!pisoline) {
		writelog(SURFIT_WARNING, "NULL pointer to piso.");
		return false;
	};

	if (!pisoline->getName())
		writelog(SURFIT_MESSAGE,"saving piso to file %s", filename);
	else
		writelog(SURFIT_MESSAGE,"saving piso \"%s\" to file %s", pisoline->getName(), filename);

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _piso_save_df(pisoline, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _piso_save_df(piso * pisoline, datafile * df) {

	if (!pisoline->getName()) 
		writelog(SURFIT_MESSAGE,"saving piso with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving piso \"%s\" to file %s",pisoline->getName(),df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("piso");				res = (op && res);
	if (pisoline->getName()) {
		op = df->writeString("name",pisoline->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", pisoline->X_begin, pisoline->size()); res = (op && res);
	op = df->writeRealArray("y", pisoline->Y_begin, pisoline->size()); res = (op && res);
	op = df->writeReal("value", pisoline->value);                 res = (op && res);
	op = df->writeEndTag();						res = (op && res);
		
	return res;
};

piso * _piso_load(const char * filename, const char * pisoname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	piso * pisoline = _piso_load_df(df, pisoname);
	if (!pisoline)
		goto exit;

	delete df;
	return pisoline;
	
exit:
	delete pisoline; 
	delete df;
	return NULL;

};

piso * _piso_load_df(datafile * df, const char * pisoname) {

	if (!pisoname)
		writelog(SURFIT_MESSAGE,"loading piso from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading piso \"%s\" from file %s", pisoname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "piso_load : wrong datafile format";

	piso * pisoline = new piso(NULL, NULL, NULL, NULL, REAL(0));
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("piso")) {
			
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
						pisoline->value = value;
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
							pisoline->X_begin = X_begin;
							pisoline->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							pisoline->Y_begin = Y_begin;
							pisoline->Y_end = Y_end;
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
						pisoline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(pisoline->X_begin != NULL) &&
				(pisoline->X_end != NULL) &&
				(pisoline->Y_begin != NULL) &&
				(pisoline->Y_end != NULL) &&
        		        ((pisoline->X_end - pisoline->X_begin) == (pisoline->Y_end - pisoline->Y_begin))
                	   ) 
			{
				if (!pisoname) {
					return pisoline;
				} else {
					if (pisoline->getName()) {
						if ( strcmp(pisoline->getName(),pisoname) == 0 ) {
							return pisoline;
						} else {
							delete pisoline;
							pisoline = new piso(NULL, NULL, NULL, NULL, REAL(0));
						}
					}
				}
			}
		} else {
			if (!pisoname)
				writelog(SURFIT_ERROR, "piso_load : this file have no piso");
			else
				writelog(SURFIT_ERROR, "piso_load : this file have no piso with name %s", pisoname);
			delete pisoline;
			return NULL;
		}
	};

exit:
	delete pisoline; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

void _piso_info(piso * pisoline) {
	if (!pisoline) {
		writelog(SURFIT_WARNING, "_piso_info : NULL pointer given");
		return;
	}
	if (pisoline->getName()) {
		if (pisoline->value == undef_value)
			writelog(SURFIT_MESSAGE,"piso (%s) : value = \"undef\"",pisoline->getName());
		else
			writelog(SURFIT_MESSAGE,"piso (%s) : value = %g",pisoline->getName(), pisoline->value);
	} else {
		if (pisoline->value == undef_value)
			writelog(SURFIT_MESSAGE,"piso noname : value = \"undef\"");
		else
			writelog(SURFIT_MESSAGE,"piso noname : value = %g", pisoline->value);
	}
		
};

piso * _get_flow_piso() {
	return flow_piso;
};

void _set_flow_piso(piso * pisoline) {
	delete flow_piso;
	flow_piso = pisoline;
};

void _add_flow_pisos(piso * pisoline) {
	if (!pisoline)
		return;
	flow_pisos->push_back(pisoline);
};

}; // namespace surfit;



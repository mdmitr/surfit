
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
#include "parea.h"
#include "parea_internal.h"
#include "variables_tcl.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"

#include "parea_user.h"

namespace surfit {

bool _parea_check() {
	if (flow_parea)
		return true;
	return false;
};

bool _parea_unload() {
	if (!_parea_check())
		return false;
	delete flow_parea;
	flow_parea = NULL;
	return true;
};

parea * _parea_read(const char * filename, const char * pareaname, REAL value,
		    int columns, int col1, int col2, int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (pareaname)
		writelog(SURFIT_MESSAGE,"reading parea \"%s\" from file %s", pareaname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading parea from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end))
		return NULL;

	parea * res = new parea(col1_begin, col1_end,
		                col2_begin, col2_end,
				value,
				pareaname);

	return res;
};

bool _parea_write(parea * parealine, const char * filename, const char * mask) {
	if (!parealine)
		return false;
	return two_columns_write(filename, mask,
		                 parealine->X_begin, parealine->X_end,
		                 parealine->Y_begin, parealine->Y_end);
};

bool _parea_save(parea * parealine, const char * filename, int mode) {
	if (!parealine) {
		writelog(SURFIT_WARNING, "NULL pointer to parea.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _parea_save_df(parealine, df);
	bool op;
	op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _parea_save_df(parea * ar, datafile * df) {

	if (!ar->getName())
		writelog(SURFIT_MESSAGE,"saving parea to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving parea \"%s\" to file %s", ar->getName(), df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("parea");				res = (op && res);
	if (ar->getName()) {
		op = df->writeString("name",ar->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", ar->X_begin, ar->size()); res = (op && res);
	op = df->writeRealArray("y", ar->Y_begin, ar->size()); res = (op && res);
	op = df->writeReal("value", ar->value);                res = (op && res);
	op = df->writeEndTag();				       res = (op && res);
	
	return res;

};

parea * _parea_load_df(datafile * df, const char * pareaname) {

	if (!pareaname)
		writelog(SURFIT_MESSAGE,"loading parea from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading parea \"%s\" from file %s", pareaname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "parea_load : wrong datafile format";

	parea * parealine = new parea(NULL, NULL, NULL, NULL, REAL(0));
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("parea")) {
			
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
						parealine->value = value;
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
							parealine->X_begin = X_begin;
							parealine->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							parealine->Y_begin = Y_begin;
							parealine->Y_end = Y_end;
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
						parealine->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(parealine->X_begin != NULL) &&
				(parealine->X_end != NULL) &&
				(parealine->Y_begin != NULL) &&
				(parealine->Y_end != NULL) &&
		                ((parealine->X_end - parealine->X_begin) == (parealine->Y_end - parealine->Y_begin))
                	   ) 
			{
				if (!pareaname) {
					return parealine;
				} else {
					if (parealine->getName()) {
						if ( strcmp(parealine->getName(),pareaname) == 0 ) {
							return parealine;
						} else {
							delete parealine;
							parealine = new parea(NULL, NULL, NULL, NULL, REAL(0));
						}
					}
				}
			}
		} else {
			if (!pareaname)
				writelog(SURFIT_ERROR, "parea_load : this file have no pareas");
			else
				writelog(SURFIT_ERROR, "parea_load : this file have no parea with name %s", pareaname);
			delete parealine;
			return NULL;
		}
	};

exit:
	delete parealine; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

parea * _parea_load(const char * filename, const char * pareaname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	parea * parealine = _parea_load_df(df, pareaname);

	if (!parealine)
		goto exit;

	delete df;
	return parealine;

exit:
	delete parealine; 
	delete df;
	return NULL;

};

void _parea_info(parea * parealine) {
	if (!parealine) {
		writelog(SURFIT_WARNING, "_parea_info : NULL pointer given");
		return;
	}
	if (parealine->getName()) {
		if (parealine->value == undef_value)
			writelog(SURFIT_MESSAGE,"parea (%s) : value = \"undef\"",parealine->getName());
		else 
			writelog(SURFIT_MESSAGE,"parea (%s) : value = \"%g\"",parealine->getName(), parealine->value);

	} else {
		if (parealine->value == undef_value)
			writelog(SURFIT_MESSAGE,"parea noname : value = \"undef\"");
		else 
			writelog(SURFIT_MESSAGE,"parea noname : value = \"%g\"", parealine->value);
	}
};

parea * _get_flow_parea() {
	return flow_parea;
};

void _set_flow_parea(parea * parealine) {
	delete flow_parea;
	flow_parea = parealine;
};

void _add_flow_pareas(parea * parealine) {
	if (!parealine)
		return;
	flow_pareas->push_back(parealine);
};

}; // namespace surfit;



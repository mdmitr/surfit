
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
#include "flt.h"
#include "flt_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"

#include "flt_user.h"

namespace surfit {

bool _flt_check() {
	if (surfit_flt)
		return true;
	return false;
};

bool _flt_unload() {
	if (!_flt_check())
		return false;
	delete surfit_flt;
	surfit_flt = NULL;
	return true;
};

flt * _flt_read(const char * filename, const char * fltname, int columns, 
					int col1, int col2, int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;

	if (fltname)
		writelog(SURFIT_MESSAGE,"reading fault line \"%s\" from file %s", fltname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading fault line from file %s", filename);

	if (!two_columns_read(filename, columns, col1, col2, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end))
		return NULL;

	flt * res = new flt(col1_begin, col1_end,
	                    col2_begin, col2_end,
			    fltname);

	return res;
};

bool _flt_write(flt * fault, const char * filename, const char * mask) {
	if (!fault)
		return false;
	return two_columns_write(filename, mask,
		                 fault->X_begin, fault->X_end,
		                 fault->Y_begin, fault->Y_end);
};

bool _flt_save_df(flt * fault, datafile * df) {

	if (!fault->getName()) 
		writelog(SURFIT_MESSAGE,"saving fault with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving fault \"%s\" to file %s",fault->getName(),df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("flt");				res = (op && res);
	if (fault->getName()) {
		op = df->writeString("name",fault->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", fault->X_begin, fault->size()); res = (op && res);
	op = df->writeRealArray("y", fault->Y_begin, fault->size()); res = (op && res);
	op = df->writeEndTag();					     res = (op && res);
	
	return res;
};

bool _flt_save(flt * fault, const char * filename, int mode) {

	if (!fault) {
		writelog(SURFIT_WARNING, "NULL pointer to flt.");
		return false;
	};
	
	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _flt_save_df(fault, df);
	bool op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

flt * _flt_load_df(datafile * df, const char * fltname) {

	if (!fltname)
		writelog(SURFIT_MESSAGE,"loading flt from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading flt \"%s\" from file %s", fltname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "flt_load : wrong datafile format";

	flt * fault = new flt(NULL, NULL, NULL, NULL);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("flt")) {
			
			df->skipTagName();
			
			REAL * X_begin = NULL;
			REAL * X_end = NULL;
			REAL * Y_begin = NULL;
			REAL * Y_end = NULL;
            
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
							fault->X_begin = X_begin;
							fault->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							fault->Y_begin = Y_begin;
							fault->Y_end = Y_end;
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
						fault->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(fault->X_begin != NULL) &&
				(fault->X_end != NULL) &&
				(fault->Y_begin != NULL) &&
				(fault->Y_end != NULL) &&
                ((fault->X_end - fault->X_begin) == (fault->Y_end - fault->Y_begin))
                ) 
			{
				if (!fltname) {
					return fault;
				} else {
					if (fault->getName()) {
						if ( strcmp(fault->getName(),fltname) == 0 ) {
							return fault;
						} else {
							delete fault;
							fault = new flt(NULL, NULL, NULL, NULL);
						}
					}
				}
			}
		} else {
			if (!fltname)
				writelog(SURFIT_ERROR, "flt_load : this file have no flt");
			else
				writelog(SURFIT_ERROR, "flt_load : this file have no flt with name %s", fltname);
			delete fault;
			return NULL;
		}
	};

exit:
	delete fault; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

flt * _flt_load(const char * filename, const char * fltname, int mode) {

	datafile *df = new datafile(filename, DF_MODE_READ, mode);

	flt * fault = _flt_load_df(df, fltname);
	
	if (!fault)
		goto exit;

	delete df;
	return fault;

exit:
	delete fault; 
	delete df;
	return NULL;

};

void _flt_info(flt * fault) {
	if (!fault) {
		writelog(SURFIT_WARNING, "_flt_info : NULL pointer given");
		return;
	}
	if (fault->getName())
		writelog(SURFIT_MESSAGE,"flt (%s)",fault->getName());
	else
		writelog(SURFIT_MESSAGE,"flt noname");	
};

flt * _get_surfit_flt() {
	return surfit_flt;
};

void _set_surfit_flt(flt * fault) {
	delete surfit_flt;
	surfit_flt = fault;
};

void _add_surfit_flts(flt * fault) {
	if (!fault)
		return;
	surfit_flts->push_back(fault);
};

}; // namespace surfit;




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
#include "real.h"
#include "wfunc.h"
#include "wfunc_internal.h"
#include "func_internal.h"
#include "grid.h"
#include "grid_internal.h"
#include "vec.h"
#include "fileio.h"
#include "datafile.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "wtask.h"

#include "wfunc_user.h"

#include <float.h>
#include <errno.h>

namespace surfit {

int calc_ptr(int i, int j, int N);

bool _wfunc_unload(wfunc *& fnc) {
	if (!fnc)
		return false;
	if (fnc->getName())
		writelog(SURFIT_MESSAGE,"unloading wfunc \"%s\"", fnc->getName());
	else 
		writelog(SURFIT_MESSAGE,"unloading noname wfunc");
	delete fnc;
	fnc = NULL;
	return true;
};

bool _wfunc_check() {
	if (surfit_wfunc)
		return true;
	return false;
};

wfunc * _wfunc_load_df(datafile * df, const char * wfuncname) {

	if (!wfuncname) 
		writelog(SURFIT_MESSAGE,"loading wfunc with no name from file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"loading wfunc \"%s\" from file %s",wfuncname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "wfunc_load : wrong datafile format";

	bool err = false;
	wfunc * fnc = NULL;
	vec * icoeff = NULL;
	grid * grd = NULL;
	char * name = NULL;
	REAL undef_value = FLT_MAX;
	REAL weight = 0;

	REAL * coeff_begin = NULL;
	REAL * coeff_end = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("wfunc")) {
			
			df->skipTagName();
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						name = (char*)malloc(strlen(df->getWord())+1);
						strcpy(name,df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}

				if ( df->isWord(REAL_NAME) ) {
					// read char name
					if (!df->readWord()) goto exit;
					
					if ( df->isWord("undef_value") ) {
						if ( !df->readReal(undef_value) ) goto exit;
						goto cont;
					}

					if ( df->isWord("weight") ) {
						if ( !df->readReal(weight) ) goto exit;
						goto cont;
					}

					if (!df->skipReal(false)) goto exit;
					goto cont;
				}
				
				if ( df->isWord("array") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord(REAL_NAME) ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("coeff") ) {
							df->readRealArray(coeff_begin, coeff_end);
							goto cont;
						}
					}
					if ( !df->skipArray(false) ) goto exit;
				}
				
				if ( df->isWord("tag") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord("grid") ) {
						if ( !_grid_load_df_tag_readed(df, grd) ) goto exit;
						goto cont;
					}
					if (!df->skipToEndTag()) goto exit;
					goto cont;
				}
								
				if ( !df->skip(false) ) goto exit;
				goto cont;
cont:
				if ( !df->readWord() ) goto exit;
				continue;
			}
		} else {
			goto exit;
		}
		
		icoeff = new vec(coeff_begin, coeff_end);
		
		if ( !icoeff ) {
			writelog(SURFIT_ERROR,"wfunc_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(SURFIT_ERROR,"wfunc_load : empty geometry");
			err = true;
		}
		
		if (err) {
			delete icoeff;
			delete grd;
			free(name);
			return false;
		}
		
		fnc = new wfunc(icoeff, grd, weight, name);
		fnc->undef_value = undef_value;
		free(name);
		
		if (!wfuncname) {
			return fnc;
		} else {
			if (fnc->getName()) {
				if (strcmp(fnc->getName(),wfuncname) == 0) {
					return fnc;
				}
			}
			delete fnc;
			fnc = NULL;
		}
		
	}
	
	return fnc;

exit:

	if (!wfuncname)
		writelog(SURFIT_ERROR, "wfunc_load : this file have no wfunc");
	else 
		writelog(SURFIT_ERROR, "wfunc_load : this file have no wfunc named %s", wfuncname);
	return NULL;

};

wfunc * _wfunc_load(const char * filename, const char * wfuncname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode); // read
	
	wfunc * res = _wfunc_load_df(df, wfuncname);

	if (!res)
		goto exit;

	delete df;
	return res;

exit:

	delete res;
	delete df;
	return NULL;
};
	

bool _wfunc_save(wfunc * fnc, const char * filename, const char * wfuncname) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE, get_rw_mode()); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	fnc->setName(wfuncname);

	res = _wfunc_save_df(fnc, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _wfunc_save_df(wfunc * fnc, datafile * df) {

	if (!fnc->getName()) 
		writelog(SURFIT_MESSAGE,"saving wfunc with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving wfunc \"%s\" to file %s",fnc->getName(),df->get_filename());
		
	bool res = true;
	bool op;
	
	op = fnc->writeTags(df);           res = ( op && res );
	
	return res;
};

void _wfunc_info(wfunc * fnc) {
	if (!fnc)
		return;
	if (fnc->getName()) 
		writelog(SURFIT_MESSAGE,"wfunc (%s) : size=(%d x %d)", fnc->getName(), fnc->getCountX(), fnc->getCountY());
	else 
		writelog(SURFIT_MESSAGE,"wfunc noname : size=(%d x %d)", fnc->getCountX(), fnc->getCountY());
};

wfunc * _get_surfit_wfunc() {
	return surfit_wfunc;
};

void _set_surfit_wfunc(wfunc * fnc) {
	delete surfit_wfunc;
	surfit_wfunc = fnc;
};

void _add_surfit_wfuncs(wfunc * fnc) {
	if (!fnc)
		return;
	surfit_wfuncs->push_back(fnc);
};

wtask * _wfunc_to_wtask(wfunc * wfnc) {
	
	REAL * Z_begin = (REAL*)malloc(wfnc->coeff->size() * sizeof(REAL));
	
	if (!wfnc->coeff) {
		writelog(SURFIT_ERROR,"convert_wfunc_to_wtask : wrong wfunc - no coeffs");
		return NULL;
	}

	Z_begin = (REAL*) memcpy(Z_begin, wfnc->coeff->begin(), wfnc->coeff->size() * sizeof(REAL));
	if (Z_begin == NULL) {
		writelog(SURFIT_ERROR,"Not enought memory to convert func to task");
		return NULL;
	}

	REAL * Z_end = Z_begin + wfnc->coeff->size();

	REAL * X_begin = (REAL*)malloc(wfnc->coeff->size() * sizeof(REAL));
	if (X_begin == NULL) {
		writelog(SURFIT_ERROR,"Not enought memory to convert func to task");
		free(Z_begin);
		return NULL;
	}
	REAL * X_end = X_begin + wfnc->coeff->size();
	
	REAL * Y_begin = (REAL*)malloc(wfnc->coeff->size() * sizeof(REAL));
	if (Y_begin == NULL) {
		writelog(SURFIT_ERROR,"Not enought memory to convert func to task");
		free(Z_begin);
		free(X_begin);
		return NULL;
	}
	REAL * Y_end = Y_begin + wfnc->coeff->size();

	REAL * X_ptr = X_begin;
	REAL * Y_ptr = Y_begin;

	int i,j;
	for (j = 0; j < wfnc->getCountY(); j++) {
		for (i = 0; i < wfnc->getCountX(); i++) {
			wfnc->getCoordNode(i,j,*X_ptr,*Y_ptr);
			X_ptr++;
			Y_ptr++;
		}
	}

	REAL * W_begin = (REAL*)malloc(wfnc->coeff->size() * sizeof(REAL));
	REAL * W_end = W_begin + wfnc->coeff->size();
	for (j = 0; j < wfnc->coeff->size(); j++) {
		*(W_begin + j) = wfnc->weight;
	}

	return new wtask(X_begin, X_end,
			 Y_begin, Y_end,
			 Z_begin, Z_end,
			 W_begin, W_end,
			 wfnc->getName());
};

wfunc * _wfunc_project(wfunc * wfnc, grid * grd) {
	func * fnc = _func_project(wfnc, grd);
	if (!fnc)
		return NULL;
	wfunc * res = new wfunc(fnc, wfnc->weight);
	
	delete fnc;
	return res;
};

wfunc * _wfunc_project(wfunc * wfnc, grid * grd, grid_line * fault_line) {
	func * fnc = _func_project(wfnc, grd, fault_line);
	if (!fnc)
		return NULL;
	wfunc * res = new wfunc(fnc, wfnc->weight);
	
	delete fnc;
	return res;
};

func * _wfunc_to_func(wfunc * wfnc) {
	if (!wfnc)
		return NULL;
	func * res = new func( new vec(*(wfnc->coeff)), new grid(wfnc->grd), wfnc->getName() );
	return res;
};

wfunc * _wfunc_load_grd(const char * filename, REAL weight, const char * wfuncname = NULL) 
{
	func * fnc = _func_load_grd(filename, wfuncname);
	if (!fnc)
		return NULL;
	wfunc * res = new wfunc(fnc, weight);
	
	delete fnc;
	return res;
};

}; // namespace surfit;



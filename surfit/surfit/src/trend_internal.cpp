
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
#include "trend.h"
#include "trend_internal.h"
#include "fileio.h"
#include "func_internal.h"
#include "vec.h"
#include "datafile.h"
#include "grid.h"
#include "grid_internal.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "trend_user.h"

#include <float.h>

namespace surfit {

bool _trend_unload(trend *& func) {
	if (!func)
		return false;
	if (func->getName())
		writelog(SURFIT_MESSAGE,"unloading trend \"%s\"", func->getName());
	else 
		writelog(SURFIT_MESSAGE,"unloading noname trend");
	delete func;
	func = NULL;
	return true;
};

bool _trend_check() {
	if (surfit_trend)
		return true;
	return false;
};

bool _trend_save(trend * fnc, const char * filename, const char * funcname) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE, get_rw_mode()); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	fnc->setName(funcname);

	res = _trend_save_df(fnc, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _trend_save_df(trend * fnc, datafile * df) {

	if (!fnc->getName()) 
		writelog(SURFIT_MESSAGE,"saving trend with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving trend \"%s\" to file %s",fnc->getName(),df->get_filename());
	
	bool res = true;
	bool op;
	
	op = fnc->writeTags(df);           res = ( op && res );
	
	return res;
};

trend * _trend_load_df(datafile * df, const char * funcname) {

	if (!funcname) 
		writelog(SURFIT_MESSAGE,"loading trend with no name from file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"loading trend \"%s\" from file %s",funcname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "trend_load : wrong datafile format";

	bool err = false;
	trend * aux_fnc = NULL;
	vec * icoeff = NULL;
	grid * grd = NULL;
	char * name = NULL;
	REAL undef_value = FLT_MAX;
	REAL D1 = 1;
	REAL D2 = 0;

	REAL * coeff_begin = NULL;
	REAL * coeff_end = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("trend")) {
			
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

					if ( df->isWord("D1") ) {
						if ( !df->readReal(D1) ) goto exit;
						goto cont;
					}

					if ( df->isWord("D2") ) {
						if ( !df->readReal(D2) ) goto exit;
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
			writelog(SURFIT_ERROR,"func_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(SURFIT_ERROR,"func_load : empty geometry");
			err = true;
		}
		
		if (err) {
			delete icoeff;
			delete grd;
			free(name);
			return false;
		}
		
		aux_fnc = new trend(icoeff, grd, D1, D2, name);
		aux_fnc->undef_value = undef_value;
		free(name);
		
		if (!funcname) {
			return aux_fnc;
		} else {
			if (aux_fnc->getName()) {
				if (strcmp(aux_fnc->getName(),funcname) == 0) {
					return aux_fnc;
				}
			}
			delete aux_fnc;
			aux_fnc = NULL;
		}
		
	}
	
	return aux_fnc;

exit:

	if (!funcname)
		writelog(SURFIT_ERROR, "trend_load : this file have no trend");
	else 
		writelog(SURFIT_ERROR, "trend_load : this file have no trend named %s", funcname);
	return NULL;

};

trend * _trend_load(const char * filename, const char * funcname, int mode) {
	
	datafile * df = new datafile(filename, DF_MODE_READ, mode); // read
	
	trend * res = _trend_load_df(df, funcname);

	if (!res)
		goto exit;

	delete df;
	return res;

exit:

	delete res;
	delete df;
	return NULL;
};

trend * _trend_load_grd(const char * filename, REAL D1, REAL D2, const char * trendname = NULL) 
{
	func * fnc = _func_load_grd(filename, trendname);
	if (!fnc)
		return NULL;
	trend * res = new trend(fnc, D1, D2);
	
	delete fnc;

	return res;
};

void _trend_info(trend * aux_fnc) {
	if (!aux_fnc)
		return;
	if (aux_fnc->getName()) 
		writelog(SURFIT_MESSAGE,"trend (%s) : D1=%lf, D2=%lf, size=(%d x %d)", 
		aux_fnc->getName(), aux_fnc->D1, aux_fnc->D2, aux_fnc->getCountX(), aux_fnc->getCountY());
	else 
		writelog(SURFIT_MESSAGE,"trend noname : D1=%lf, D2=%lf, size=(%d x %d)", 
		aux_fnc->D1, aux_fnc->D2, aux_fnc->getCountX(), aux_fnc->getCountY());
};

trend * _get_surfit_trend() {
	return surfit_trend;
};

void _set_surfit_trend(trend * aux_fnc) {
	delete surfit_trend;
	surfit_trend = aux_fnc;
};

void _add_surfit_trends(trend * aux_fnc) {
	if (!aux_fnc)
		return;
	surfit_trends->push_back(aux_fnc);
};

trend * _trend_project(trend * trnd, grid * grd) {
	func * fnc = _func_project(trnd, grd);
	if (!fnc)
		return NULL;
	trend * res = new trend(fnc, trnd->D1, trnd->D2);
	
	delete fnc;
	return res;
};

trend * _trend_project(trend * trnd, grid * grd, grid_line * fault_line) {
	func * fnc = _func_project(trnd, grd, fault_line);
	if (!fnc)
		return NULL;
	trend * res = new trend(fnc, trnd->D1, trnd->D2);
	
	delete fnc;
	return res;
};

func * _trend_to_func(trend * trnd) {
	if (!trnd)
		return NULL;
	func * res = new func( new vec(*(trnd->coeff)), new grid(trnd->grd), trnd->getName() );
	return res;
};

}; // namespace surfit;



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
#include "defarea.h"
#include "func.h"
#include "defarea_internal.h"
#include "defarea_tcl.h"
#include "func_internal.h"
#include "func_tcl.h"
#include "grid.h"
#include "fileio.h"
#include "boolvec.h"
#include "variables_internal.h"

#include "defarea_user.h"
#include "func_user.h"

#include <errno.h>
#include <float.h>

namespace surfit {

void defarea_unload() {
	_defarea_unload(surfit_defarea);
};

bool defarea_check() {
	return (surfit_defarea != NULL);
};

bool defarea_load(const char * filename, const char * defname) {
	defarea_unload();
	surfit_defarea = _defarea_load(filename, defname, get_rw_mode());
	return (surfit_defarea != NULL);
};

bool defarea_save(const char * filename, const char * defname) {
	if (!_defarea_check())
		return false;
	return _defarea_save(surfit_defarea, filename,defname);
};

bool defarea_save_grd(const char * filename) {

	if (!filename)
		return false;

	if (!surfit_defarea) {
		writelog(SURFIT_ERROR,"defarea_save_grd : no defarea loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(SURFIT_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	writelog(SURFIT_MESSAGE,"Saving defarea %s to file %s (grd-ASCII)", surfit_defarea->getName(), filename);

	fprintf(f,"DSAA\n");
	int nx = surfit_defarea->getCountX();
	int ny = surfit_defarea->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", surfit_defarea->getMinX(), surfit_defarea->getMaxX());
	fprintf(f,"%lf %lf\n", surfit_defarea->getMinY(), surfit_defarea->getMaxY());
	fprintf(f,"0 1\n");

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = (*(surfit_defarea->coeff))( ix + nx*iy );
			fprintf(f,"%lf ", val);
			if (ncnt>9) { 
				fprintf(f,"\n");
				ncnt = 0;
			}
			ncnt++;
		}
		fprintf(f,"\n");
	}

	fclose(f);

	return true;
};

bool defarea_save_xyz(const char * filename) {

	if (!filename)
		return false;

	if (!surfit_defarea) {
		writelog(SURFIT_ERROR,"defarea_save_xyz : no defarea loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(SURFIT_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	writelog(SURFIT_MESSAGE,"Saving defarea %s to file %s (xyz-ASCII)", surfit_defarea->getName(), filename);

	int nx = surfit_defarea->getCountX();
	int ny = surfit_defarea->getCountY();

	int iy, ix;
	int cnt = 0;
	REAL val;
	REAL x_coord, y_coord;
	
    
	for(iy=0; iy<ny; iy++)	{
		for(ix=0; ix<nx; ix++)	{
			surfit_defarea->getCoordNode(ix, iy, x_coord, y_coord);
			val = (*(surfit_defarea->coeff))( ix + nx*iy );
			fprintf(f,"%lf %lf %lf \n", x_coord, y_coord, val);
			
		}
	}

	fclose(f);

	return true;
};

bool defarea_or(defarea * def) {
	writelog(SURFIT_MESSAGE,"defarea : OR operation");
	if (!_defarea_check())
		return false;
	surfit_defarea->OR(def);
	return true;
};

bool defarea_xor(defarea * def) {
	writelog(SURFIT_MESSAGE,"defarea : XOR operation");
	if (!_defarea_check())
		return false;
	surfit_defarea->XOR(def);
	return true;
};

bool defarea_and(defarea * def) {
	writelog(SURFIT_MESSAGE,"defarea : AND operation");
	if (!_defarea_check())
		return false;
	surfit_defarea->AND(def);
	return true;
};

bool defarea_not(defarea * def) {
	writelog(SURFIT_MESSAGE,"defarea : NOT operation");
	if (!_defarea_check() && def) {
		surfit_defarea = new defarea(new boolvec(*(def->coeff)), new grid(def->grd));
		surfit_defarea->NOT(def);
		return true;
	}

	if (!_defarea_check() && !def) {
		writelog(SURFIT_ERROR,"defarea : NOT operation - no defareas loaded");
		return false;
	}

	if (def) {
		delete surfit_defarea;
		surfit_defarea = new defarea(new boolvec(*(def->coeff)), new grid(def->grd));
		surfit_defarea->NOT(def);
	} else
		surfit_defarea->NOT(surfit_defarea);
	
	
	return true;
};

bool defarea_by_func() {
	if (!_func_check())
		return false;
	defarea_unload();
	surfit_defarea = _defarea_by_func(surfit_func);
	return (surfit_defarea != NULL);
};

bool defarea_apply_to_func() {
	if (!_func_check())
		return false;
	if (!_defarea_check())
		return false;

	return _defarea_apply_to_func(surfit_defarea, surfit_func);
};

bool defarea_name(const char * new_name, defarea * def) {
	if (def) {
		def->setName(new_name);
		return true;
	}
	if (!_defarea_check())
		return false;
	if (!new_name) {
		if (surfit_defarea->getName())
			writelog(SURFIT_MESSAGE,"surfit_defarea name is \"%s\"",surfit_defarea->getName());
		else 
			writelog(SURFIT_MESSAGE,"surfit_defarea have no name");
		return true;
	}
	surfit_defarea->setName(new_name);
	return true;
};

bool defarea_getValue(REAL x, REAL y) {
	if (!_defarea_check())
		return false;
	return surfit_defarea->getValue(x,y);
};

bool defarea_to_func() {
	if (!_defarea_check())
		return false;

	if (surfit_func)
		func_unload();

	surfit_func = new func(surfit_defarea);
	delete surfit_defarea;
	return true;
};

bool defarea_to_funcs() {
	if (!_defarea_check())
		return false;

	func * fnc = new func(surfit_defarea);
	
	delete surfit_defarea;
	surfit_funcs->push_back(fnc);
	return true;
};

bool defarea_to_defareas() {
	if (!_defarea_check())
		return false;
	surfit_defareas->push_back(surfit_defarea);
	surfit_defarea = NULL;
	return true;
};


}; // namespace surfit;


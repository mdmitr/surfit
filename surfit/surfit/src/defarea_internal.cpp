
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
#include "defarea.h"
#include "defarea_internal.h"
#include "grid.h"
#include "grid_internal.h"
#include "func.h"
#include "fileio.h"
#include "datafile.h"
#include "boolvec.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "defarea_user.h"

#include <errno.h>

namespace surfit {

bool _defarea_unload(defarea *& func) {
	if (!func)
		return false;
	if (func->getName())
		writelog(SURFIT_MESSAGE,"unloading defarea \"%s\"", func->getName());
	else 
		writelog(SURFIT_MESSAGE,"unloading noname defarea");
	delete func;
	func = NULL;
	return true;
};

bool _defarea_check() {
	if (surfit_defarea)
		return true;
	return false;
};

defarea * _defarea_load_df(datafile * df, const char * defareaname) {

	if (!defareaname) 
		writelog(SURFIT_MESSAGE,"loading defarea with no name from file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"loading defarea \"%s\" from file %s",defareaname,df->get_filename());


	if (!df->condition()) {
		return NULL;
	}

	char error[] = "defarea_load : wrong datafile format";

	bool err = false;
	defarea * def = NULL;
	boolvec * icoeff = NULL;
	grid * grd = NULL;
	char * name = NULL;

	bool * coeff_begin = NULL;
	bool * coeff_end = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("defarea")) {
			
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

					if (!df->skipReal(false)) goto exit;
					goto cont;
				}
				
				if ( df->isWord("array") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord("bool") ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("coeff") ) {
							df->readBoolArray(coeff_begin, coeff_end);
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
		
		icoeff = new boolvec(coeff_begin, coeff_end);
		
		if ( !icoeff ) {
			writelog(SURFIT_ERROR,"defarea_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(SURFIT_ERROR,"defarea_load : empty geometry");
			err = true;
		}
		
		if (err) {
			delete icoeff;
			delete grd;
			free(name);
			return false;
		}
		
		def = new defarea(icoeff, grd, name);
		free(name);
		
		if (!defareaname) {
			return def;
		} else {
			if (def->getName()) {
				if (strcmp(def->getName(),defareaname) == 0) {
					return def;
				}
			}
			delete def;
			def = NULL;
		}
		
	}
	
	return def;

exit:

	if (!defareaname)
		writelog(SURFIT_ERROR, "defarea_load : this file have no defarea");
	else 
		writelog(SURFIT_ERROR, "defarea_load : this file have no defarea named %s", defareaname);
	return NULL;

};


defarea * _defarea_load(const char * filename, const char * defareaname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode); // read
	
	defarea * res = _defarea_load_df(df, defareaname);

	if (!res)
		goto exit;

	delete df;
	return res;

exit:

	delete res;
	delete df;
	return NULL;
};


bool _defarea_save(defarea * def, const char * filename, const char * defareaname) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE, get_rw_mode()); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	def->setName(defareaname);

	res = _defarea_save_df(def, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _defarea_save_df(defarea * def, datafile * df) {

	if (!def->getName()) 
		writelog(SURFIT_MESSAGE,"saving defarea with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving defarea \"%s\" to file %s",def->getName(),df->get_filename());
	
	bool res = true;
	bool op;
	
	op = def->writeTags(df);           res = ( op && res );
	
	return res;
};


defarea * _defarea_load_grd(const char * filename, const char * defareaname) 
{
	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(SURFIT_ERROR, "defarea_load_grd : The file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	int nx, ny;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	bool * values = NULL;
	grid * grd = NULL;
	defarea * res = NULL;
	boolvec * data = NULL;

	char buf[200];
	if (fscanf(file, "%s", buf) == 0)
		goto exit;
		
	if (strcmp(buf,"DSAA") != 0) 
		goto exit;
	
	int ix, iy;

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	nx = atoi(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	ny = atoi(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	minx = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxx = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	miny = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxy = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	minz = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxz = atof(buf);

	values = (bool*)malloc(sizeof(bool)*nx*ny);

	for(iy=0; iy<ny; iy++) {
		for(ix=0; ix<nx; ix++) {
			
			if (fscanf(file, "%s", buf) != 1)
				goto exit;
	
			*(values + ix + iy*nx) = (atoi(buf) != 0);
		}
	}

	if (fscanf(file, "%s", buf) == 1)
		goto exit;

	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = new grid(minx, maxx, stepX,
                   miny, maxy, stepY);

	data = new boolvec(values, values + nx*ny);

	res = new defarea(data, grd, defareaname);

	return res;

exit:
	writelog(SURFIT_ERROR, "func_load_grd : Wrong file format %s", filename);
	
	delete res;
	delete data;
	delete grd;
	free(values);
	fclose(file);
	return NULL;
}

defarea * _defarea_by_func(func * fnc) {
	if (!fnc)
		return NULL;
	boolvec * bcoeff = new boolvec( fnc->coeff->size() );
	int i;
	REAL val;
	for (i = 0; i < fnc->coeff->size(); i++) {
		val = (*(fnc->coeff))(i);
		if (val != fnc->undef_value)
			(*bcoeff)(i) = 1;
		else 
			(*bcoeff)(i) = 0;
	};

	grid * fgrd = fnc->grd;
	grid * grd = new grid(fgrd);

	defarea * res = new defarea(bcoeff, grd, fnc->getName());
	return res;

};

bool _defarea_apply_to_func(defarea * def, func * fnc) {
	if (!fnc)
		return false;
	if (!def)
		return false;
	
	int i,j;
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();
	REAL x,y;
	bool val;
	REAL func_val;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			fnc->getCoordNode(i,j,x,y);
			func_val = (*(fnc->coeff))(i + j*NN);
			val = def->getValue(x,y);
			if (val == false) {
				(*(fnc->coeff))(i + j*NN) = fnc->undef_value;
			}
		}
	}

	return true;
};

defarea * _get_surfit_defarea() {
	return surfit_defarea;
};

void _set_surfit_defarea(defarea * def) {
	delete surfit_defarea;
	surfit_defarea = def;
};

void _defarea_info(defarea * def) {
	if (!def)
		return;
	if (def->getName()) 
		writelog(SURFIT_MESSAGE,"defarea (%s) : size=(%d x %d)", def->getName(), def->getCountX(), def->getCountY());
	else 
		writelog(SURFIT_MESSAGE,"defarea noname : size=(%d x %d)", def->getCountX(), def->getCountY());
};

}; // namespace surfit;


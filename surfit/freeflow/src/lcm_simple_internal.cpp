
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
#include "lcm_simple_internal.h"
#include "lcm_simple.h"
#include "flow_variables.h"
#include "fileio.h"
#include "datafile.h"

#include "lcm_simple_user.h"

#include <errno.h>

namespace surfit {

lcm_simple * _lcm_simple_read(const char * filename, const char * lcm_simple_name) {

	if (lcm_simple_name)
		writelog(SURFIT_MESSAGE,"reading lcm_simple \"%s\" from file %s", lcm_simple_name, filename);
	else
		writelog(SURFIT_MESSAGE,"reading lcm_simple from file %s", filename);
	

	lcm_simple * res = NULL;

	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "loading lcm_simple: file error");
		fclose(file);
		return false;
	}

	REAL permeability, viscosity, multiplier;

	char buf[256];
	int scan_res = 0;
	
	scan_res = fscanf(file,"%s",buf);
	if (scan_res == -1)
		goto fatal_exit;
	permeability = atof(buf);

	scan_res = fscanf(file,"%s",buf);
	if (scan_res == -1)
		goto fatal_exit;
	viscosity = atof(buf);

	scan_res = fscanf(file,"%s",buf);
	if (scan_res == -1)
		goto fatal_exit;
	multiplier = atof(buf);

	fclose(file);

	res = new lcm_simple(permeability, viscosity, multiplier, lcm_simple_name);
	return res;
	

fatal_exit:

	writelog(SURFIT_ERROR, "loading lcm_simple: file error");
	fclose(file);
	return res;

};

lcm_simple * _lcm_simple_load_df(datafile * df, const char * lcm_simple_name) {

	if (!lcm_simple_name)
		writelog(SURFIT_MESSAGE,"loading lcm_simple from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading lcm_simple \"%s\" from file %s", lcm_simple_name, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "lcm_simple_load : wrong datafile format";

	lcm_simple * lcm = new lcm_simple(1, 1, 1);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("lcm_simple")) {
			
			df->skipTagName();
			
			REAL perm, visc, mult;
			
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord(REAL_NAME) ) {
					// read variable name
					if (!df->readWord()) goto exit;
					if ( df->isWord("permeability") ) {
						if ( !df->readReal(perm) ) goto exit;
						lcm->permeability = perm;
						if ( !df->readWord() ) goto exit;
						continue;
					}
					if ( df->isWord("viscosity") ) {
						if ( !df->readReal(visc) ) goto exit;
						lcm->viscosity = visc;
						if ( !df->readWord() ) goto exit;
						continue;
					}
					if ( df->isWord("multiplier") ) {
						if ( !df->readReal(mult) ) goto exit;
						lcm->multiplier = mult;
						if ( !df->readWord() ) goto exit;
						continue;
					}
					if ( !df->skipReal(false) ) goto exit;
				}
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						lcm->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (!lcm_simple_name) {
				return lcm;
			} else {
				if (lcm->getName()) {
					if ( strcmp(lcm->getName(),lcm_simple_name) == 0 ) {
						return lcm;
					} else {
						delete lcm;
						lcm = new lcm_simple(1, 1, 1);
					}
				}
			}
			
		} else {
			if (!lcm_simple_name)
				writelog(SURFIT_ERROR, "lcm_simple_load : this file have no lcm_simple");
			else
				writelog(SURFIT_ERROR, "lcm_simple_load : this file have no lcm_simple with name %s", lcm_simple_name);
			delete lcm;
			return NULL;
		}
	};

exit:
	delete lcm; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

lcm_simple * _lcm_simple_load(const char * filename, const char * lcm_simple_name, int mode) {
	
	datafile *df = new datafile(filename, DF_MODE_READ, mode);
	
	lcm_simple * lcm = _lcm_simple_load_df(df, lcm_simple_name);

	if (!lcm)
		goto exit;

	delete df;
	return lcm;

exit:
	delete lcm; 
	delete df;
	return NULL;

};


bool _lcm_simple_write(lcm_simple * lcm, const char * filename) {

	if (!lcm)
		return false;

	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(SURFIT_WARNING, "writing lcm_simple : NULL pointer to file.");
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "writing clm_simple file: file error.");
		fclose(file);
		return false;
	}

	fprintf(file,"%lf %lf %lf",lcm->permeability, lcm->viscosity, lcm->multiplier);
	
	fclose(file);
	return true;
};

bool _lcm_simple_save(lcm_simple * lcm, const char * filename, int mode) {
	if (!lcm) {
		writelog(SURFIT_WARNING, "NULL pointer to lcm_simple.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _lcm_simple_save_df(lcm, df);
	bool op;
	op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _lcm_simple_save_df(lcm_simple * lcm, datafile * df) {
	if (!lcm->getName())
		writelog(SURFIT_MESSAGE,"saving lcm_simple to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving lcm_simple \"%s\" to file %s", lcm->getName(), df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("lcm_simple"); res = (op && res);
	if (lcm->getName()) {
		op = df->writeString("name",lcm->getName()); res = (op && res);
	}
	op = df->writeReal("permeability", lcm->permeability); res = (op && res);
	op = df->writeReal("viscosity", lcm->viscosity); res = (op && res);
	op = df->writeReal("multiplier", lcm->multiplier); res = (op && res);
	op = df->writeEndTag();	res = (op && res);
	
	return res;
};

bool _lcm_simple_check() {
	return (flow_lcm_simple != NULL);
};

int _lcm_simple_info(lcm_simple * lcm) {
	writelog(SURFIT_MESSAGE,"lcm_simple : perm = %g, visc = %g, mult = %g",
		lcm->permeability,
		lcm->viscosity,
		lcm->multiplier);
	return lcm->get_priority();
};

lcm_simple * _get_flow_lcm_simple() {
	return flow_lcm_simple;
};

void _set_flow_lcm_simple(lcm_simple * lcm) {
	delete flow_lcm_simple;
	flow_lcm_simple = lcm;
};

}; // namespace surfit;


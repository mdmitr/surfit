
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "surfit_ie.h"

#include "real.h"
#include "fileio.h"
#include "datafile.h"

#include "mask.h"
#include "mask_internal.h"
#include "grid.h"
#include "grid_internal.h"
#include "surf.h"
#include "bitvec.h"
#include "vec.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include <errno.h>

namespace surfit {

d_mask * _mask_load_df(datafile * df, const char * maskname) {

	if (!maskname) 
		writelog(LOG_MESSAGE,"loading mask with no name from file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"loading mask \"%s\" from file %s",maskname,df->get_filename());


	if (!df->condition()) {
		return NULL;
	}

	char error[] = "mask_load : wrong datafile format";

	bool err = false;
	d_mask * msk = NULL;
	bitvec * icoeff = NULL;
	d_grid * grd = NULL;
	char * name = NULL;

	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("mask")) {
			
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
					if ( df->isWord("bit") ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("coeff") ) {
							df->readBitArray(icoeff);
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
				
		if ( !icoeff ) {
			writelog(LOG_ERROR,"mask_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(LOG_ERROR,"mask_load : empty geometry");
			err = true;
		}
		
		if (err) {
			if (icoeff)
				icoeff->release();
			if (grd)
				grd->release();
			free(name);
			return false;
		}
		
		msk = create_mask(icoeff, grd, name);
		free(name);
		
		if (!maskname) {
			return msk;
		} else {
			if (msk->getName()) {
				if (strcmp(msk->getName(),maskname) == 0) {
					return msk;
				}
			}
			if (msk)
				msk->release();
			msk = NULL;
		}
		
	}
	
	return msk;

exit:

	if (!maskname)
		writelog(LOG_ERROR, "mask_load : this file have no mask");
	else 
		writelog(LOG_ERROR, "mask_load : this file have no mask named %s", maskname);
	return NULL;

};


d_mask * _mask_load(const char * filename, const char * maskname) {

	datafile * df = new datafile(filename, DF_MODE_READ); // read
	
	d_mask * res = _mask_load_df(df, maskname);

	if (!res)
		goto exit;

	delete df;
	return res;

exit:

	if (res)
		res->release();
	delete df;
	return NULL;
};


bool _mask_save(const d_mask * msk, const char * filename) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	res = _mask_save_df(msk, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _mask_save_df(const d_mask * msk, datafile * df) {

	if (!msk->getName()) 
		writelog(LOG_MESSAGE,"saving mask with no name to file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"saving mask \"%s\" to file %s",msk->getName(),df->get_filename());
	
	bool res = true;
	bool op;
	
	op = msk->writeTags(df);           res = ( op && res );
	
	return res;
};


d_mask * _mask_load_grd(const char * filename, const char * maskname) 
{
	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(LOG_ERROR, "mask_load_grd : The file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	int nx, ny;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	bitvec * values = NULL;
	d_grid * grd = NULL;
	d_mask * res = NULL;
	
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
	
	values = create_bitvec(nx*ny);
	
	for(iy=0; iy<ny; iy++) {
		for(ix=0; ix<nx; ix++) {
			
			if (fscanf(file, "%s", buf) != 1)
				goto exit;
	
			bool val = (atoi(buf) != 0);

			if (val)
				values->set_true(ix + iy*nx);
			else 
				values->set_false(ix + iy*nx);
		}
	}

	if (fscanf(file, "%s", buf) == 1)
		goto exit;

	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = create_grid(minx, maxx, stepX,
                          miny, maxy, stepY);

	res = create_mask(values, grd, maskname);

	return res;

exit:
	writelog(LOG_ERROR, "surf_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (values)
		values->release();
	if (grd)
		grd->release();
	fclose(file);
	return NULL;
}

d_mask * _mask_by_surf(const d_surf * srf) {
	if (!srf)
		return NULL;
	bitvec * bcoeff = create_bitvec( srf->coeff->size() );
	size_t i;
	REAL val;
	for (i = 0; i < srf->coeff->size(); i++) {
		val = (*(srf->coeff))(i);
		if (val != srf->undef_value)
			bcoeff->set_true(i);
		else 
			bcoeff->set_false(i);
	};

	d_grid * fgrd = srf->grd;
	d_grid * grd = create_grid(fgrd);

	d_mask * res = create_mask(bcoeff, grd, srf->getName());
	return res;

};

bool _mask_apply_to_surf(const d_mask * msk, d_surf * srf) {
	if (!srf)
		return false;
	if (!msk)
		return false;

	writelog(LOG_MESSAGE,"applying mask \"%s\" to surface \"%s\"",
		msk->getName(),srf->getName());
	
	size_t i,j;
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();
	REAL x,y;
	bool val;
	REAL surf_val;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			srf->getCoordNode(i,j,x,y);
			surf_val = (*(srf->coeff))(i + j*NN);
			val = msk->getValue(x,y);
			if (val == false) {
				(*(srf->coeff))(i + j*NN) = srf->undef_value;
			}
		}
	}

	return true;
};

void _mask_info(const d_mask * msk) {
	if (!msk)
		return;
	writelog(LOG_MESSAGE,"mask (%s) : size=(%d x %d)", msk->getName(), msk->getCountX(), msk->getCountY());
};

void _surfit_mask_add(d_mask * msk) {
	surfit_masks->push_back(msk);
};


}; // namespace surfit;


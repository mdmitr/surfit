
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

#include "sstuff.h"
#include "real.h"
#include "fileio.h"
#include "bitvec.h"
#include "vec.h"
#include "datafile.h"

#include "surf.h"
#include "surf_internal.h"
#include "grid.h"
#include "grid_internal.h"
#include "grid_line.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "points.h"
#include "curv.h"
#include "grid_line_internal.h"

#include "sort_alg.h"

#include "grid_line_user.h"
#include "grid_user.h"

#include <math.h>
#include <float.h>
#include <errno.h>

namespace surfit {

int calc_ptr(int i, int j, int N);

d_surf * _surf_load_df(datafile * df, const char * surfname) {

	if (!surfname) 
		writelog(LOG_MESSAGE,"loading surf with no name from file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"loading surf \"%s\" from file %s",surfname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "surf_load : wrong datafile format";

	bool err = false;
	d_surf * srf = NULL;
	vec * icoeff = NULL;
	d_grid * grd = NULL;
	char * name = NULL;
	REAL undef_value = FLT_MAX;

	vec * coeff = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("surf","func")) {
			
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
					if ( df->isWord(REAL_NAME) ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("coeff") ) {
							df->readRealArray(coeff);
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
		
		if ( !coeff ) {
			writelog(LOG_ERROR,"surf_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(LOG_ERROR,"surf_load : empty geometry");
			err = true;
		}
		
		if (err) {
			if (coeff)
				coeff->release();
			delete grd;
			free(name);
			return false;
		}
		
		srf = create_surf(coeff, grd, name);
		srf->undef_value = undef_value;
		free(name);
		
		if (!surfname) {
			return srf;
		} else {
			if (srf->getName()) {
				if (strcmp(srf->getName(),surfname) == 0) {
					return srf;
				}
			}
			if (srf)
				srf->release();
			srf = NULL;
		}
		
	}
	
	return srf;

exit:

	if (!surfname)
		writelog(LOG_ERROR, "surf_load : this file have no surf");
	else 
		writelog(LOG_ERROR, "surf_load : this file have no surf named %s", surfname);
	return NULL;

};

d_surf * _surf_load(const char * filename, const char * surfname) {

	datafile * df = new datafile(filename, DF_MODE_READ); // read

	d_surf * res = _surf_load_df(df, surfname);

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
	
bool _surf_save(const d_surf * srf, const char * filename) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	res = _surf_save_df(srf, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _surf_save_df(const d_surf * srf, datafile * df) {

	if (!srf->getName()) 
		writelog(LOG_MESSAGE,"saving surf with no name to file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"saving surf \"%s\" to file %s",srf->getName(),df->get_filename());
		
	bool res = true;
	bool op;
	
	op = srf->writeTags(df);           res = ( op && res );
	
	return res;
};

d_surf * _surf_load_grd(const char * filename, const char * surfname) 
{
	writelog(LOG_MESSAGE, "loading surface from Surfer GRD-ASCII format file %s",filename);

	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(LOG_ERROR, "surf_load_grd : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	int nx, ny;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	d_grid * grd = NULL;
	d_surf * res = NULL;
	vec * data = NULL;

	char buf[200];
	
	//if ( fscanf(file, "%s", buf) == 0)
	//	goto exit;
	if ( fread(buf, sizeof(char), 4, file) != 4)
		goto exit;
	buf[4]='\0';
		
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

	data = create_vec(nx*ny);
	REAL value;

	for(iy=0; iy<ny; iy++) {
		for(ix=0; ix<nx; ix++) {
			
			if (fscanf(file, "%s", buf) != 1)
				goto exit;
	
			value = atof(buf);
			if ((value >= minz) && (value <= maxz))
				(*data)(ix + iy*nx) = value;
			else 
				(*data)(ix + iy*nx) = undef_value;
		}
	}

	if (fscanf(file, "%s", buf) == 1)
		goto exit;

	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = new d_grid(minx, maxx, stepX,
			 miny, maxy, stepY);

	res = create_surf(data, grd);

	fclose(file);

	if (surfname)
		res->setName(surfname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;

exit:
	writelog(LOG_ERROR, "surf_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	delete grd;
	fclose(file);
	return NULL;
};

bool _surf_save_grd(const d_surf * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_grd : no surf loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to file %s (grd-ASCII)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to file %s (grd-ASCII)", filename);

	fprintf(f,"DSAA\n");
	int nx = srf->getCountX();
	int ny = srf->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", srf->grd->startX, srf->grd->endX);
	fprintf(f,"%lf %lf\n", srf->grd->startY, srf->grd->endY);

	REAL minZ, maxZ;
	srf->getMinMaxZ(minZ, maxZ);
	fprintf(f,"%lf %lf\n", minZ, maxZ);

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
    
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = (*(srf->coeff))( ix + nx*iy );
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

bool _surf_save_xyz(const d_surf * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_xyz : no surf loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to file %s (xyz-ASCII)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to file %s (xyz-ASCII)", filename);

	int nx = srf->getCountX();
	int ny = srf->getCountY();

	int iy, ix;
	int cnt = 0;
	REAL val;
	REAL x_coord, y_coord;
	
    
	for(iy=0; iy<ny; iy++)	{
		for(ix=0; ix<nx; ix++)	{
			srf->getCoordNode(ix, iy, x_coord, y_coord);
			val = (*(srf->coeff))( ix + nx*iy );
			fprintf(f,"%lf %lf %lf \n", x_coord, y_coord, val);
			
		}
	}

	fclose(f);

	return true;
};

d_points * _surf_to_pnts(const d_surf * srf) {
	
	if (!srf->coeff) {
		writelog(LOG_ERROR,"convert_surf_to_pnts : wrong surf - no coeffs");
		return NULL;
	}

	vec * Z = create_vec(*(srf->coeff));

	vec * X = create_vec(srf->coeff->size());
	vec * Y = create_vec(srf->coeff->size());
	
	REAL * X_ptr = X->begin();
	REAL * Y_ptr = Y->begin();

	int i,j;
	for (j = 0; j < srf->getCountY(); j++) {
		for (i = 0; i < srf->getCountX(); i++) {
			srf->getCoordNode(i,j,*X_ptr,*Y_ptr);
			X_ptr++;
			Y_ptr++;
		}
	}

	return create_points(X, Y, Z,
			     srf->getName());
};

//
//
// wavelets section
//
//

bool _surf_decomp(d_surf * srf) {
	if (!srf)
		return false;
	
	return srf->decompose();
};

bool _surf_auto_decomp(d_surf * srf, REAL eps) {
	if (!srf)
		return false;

	return srf->auto_decompose(eps);
};

bool _surf_add_noise(d_surf * srf, REAL std) {
	if (!srf)
		return false;

	return srf->add_noise(std);
};

bool _surf_recons(d_surf * srf) {
	if (!srf)
		return false;

	return srf->reconstruct();
};

bool _surf_full_recons(d_surf * srf) {
	if (!srf)
		return false;

	return srf->full_reconstruct();
};


d_surf * _surf_project(const d_surf * srf, d_grid * grd) {

	int size_x = grd->getCountX();
	int size_y = grd->getCountY();

	vec * coeff = create_vec(size_x*size_y,0,0);  // do not fill this vector
	
	int surf_size = srf->coeff->size();
	int surf_sizeX = srf->getCountX();
	int surf_sizeY = srf->getCountY();

	if (srf->getName())
		writelog(LOG_MESSAGE,"Projecting surf \"%s\" (%d x %d) => (%d x %d)",srf->getName(), surf_sizeX, surf_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting surf (%d x %d) => (%d x %d)", surf_sizeX, surf_sizeY, size_x, size_y);

	{

		REAL x, y;
		int I0, J0, I1, J1;
		REAL value;
		int i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
				
				d_grid * g = srf->grd;
				I0 = (int)floor( (x - g->startX)/g->stepX );
				J0 = (int)floor( (y - g->startY)/g->stepY );

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), surf_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), surf_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), surf_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), surf_sizeY-1);

				srf->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(srf->coeff))(I0 + surf_sizeX*J0);
				z1 = (*(srf->coeff))(I1 + surf_sizeX*J0);
				z2 = (*(srf->coeff))(I1 + surf_sizeX*J1);
				z3 = (*(srf->coeff))(I0 + surf_sizeX*J1);
				
				if (
					(z0 == srf->undef_value) ||
					(z1 == srf->undef_value) ||
					(z2 == srf->undef_value) ||
					(z3 == srf->undef_value) 
					) 
				{
					
					REAL sum = REAL(0);
					int cnt = 0;
					
					if (z0 != srf->undef_value) {
						sum += z0;
						cnt++;
					}
					if (z1 != srf->undef_value) {
						sum += z1;
						cnt++;
					}
					if (z2 != srf->undef_value) {
						sum += z2;
						cnt++;
					}
					if (z3 != srf->undef_value) {
						sum += z3;
						cnt++;
					}
					
					if (cnt == 0) {
						(*coeff)(i + j*size_x) = srf->undef_value;
						continue;
					}

					REAL mean_z = sum/REAL(cnt);
					if (z0 == srf->undef_value)
						z0 = mean_z;
					if (z1 == srf->undef_value)
						z1 = mean_z;
					if (z2 == srf->undef_value)
						z2 = mean_z;
					if (z3 == srf->undef_value)
						z3 = mean_z;
					
				}
				
				delta_x = x - x0;
				delta_y = y - y0;
				
				// первый шаг линейной интерполяции
				REAL z11 = (z2-z1)*delta_y/hY+z1;
				REAL z22 = (z3-z0)*delta_y/hY+z0;
				
				// второй шаг линейной интерполяции
				REAL res = (z11-z22)*delta_x/hX+z22;
								
				(*coeff)(i + j*size_x) = res;
				
								
			}
		}
	}
	
	d_grid * new_grd = new d_grid(grd);
	d_surf * res = create_surf(coeff, new_grd, srf->getName());
	res->undef_value = srf->undef_value;
	return res;
};

d_surf * _surf_project(d_surf * srf, d_grid * grd, grid_line * fault_grd_line) {

	if (!fault_grd_line)
		return _surf_project(srf, grd);

	int size_x = grd->getCountX();
	int size_y = grd->getCountY();

	vec * coeff = create_vec(size_x*size_y,0,0);  // do not fill this vector
	
	int surf_size = srf->coeff->size();
	int surf_sizeX = srf->getCountX();
	int surf_sizeY = srf->getCountY();

	if (srf->getName())
		writelog(LOG_MESSAGE,"Projecting surf \"%s\" (%d x %d) => (%d x %d)",srf->getName(), surf_sizeX, surf_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting surf (%d x %d) => (%d x %d)", surf_sizeX, surf_sizeY, size_x, size_y);

	{

		REAL x, y;
		int I0, J0, I1, J1;
		REAL value;
		int i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);

				x -= grd->stepX/REAL(2);
				y -= grd->stepY/REAL(2);
				
				d_grid * g = srf->grd;
				I0 = (int)floor( (x - g->startX)/g->stepX );
				J0 = (int)floor( (y - g->startY)/g->stepY );

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), surf_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), surf_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), surf_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), surf_sizeY-1);

				srf->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(srf->coeff))(I0 + surf_sizeX*J0);
				z1 = (*(srf->coeff))(I1 + surf_sizeX*J0);
				z2 = (*(srf->coeff))(I1 + surf_sizeX*J1);
				z3 = (*(srf->coeff))(I0 + surf_sizeX*J1);
				
				if (
					(z0 == srf->undef_value) &&
					(z1 == srf->undef_value) &&
					(z2 == srf->undef_value) &&
					(z3 == srf->undef_value) 
				   )
				{
					(*coeff)(i + j*size_x) = srf->undef_value;
				} else {
					
					if (
						(z0 == srf->undef_value) ||
						(z1 == srf->undef_value) ||
						(z2 == srf->undef_value) ||
						(z3 == srf->undef_value) 
						) 
					{
						
						REAL sum = REAL(0);
						int cnt = 0;
								
						if (z0 != srf->undef_value) {
							sum += z0;
							cnt++;
						}
						if (z1 != srf->undef_value) {
							sum += z1;
							cnt++;
						}
						if (z2 != srf->undef_value) {
							sum += z2;
							cnt++;
						}
						if (z3 != srf->undef_value) {
							sum += z3;
							cnt++;
						}

						REAL mean_z = sum/REAL(cnt);
						if (z0 == srf->undef_value)
							z0 = mean_z;
						if (z1 == srf->undef_value)
							z1 = mean_z;
						if (z2 == srf->undef_value)
							z2 = mean_z;
						if (z3 == srf->undef_value)
							z3 = mean_z;

					}
					
					delta_x = x - x0;
					delta_y = y - y0;

					if ( check_for_pair(fault_grd_line,
						                I1 + J0*surf_sizeX, 
						                I1 + J1*surf_sizeX) )
					{
						if (delta_y < srf->grd->stepY/REAL(2))
							z2 = z1;
						else
							z1 = z2;
					}

					if ( check_for_pair(fault_grd_line,
						                I0 + J0*surf_sizeX, 
						                I0 + J1*surf_sizeX) )
					{
						if (delta_y < srf->grd->stepY/REAL(2))
							z3 = z0;
						else
							z0 = z3;
					}

					// first step of linear interpolation
					REAL z11 = (z2-z1)*delta_y/hY+z1,
						 z22 = (z3-z0)*delta_y/hY+z0;

					if ( check_for_pair(fault_grd_line,
						                I0 + J0*surf_sizeX,
										I1 + J0*surf_sizeX)
						 ||
						 check_for_pair(fault_grd_line,
						                I0 + J1*surf_sizeX,
										I1 + J1*surf_sizeX)
										) 
					{
						if (delta_x < srf->grd->stepX/REAL(2))
							(*coeff)(i + j*size_x) = z22;
						else
							(*coeff)(i + j*size_x) = z11;
					} else {
						
						// second step of linear interpolation
						REAL Res = (z11-z22)*delta_x/hX+z22;
						(*coeff)(i + j*size_x) = Res;
					}
				}
			}
		}
	}
	
	d_grid * new_grd = new d_grid(grd);
	d_surf * res = create_surf(coeff, new_grd, srf->getName());
	res->undef_value = srf->undef_value;
	return res;
};

void _surf_info(const d_surf * srf) {
	if (!srf)
		return;
	if (srf->getName()) 
		writelog(LOG_MESSAGE,"surf (%s) : size=(%d x %d)", srf->getName(), srf->getCountX(), srf->getCountY());
	else 
		writelog(LOG_MESSAGE,"surf noname : size=(%d x %d)", srf->getCountX(), srf->getCountY());
};

bool _surf_resid(const d_surf * srf, const d_points * pnts, const char * filename) {
	if (!srf)
		return false;
	if (!pnts)
		return false;

	if (pnts->size() == 0)
		return false;

	writelog(LOG_MESSAGE, "Calcualting residuals...");

	FILE * f = fopen(filename, "w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	int pnts_size = pnts->size();
	int cnt;
	REAL res;
	REAL x,y,z;

	REAL maxres = -FLT_MAX;

	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();

	for (cnt = 0; cnt < pnts_size; cnt++) {
		x = *(x_ptr + cnt);
		y = *(y_ptr + cnt);
		z = *(z_ptr + cnt);
		res = srf->getValue(x,y) - z;
		maxres = (REAL)MAX(fabs(res),maxres);
		fprintf(f,"%lf \t %lf \t %lf %lf\n",x,y,z,res);
	}
	
	fclose(f);
	writelog(LOG_MESSAGE,"max residual : %lf", maxres);

	return true;

};

REAL _surf_D1(const d_surf * srf) {

	int i,j;
	int NN = srf->getCountX();
	int MM = srf->getCountY();

	REAL * ptr = srf->coeff->begin();

	REAL v1, v2;

	REAL dx = 0;
	int dx_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			if ((v1 != srf->undef_value) && (v2 != srf->undef_value)) {
				dx += (v2-v1)*(v2-v1);
				dx_cnt++;
			}
		}
	}

	dx /= REAL(dx_cnt);

	REAL dy = 0;
	int dy_cnt = 0;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-2; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + i + (j+1)*NN);
			if ((v1 != srf->undef_value) && (v2 != srf->undef_value)) {
				dy += (v2-v1)*(v2-v1);
				dy_cnt++;
			}
		}
	}

	dy /= REAL(dy_cnt);

	REAL h_x_2 = (srf->grd->stepX)*(srf->grd->stepX);
	REAL h_y_2 = (srf->grd->stepY)*(srf->grd->stepY);

	REAL res = dx/h_x_2 + dy/h_y_2;

	return res;

};

REAL _surf_D2(const d_surf * srf) {

	int i,j;
	int NN = srf->getCountX();
	int MM = srf->getCountY();

	REAL * ptr = srf->coeff->begin();

	REAL v1, v2, v3, v4;

	REAL dx2 = 0;
	int dx2_cnt = 0;
	for (i = 0; i < NN-3; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + (i+2) + j*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value)) {
				dx2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dx2_cnt++;
			}
		}
	}

	REAL dxdy = 0;
	int dxdy_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-2; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + i + (j+1)*NN);
			v4 = *(ptr + (i+1) + (j+1)*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value) && 
				(v4 != srf->undef_value) ) {
				dxdy += (v4-v3-v2+v1)*(v4-v3-v2+v1);
				dxdy_cnt++;
			}
		}
	}

	REAL dy2 = 0;
	int dy2_cnt = 0;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-3; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + i + (j+1)*NN);
			v3 = *(ptr + i + (j+2)*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value)) {
				dy2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dy2_cnt++;
			}
		}
	}

	REAL h_x_2 = (srf->grd->stepX)*(srf->grd->stepX);
	REAL h_y_2 = (srf->grd->stepY)*(srf->grd->stepY);
	writelog(LOG_DEBUG,"h_x_2 = %lf    h_y_2 = %lf",h_x_2, h_y_2);
	writelog(LOG_DEBUG,"dx2_cnt = %d dy2_cnt = %d dxdy_cnt = %d",dx2_cnt, dy2_cnt, dxdy_cnt);
	writelog(LOG_DEBUG,"dx2  = %lf",dx2);
	writelog(LOG_DEBUG,"dy2  = %lf",dy2);
	writelog(LOG_DEBUG,"dxdy = %lf",dxdy);

	dx2 /= REAL(dx2_cnt);
	dxdy /= REAL(dxdy_cnt);
	dy2 /= REAL(dy2_cnt);

	REAL res = dx2/(h_x_2*h_x_2) + 2*dxdy/(h_x_2*h_y_2) + dy2/(h_y_2*h_y_2);

	return res;
};

void _add_surfit_surfs(d_surf * srf) {
	if (!srf)
		return;
	surfit_surfs->push_back(srf);
};

d_surf * _surf_gradient(const d_surf * srf) {
	
	int NN = srf->getCountX();
	int MM = srf->getCountY();

	bool first_x, second_x;
	bool first_y, second_y;

	vec * coeff = create_vec(NN*MM);

	int i, j, pos, pos1;
	REAL val;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			
			first_x = true;
			second_x = true;
			first_y = true;
			second_y = true;

			if (i == 0)
				second_x = false;
			if (i == NN-1)
				first_x = false;
			if (j == 0)
				second_y = false;
			if (j == MM-1)
				first_y = false;

			pos = i + j*NN;
			REAL pos_val = (*(srf->coeff))(pos);
			if (pos_val == srf->undef_value) {
				(*(coeff))(pos) = srf->undef_value;
				continue;
			}
			REAL pos1_val;

			val = REAL(0);

			if (first_x) {
				pos1 = (i+1) + j*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_x) {
				pos1 = (i-1) + j*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			if (first_y) {
				pos1 = (i) + (j+1)*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_y) {
				pos1 = i + (j-1)*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			(*(coeff))(pos) = val;
			
		}
	}

	d_grid * grd = new d_grid(srf->grd);
	d_surf * res = create_surf(coeff, grd, srf->getName());
	return res;

};

d_grid * adopt_surf_grid(const d_surf * srf, d_grid * grd,
			 int & from_x, int & to_x,
			 int & from_y, int & to_y) {

	REAL g_x0, g_xn, g_y0, g_yn; // Начало и конец геометрии
	REAL f_x0, f_xn, f_y0, f_yn; // Начало и конец функции
	REAL x0, xn, y0, yn;     // Реальные начало и конец

	grd->getCoordNode(0,0, g_x0, g_y0);
	grd->getCoordNode(grd->getCountX()-1, grd->getCountY()-1, g_xn, g_yn);

	srf->getCoordNode(0,0, f_x0, f_y0);
	srf->getCoordNode(srf->getCountX()-1,srf->getCountY()-1, f_xn, f_yn);
	
	
	x0 = MAX(g_x0, f_x0);
	xn = MIN(g_xn, f_xn);
	y0 = MAX(g_y0, f_y0);
	yn = MIN(g_yn, f_yn);

	if (x0 >= xn)
		return NULL;
	
	if (y0 >= yn)
		return NULL;

	REAL grd_x, grd_y;
	
	int i0 = grd->get_i(x0);
	grd->getCoordNode(i0, 0, grd_x, grd_y);
	if (grd_x < x0)
		i0++;

	int in = grd->get_i(xn);
	grd->getCoordNode(in, 0, grd_x, grd_y);
	if (grd_x > xn)
		in--;

	int j0 = grd->get_j(y0);
	grd->getCoordNode(0, j0, grd_x, grd_y);
	if (grd_y < y0)
		j0++;

	int jn = grd->get_j(yn);
	grd->getCoordNode(0, jn, grd_x, grd_y);
	if (grd_y > yn)
		jn--;

	from_x = i0;
	to_x = in;
	from_y = j0;
	to_y = jn;

	grd->getCoordNode(i0,j0,x0,y0);
	grd->getCoordNode(in,jn,xn,yn);
	
	d_grid * new_geom = new d_grid(x0, xn, grd->stepX, y0, yn, grd->stepY);
	return new_geom;

};

REAL _surf_mean_area(const d_surf * srf, const d_area * area) {
	
	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return srf->undef_value;
	
	int i, N = 0;
	REAL sum = 0;
	REAL value;
	for (i = 0; i < mask->size(); i++) {

		if (mask->get(i) == false)
			continue;
		
		value = (*(srf->coeff))(i); 
		
		if (value == srf->undef_value)
			continue;

		sum += value;
		N++;
	}

	if (mask)
		mask->release();
	if (N == 0)
		return srf->undef_value;

	return sum/REAL(N);
	
};

REAL _surf_wmean_area(const d_surf * srf, const d_surf * wsrf, const d_area * area) {
	
	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	
	int i;
	
	if (mask == NULL) 
		return srf->undef_value;
	
	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	_grid_intersect1(srf->grd, wsrf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_grid * aux_grid = _create_sub_grid(srf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_surf * w_srf = _surf_project(wsrf, aux_grid);
	int nn = aux_grid->getCountX();
	int mm = aux_grid->getCountY();
	int NN = srf->getCountX();
	int MM = srf->getCountY();
	
	delete aux_grid;

	REAL denom = 0;
	int ii, jj;
	REAL sum = 0;
	REAL value;
	for (i = 0; i < mask->size(); i++) {

		if (mask->get(i) == false)
			continue;
		
		value = (*(srf->coeff))(i);
		if (value == srf->undef_value)
			continue;

		REAL weight = 0;

		one2two(i, ii, jj, NN, MM);

		if ((ii >= aux_X_from) && (ii <= aux_X_to) && (jj >= aux_Y_from) && (jj <= aux_Y_to)) {
			int I = ii-aux_X_from;
			int J = jj-aux_Y_from;
			weight = (*(w_srf->coeff))(I + J*nn);
			if (weight == w_srf->undef_value)
				weight = 0;
		}

		if (weight <= 0)
			continue;

		sum += value*weight;
		denom += weight;
	}

	if (w_srf)
		w_srf->release();
	if (mask)
		mask->release();

	return sum/denom;
	
};

REAL _surf_sum_area(const d_surf * srf, const d_area * area) {

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return 0;

	unsigned int i;

	REAL sum = 0;
	REAL value;
	for (i = 0; i < (unsigned int)mask->size(); i++) {
		
		if (mask->get(i) == false)
			continue;

		value = (*(srf->coeff))(i);
		if (value == srf->undef_value)
			continue;

		sum += value;
	}

	if (mask)
		mask->release();
	return sum;	

};

int _surf_cells_in_area(const d_surf * srf, const d_area * area) {

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return 0;
	int res = mask->true_size();
	if (mask)
		mask->release();
	return res;
	
};

void _surfit_surf_add(d_surf * srf) {
	surfit_surfs->push_back(srf);
};


}; // namespace surfit;



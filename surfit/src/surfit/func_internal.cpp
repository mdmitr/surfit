
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

#include "func.h"
#include "func_internal.h"
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

d_func * _func_load_df(datafile * df, const char * funcname) {

	if (!funcname) 
		writelog(LOG_MESSAGE,"loading func with no name from file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"loading func \"%s\" from file %s",funcname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "func_load : wrong datafile format";

	bool err = false;
	d_func * fnc = NULL;
	vec * icoeff = NULL;
	d_grid * grd = NULL;
	char * name = NULL;
	REAL undef_value = FLT_MAX;

	vec * coeff = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("func")) {
			
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
			writelog(LOG_ERROR,"func_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(LOG_ERROR,"func_load : empty geometry");
			err = true;
		}
		
		if (err) {
			if (coeff)
				coeff->release();
			delete grd;
			free(name);
			return false;
		}
		
		fnc = create_func(coeff, grd, name);
		fnc->undef_value = undef_value;
		free(name);
		
		if (!funcname) {
			return fnc;
		} else {
			if (fnc->getName()) {
				if (strcmp(fnc->getName(),funcname) == 0) {
					return fnc;
				}
			}
			if (fnc)
				fnc->release();
			fnc = NULL;
		}
		
	}
	
	return fnc;

exit:

	if (!funcname)
		writelog(LOG_ERROR, "func_load : this file have no func");
	else 
		writelog(LOG_ERROR, "func_load : this file have no func named %s", funcname);
	return NULL;

};

d_func * _func_load(const char * filename, const char * funcname) {

	datafile * df = new datafile(filename, DF_MODE_READ); // read

	d_func * res = _func_load_df(df, funcname);

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
	
bool _func_save(const d_func * fnc, const char * filename) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	res = _func_save_df(fnc, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _func_save_df(const d_func * fnc, datafile * df) {

	if (!fnc->getName()) 
		writelog(LOG_MESSAGE,"saving func with no name to file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"saving func \"%s\" to file %s",fnc->getName(),df->get_filename());
		
	bool res = true;
	bool op;
	
	op = fnc->writeTags(df);           res = ( op && res );
	
	return res;
};

d_func * _func_load_grd(const char * filename, const char * funcname) 
{
	writelog(LOG_MESSAGE, "loading surface from Surfer GRD-ASCII format file %s",filename);

	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(LOG_ERROR, "func_load_grd : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	int nx, ny;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	d_grid * grd = NULL;
	d_func * res = NULL;
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

	res = create_func(data, grd);

	fclose(file);

	if (funcname)
		res->setName(funcname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;

exit:
	writelog(LOG_ERROR, "func_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	delete grd;
	fclose(file);
	return NULL;
};

bool _func_save_grd(const d_func * fnc, const char * filename) {

	if (!filename)
		return false;

	if (!fnc) {
		writelog(LOG_ERROR,"func_save_grd : no func loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (fnc->getName())
		writelog(LOG_MESSAGE,"Saving func %s to file %s (grd-ASCII)", fnc->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving func (noname) to file %s (grd-ASCII)", filename);

	fprintf(f,"DSAA\n");
	int nx = fnc->getCountX();
	int ny = fnc->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", fnc->grd->startX, fnc->grd->endX);
	fprintf(f,"%lf %lf\n", fnc->grd->startY, fnc->grd->endY);

	REAL minZ, maxZ;
	fnc->getMinMaxZ(minZ, maxZ);
	fprintf(f,"%lf %lf\n", minZ, maxZ);

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
    
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = (*(fnc->coeff))( ix + nx*iy );
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

bool _func_save_xyz(const d_func * fnc, const char * filename) {

	if (!filename)
		return false;

	if (!fnc) {
		writelog(LOG_ERROR,"func_save_xyz : no func loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (fnc->getName())
		writelog(LOG_MESSAGE,"Saving func %s to file %s (xyz-ASCII)", fnc->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving func (noname) to file %s (xyz-ASCII)", filename);

	int nx = fnc->getCountX();
	int ny = fnc->getCountY();

	int iy, ix;
	int cnt = 0;
	REAL val;
	REAL x_coord, y_coord;
	
    
	for(iy=0; iy<ny; iy++)	{
		for(ix=0; ix<nx; ix++)	{
			fnc->getCoordNode(ix, iy, x_coord, y_coord);
			val = (*(fnc->coeff))( ix + nx*iy );
			fprintf(f,"%lf %lf %lf \n", x_coord, y_coord, val);
			
		}
	}

	fclose(f);

	return true;
};

d_points * _func_to_pnts(const d_func * fnc) {
	
	if (!fnc->coeff) {
		writelog(LOG_ERROR,"convert_func_to_pnts : wrong func - no coeffs");
		return NULL;
	}

	vec * Z = create_vec(*(fnc->coeff));

	vec * X = create_vec(fnc->coeff->size());
	vec * Y = create_vec(fnc->coeff->size());
	
	REAL * X_ptr = X->begin();
	REAL * Y_ptr = Y->begin();

	int i,j;
	for (j = 0; j < fnc->getCountY(); j++) {
		for (i = 0; i < fnc->getCountX(); i++) {
			fnc->getCoordNode(i,j,*X_ptr,*Y_ptr);
			X_ptr++;
			Y_ptr++;
		}
	}

	return create_points(X, Y, Z,
			     fnc->getName());
};

//
//
// wavelets section
//
//

bool _func_decomp(d_func * fnc) {
	if (!fnc)
		return false;
	
	return fnc->decompose();
};

bool _func_auto_decomp(d_func * fnc, REAL eps) {
	if (!fnc)
		return false;

	return fnc->auto_decompose(eps);
};

bool _func_add_noise(d_func * fnc, REAL std) {
	if (!fnc)
		return false;

	return fnc->add_noise(std);
};

bool _func_recons(d_func * fnc) {
	if (!fnc)
		return false;

	return fnc->reconstruct();
};

bool _func_full_recons(d_func * fnc) {
	if (!fnc)
		return false;

	return fnc->full_reconstruct();
};


d_func * _func_project(const d_func * fnc, d_grid * grd) {

	int size_x = grd->getCountX();
	int size_y = grd->getCountY();

	vec * coeff = create_vec(size_x*size_y,0,0);  // do not fill this vector
	
	int func_size = fnc->coeff->size();
	int func_sizeX = fnc->getCountX();
	int func_sizeY = fnc->getCountY();

	if (fnc->getName())
		writelog(LOG_MESSAGE,"Projecting func \"%s\" (%d x %d) => (%d x %d)",fnc->getName(), func_sizeX, func_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting func (%d x %d) => (%d x %d)", func_sizeX, func_sizeY, size_x, size_y);

	{

		REAL x, y;
		int I0, J0, I1, J1;
		REAL value;
		int i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = fnc->grd->stepX;
		REAL hY = fnc->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
				
				d_grid * g = fnc->grd;
				I0 = (int)floor( (x - g->startX)/g->stepX );
				J0 = (int)floor( (y - g->startY)/g->stepY );

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), func_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), func_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), func_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), func_sizeY-1);

				fnc->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(fnc->coeff))(I0 + func_sizeX*J0);
				z1 = (*(fnc->coeff))(I1 + func_sizeX*J0);
				z2 = (*(fnc->coeff))(I1 + func_sizeX*J1);
				z3 = (*(fnc->coeff))(I0 + func_sizeX*J1);
				
				if (
					(z0 == fnc->undef_value) ||
					(z1 == fnc->undef_value) ||
					(z2 == fnc->undef_value) ||
					(z3 == fnc->undef_value) 
					) 
				{
					
					REAL sum = REAL(0);
					int cnt = 0;
					
					if (z0 != fnc->undef_value) {
						sum += z0;
						cnt++;
					}
					if (z1 != fnc->undef_value) {
						sum += z1;
						cnt++;
					}
					if (z2 != fnc->undef_value) {
						sum += z2;
						cnt++;
					}
					if (z3 != fnc->undef_value) {
						sum += z3;
						cnt++;
					}
					
					if (cnt == 0) {
						(*coeff)(i + j*size_x) = fnc->undef_value;
						continue;
					}

					REAL mean_z = sum/REAL(cnt);
					if (z0 == fnc->undef_value)
						z0 = mean_z;
					if (z1 == fnc->undef_value)
						z1 = mean_z;
					if (z2 == fnc->undef_value)
						z2 = mean_z;
					if (z3 == fnc->undef_value)
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
	d_func * res = create_func(coeff, new_grd, fnc->getName());
	res->undef_value = fnc->undef_value;
	return res;
};

d_func * _func_project_with_faults(const d_func * fnc, d_grid * grd) {

	grid_line * fault_grd_line = NULL;
	grid_line * fault_grd_line2 = NULL;

	int i;
	for (i = 0; i < (int)surfit_curvs->size(); i++) {
		d_curv * crv = (*surfit_curvs)[i];
		fault_grd_line = curv_to_grid_line(fault_grd_line, crv, fnc->grd);
		fault_grd_line2 = curv_to_grid_line(fault_grd_line2, crv, grd);
	};

	if (!fault_grd_line) {
		if (fault_grd_line2)
			fault_grd_line2->release();
		return _func_project(fnc, grd);
	}

	//_grid_line_write(fault_grd_line, fnc->grd, "c:\\fault_1.ctr","%g, %g\n");
	//_grid_line_write(fault_grd_line2, grd, "c:\\fault_2.ctr","%g, %g\n");
	
	int size_x = grd->getCountX();
	int size_y = grd->getCountY();

	vec * coeff = create_vec(size_x*size_y,0,0);  // do not fill this vector
	
	int func_size = fnc->coeff->size();
	int func_sizeX = fnc->getCountX();
	int func_sizeY = fnc->getCountY();

	if (fnc->getName())
		writelog(LOG_MESSAGE,"Projecting func \"%s\" (%d x %d) => (%d x %d)",fnc->getName(), func_sizeX, func_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting func (%d x %d) => (%d x %d)", func_sizeX, func_sizeY, size_x, size_y);

	{

		REAL x, y;
		int I0, J0, I1, J1;
		REAL value;
		int i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = fnc->grd->stepX;
		REAL hY = fnc->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);

				d_grid * g = fnc->grd;
				I0 = (int)floor( (x - g->startX)/g->stepX );
				J0 = (int)floor( (y - g->startY)/g->stepY );

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), func_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), func_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), func_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), func_sizeY-1);

				fnc->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(fnc->coeff))(I0 + func_sizeX*J0);
				z1 = (*(fnc->coeff))(I1 + func_sizeX*J0);
				z2 = (*(fnc->coeff))(I1 + func_sizeX*J1);
				z3 = (*(fnc->coeff))(I0 + func_sizeX*J1);
				
				if (
					(z0 == fnc->undef_value) &&
					(z1 == fnc->undef_value) &&
					(z2 == fnc->undef_value) &&
					(z3 == fnc->undef_value) 
				   )
				{
					(*coeff)(i + j*size_x) = fnc->undef_value;
				} else {
					
					if (
						(z0 == fnc->undef_value) ||
						(z1 == fnc->undef_value) ||
						(z2 == fnc->undef_value) ||
						(z3 == fnc->undef_value) 
						) 
					{
						
						REAL sum = REAL(0);
						int cnt = 0;
								
						if (z0 != fnc->undef_value) {
							sum += z0;
							cnt++;
						}
						if (z1 != fnc->undef_value) {
							sum += z1;
							cnt++;
						}
						if (z2 != fnc->undef_value) {
							sum += z2;
							cnt++;
						}
						if (z3 != fnc->undef_value) {
							sum += z3;
							cnt++;
						}

						REAL mean_z = sum/REAL(cnt);
						if (z0 == fnc->undef_value)
							z0 = mean_z;
						if (z1 == fnc->undef_value)
							z1 = mean_z;
						if (z2 == fnc->undef_value)
							z2 = mean_z;
						if (z3 == fnc->undef_value)
							z3 = mean_z;

					}
					
					delta_x = x - x0;
					delta_y = y - y0;

					// 
					if ( check_for_pair(fault_grd_line,
						            I1 + J0*func_sizeX, 
						            I1 + J1*func_sizeX) )
					{
						if (delta_y < fnc->grd->stepY/REAL(2)) {
							if ( check_for_pair(fault_grd_line2,
									    i + j*size_x,
									    i + (j-1)*size_x) )
								z1 = z2;
							else
								z2 = z1;
						} else {
							if ( check_for_pair(fault_grd_line2,
									    i + (j+1)*size_x,
									    i + j*size_x) )
								z2 = z1;
							else
								z1 = z2;
						}
					
					}

					if ( check_for_pair(fault_grd_line,
						                I0 + J0*func_sizeX, 
						                I0 + J1*func_sizeX) )
					{
						if (delta_y < fnc->grd->stepY/REAL(2)) {
							if ( check_for_pair(fault_grd_line2,
									    i + j*size_x,
									    i + (j-1)*size_x) )
								z0 = z3;
							else
								z3 = z0;
						} else {
							if ( check_for_pair(fault_grd_line2,
									    i + (j+1)*size_x,
									    i + j*size_x) )
								z3 = z0;
							else
								z0 = z3;
						}
					}

					// first step of linear interpolation
					REAL z11 = (z2-z1)*delta_y/hY+z1,
					     z22 = (z3-z0)*delta_y/hY+z0;

					if ( check_for_pair(fault_grd_line,
						            I0 + J0*func_sizeX,
							    I1 + J0*func_sizeX)
					 ||
					     check_for_pair(fault_grd_line,
					                    I0 + J1*func_sizeX,
					                    I1 + J1*func_sizeX)
					   ) 
					{
						if (delta_x < fnc->grd->stepX/REAL(2)) {
							if ( check_for_pair(fault_grd_line2,
									    i + j*size_x,
									    (i-1) + j*size_x) )
								(*coeff)(i + j*size_x) = z11;
							else 
								(*coeff)(i + j*size_x) = z22;
						} else {
							if ( check_for_pair(fault_grd_line2,
									    (i+1) + j*size_x,
									    i + j*size_x) )
								(*coeff)(i + j*size_x) = z22;
							else 
								(*coeff)(i + j*size_x) = z11;
						}
					} else {
						
						// second step of linear interpolation
						REAL Res = (z11-z22)*delta_x/hX+z22;
						(*coeff)(i + j*size_x) = Res;
					}
				}
			}
		}
	}
	
	if (fault_grd_line)
		fault_grd_line->release();
	
	if (fault_grd_line2)
		fault_grd_line2->release();

	d_grid * new_grd = new d_grid(grd);
	d_func * res = create_func(coeff, new_grd, fnc->getName());
	res->undef_value = fnc->undef_value;
	return res;
};

d_func * _func_project(d_func * fnc, d_grid * grd, grid_line * fault_grd_line) {

	if (!fault_grd_line)
		return _func_project(fnc, grd);

	int size_x = grd->getCountX();
	int size_y = grd->getCountY();

	vec * coeff = create_vec(size_x*size_y,0,0);  // do not fill this vector
	
	int func_size = fnc->coeff->size();
	int func_sizeX = fnc->getCountX();
	int func_sizeY = fnc->getCountY();

	if (fnc->getName())
		writelog(LOG_MESSAGE,"Projecting func \"%s\" (%d x %d) => (%d x %d)",fnc->getName(), func_sizeX, func_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting func (%d x %d) => (%d x %d)", func_sizeX, func_sizeY, size_x, size_y);

	{

		REAL x, y;
		int I0, J0, I1, J1;
		REAL value;
		int i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = fnc->grd->stepX;
		REAL hY = fnc->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);

				x -= grd->stepX/REAL(2);
				y -= grd->stepY/REAL(2);
				
				d_grid * g = fnc->grd;
				I0 = (int)floor( (x - g->startX)/g->stepX );
				J0 = (int)floor( (y - g->startY)/g->stepY );

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), func_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), func_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), func_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), func_sizeY-1);

				fnc->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(fnc->coeff))(I0 + func_sizeX*J0);
				z1 = (*(fnc->coeff))(I1 + func_sizeX*J0);
				z2 = (*(fnc->coeff))(I1 + func_sizeX*J1);
				z3 = (*(fnc->coeff))(I0 + func_sizeX*J1);
				
				if (
					(z0 == fnc->undef_value) &&
					(z1 == fnc->undef_value) &&
					(z2 == fnc->undef_value) &&
					(z3 == fnc->undef_value) 
				   )
				{
					(*coeff)(i + j*size_x) = fnc->undef_value;
				} else {
					
					if (
						(z0 == fnc->undef_value) ||
						(z1 == fnc->undef_value) ||
						(z2 == fnc->undef_value) ||
						(z3 == fnc->undef_value) 
						) 
					{
						
						REAL sum = REAL(0);
						int cnt = 0;
								
						if (z0 != fnc->undef_value) {
							sum += z0;
							cnt++;
						}
						if (z1 != fnc->undef_value) {
							sum += z1;
							cnt++;
						}
						if (z2 != fnc->undef_value) {
							sum += z2;
							cnt++;
						}
						if (z3 != fnc->undef_value) {
							sum += z3;
							cnt++;
						}

						REAL mean_z = sum/REAL(cnt);
						if (z0 == fnc->undef_value)
							z0 = mean_z;
						if (z1 == fnc->undef_value)
							z1 = mean_z;
						if (z2 == fnc->undef_value)
							z2 = mean_z;
						if (z3 == fnc->undef_value)
							z3 = mean_z;

					}
					
					delta_x = x - x0;
					delta_y = y - y0;

					if ( check_for_pair(fault_grd_line,
						                I1 + J0*func_sizeX, 
						                I1 + J1*func_sizeX) )
					{
						if (delta_y < fnc->grd->stepY/REAL(2))
							z2 = z1;
						else
							z1 = z2;
					}

					if ( check_for_pair(fault_grd_line,
						                I0 + J0*func_sizeX, 
						                I0 + J1*func_sizeX) )
					{
						if (delta_y < fnc->grd->stepY/REAL(2))
							z3 = z0;
						else
							z0 = z3;
					}

					// first step of linear interpolation
					REAL z11 = (z2-z1)*delta_y/hY+z1,
						 z22 = (z3-z0)*delta_y/hY+z0;

					if ( check_for_pair(fault_grd_line,
						                I0 + J0*func_sizeX,
										I1 + J0*func_sizeX)
						 ||
						 check_for_pair(fault_grd_line,
						                I0 + J1*func_sizeX,
										I1 + J1*func_sizeX)
										) 
					{
						if (delta_x < fnc->grd->stepX/REAL(2))
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
	d_func * res = create_func(coeff, new_grd, fnc->getName());
	res->undef_value = fnc->undef_value;
	return res;
};

void _func_info(const d_func * fnc) {
	if (!fnc)
		return;
	if (fnc->getName()) 
		writelog(LOG_MESSAGE,"func (%s) : size=(%d x %d)", fnc->getName(), fnc->getCountX(), fnc->getCountY());
	else 
		writelog(LOG_MESSAGE,"func noname : size=(%d x %d)", fnc->getCountX(), fnc->getCountY());
};

bool _func_resid(const d_func * fnc, const d_points * pnts, const char * filename) {
	if (!fnc)
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
		res = fnc->getValue(x,y) - z;
		maxres = (REAL)MAX(fabs(res),maxres);
		fprintf(f,"%lf \t %lf \t %lf %lf\n",x,y,z,res);
	}
	
	fclose(f);
	writelog(LOG_MESSAGE,"max residual : %lf", maxres);

	return true;

};

REAL _func_D1(const d_func * fnc) {

	int i,j;
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();

	REAL * ptr = fnc->coeff->begin();

	REAL v1, v2;

	REAL dx = 0;
	int dx_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			if ((v1 != fnc->undef_value) && (v2 != fnc->undef_value)) {
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
			if ((v1 != fnc->undef_value) && (v2 != fnc->undef_value)) {
				dy += (v2-v1)*(v2-v1);
				dy_cnt++;
			}
		}
	}

	dy /= REAL(dy_cnt);

	REAL h_x_2 = (fnc->grd->stepX)*(fnc->grd->stepX);
	REAL h_y_2 = (fnc->grd->stepY)*(fnc->grd->stepY);

	REAL res = dx/h_x_2 + dy/h_y_2;

	return res;

};

REAL _func_D2(const d_func * fnc) {

	int i,j;
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();

	REAL * ptr = fnc->coeff->begin();

	REAL v1, v2, v3, v4;

	REAL dx2 = 0;
	int dx2_cnt = 0;
	for (i = 0; i < NN-3; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + (i+2) + j*NN);
			if ((v1 != fnc->undef_value) && 
				(v2 != fnc->undef_value) && 
				(v3 != fnc->undef_value)) {
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
			if ((v1 != fnc->undef_value) && 
				(v2 != fnc->undef_value) && 
				(v3 != fnc->undef_value) && 
				(v4 != fnc->undef_value) ) {
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
			if ((v1 != fnc->undef_value) && 
				(v2 != fnc->undef_value) && 
				(v3 != fnc->undef_value)) {
				dy2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dy2_cnt++;
			}
		}
	}

	REAL h_x_2 = (fnc->grd->stepX)*(fnc->grd->stepX);
	REAL h_y_2 = (fnc->grd->stepY)*(fnc->grd->stepY);
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

void _add_surfit_funcs(d_func * fnc) {
	if (!fnc)
		return;
	surfit_funcs->push_back(fnc);
};

d_func * _func_gradient(const d_func * fnc) {
	
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();

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
			REAL pos_val = (*(fnc->coeff))(pos);
			if (pos_val == fnc->undef_value) {
				(*(coeff))(pos) = fnc->undef_value;
				continue;
			}
			REAL pos1_val;

			val = REAL(0);

			if (first_x) {
				pos1 = (i+1) + j*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_x) {
				pos1 = (i-1) + j*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			if (first_y) {
				pos1 = (i) + (j+1)*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_y) {
				pos1 = i + (j-1)*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			(*(coeff))(pos) = val;
			
		}
	}

	d_grid * grd = new d_grid(fnc->grd);
	d_func * res = create_func(coeff, grd, fnc->getName());
	return res;

};

d_grid * adopt_func_grid(const d_func * fnc, d_grid * grd,
			 int & from_x, int & to_x,
			 int & from_y, int & to_y) {

	REAL g_x0, g_xn, g_y0, g_yn; // Начало и конец геометрии
	REAL f_x0, f_xn, f_y0, f_yn; // Начало и конец функции
	REAL x0, xn, y0, yn;     // Реальные начало и конец

	grd->getCoordNode(0,0, g_x0, g_y0);
	grd->getCoordNode(grd->getCountX()-1, grd->getCountY()-1, g_xn, g_yn);

	fnc->getCoordNode(0,0, f_x0, f_y0);
	fnc->getCoordNode(fnc->getCountX()-1,fnc->getCountY()-1, f_xn, f_yn);
	
	
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

REAL _func_mean_area(const d_func * fnc, const d_area * area) {
	
	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return fnc->undef_value;
	
	int i, N = 0;
	REAL sum = 0;
	REAL value;
	for (i = 0; i < mask->size(); i++) {

		if (mask->get(i) == false)
			continue;
		
		value = (*(fnc->coeff))(i); 
		
		if (value == fnc->undef_value)
			continue;

		sum += value;
		N++;
	}

	if (mask)
		mask->release();
	if (N == 0)
		return fnc->undef_value;

	return sum/REAL(N);
	
};

REAL _func_wmean_area(const d_func * fnc, const d_func * wfnc, const d_area * area) {
	
	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	
	int i;
	
	if (mask == NULL) 
		return fnc->undef_value;
	
	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
	_grid_intersect1(fnc->grd, wfnc->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_grid * aux_grid = _create_sub_grid(fnc->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_func * w_fnc = _func_project(wfnc, aux_grid);
	int nn = aux_grid->getCountX();
	int mm = aux_grid->getCountY();
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();
	
	delete aux_grid;

	REAL denom = 0;
	int ii, jj;
	REAL sum = 0;
	REAL value;
	for (i = 0; i < mask->size(); i++) {

		if (mask->get(i) == false)
			continue;
		
		value = (*(fnc->coeff))(i);
		if (value == fnc->undef_value)
			continue;

		REAL weight = 0;

		one2two(i, ii, jj, NN, MM);

		if ((ii >= aux_X_from) && (ii <= aux_X_to) && (jj >= aux_Y_from) && (jj <= aux_Y_to)) {
			int I = ii-aux_X_from;
			int J = jj-aux_Y_from;
			weight = (*(w_fnc->coeff))(I + J*nn);
			if (weight == w_fnc->undef_value)
				weight = 0;
		}

		if (weight <= 0)
			continue;

		sum += value*weight;
		denom += weight;
	}

	if (w_fnc)
		w_fnc->release();
	if (mask)
		mask->release();

	return sum/denom;
	
};

REAL _func_sum_area(const d_func * fnc, const d_area * area) {

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return 0;

	unsigned int i;

	REAL sum = 0;
	REAL value;
	for (i = 0; i < (unsigned int)mask->size(); i++) {
		
		if (mask->get(i) == false)
			continue;

		value = (*(fnc->coeff))(i);
		if (value == fnc->undef_value)
			continue;

		sum += value;
	}

	if (mask)
		mask->release();
	return sum;	

};

int _func_cells_in_area(const d_func * fnc, const d_area * area) {

	bitvec * mask = nodes_in_area_mask(area, fnc->grd);
	if (mask == NULL)
		return 0;
	int res = mask->true_size();
	if (mask)
		mask->release();
	return res;
	
};


}; // namespace surfit;



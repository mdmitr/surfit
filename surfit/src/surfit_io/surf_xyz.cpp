
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

#include "surfit_io_ie.h"
#include "surf_io.h"

// sstuff includes
#include "sstuff.h"
#include "read_txt.h"
#include "geom_alg.h"

// surfit includes
#include "surf.h"
#include "fileio.h"
#include "vec.h"
#include "variables_tcl.h"
#include "grid.h"

#include <errno.h>
#include <float.h>

namespace surfit {

bool _surf_save_xyz(const d_surf * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_xyz : no surf loaded");
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to file %s (xyz-ASCII)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to file %s (xyz-ASCII)", filename);

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s : %s",filename,strerror( errno ));
		return false;
	}

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

d_surf * _surf_load_xyz(const char * filename, const char * surfname) {
	
	writelog(LOG_MESSAGE, "loading surface from XYZ 3 column text file %s",filename);

	d_surf * res = NULL;
	d_grid * grd = NULL;

	vec * X = NULL;
	vec * Y = NULL;
	vec * Z = NULL;
	vec * coeff = NULL;
	size_t i, j;
	size_t pnt_cnt;
	REAL x, y, z;

	REAL dist1, dist2;
	REAL x0, x1, y0, y1;
	REAL cx, cy;
	REAL cos_alpha = 1;
	REAL angle = 0;
	REAL stepX = 0;
	REAL stepY = 0;
	REAL minx = FLT_MAX;
	REAL maxx = -FLT_MAX;
	REAL miny = FLT_MAX;
	REAL maxy = -FLT_MAX;
	int nx = 0, ny = 0;
	int div;
	size_t I, J;
	// loading all points

	if (!three_columns_read(filename, 
				1, 2, 3, 0, "\t, ", 1000, 
				X, Y, Z))
				goto exit;

	if (X == NULL)
		goto exit;
	if (Y == NULL)
		goto exit;
	if (Z == NULL)
		goto exit;

	pnt_cnt = Z->size();

	if (X->size() != pnt_cnt)
		goto exit;
	if (Y->size() != pnt_cnt)
		goto exit;

	// filter bad points
	for (i = pnt_cnt-1; i--;) {
		
		x = (*X)(i);
		y = (*Y)(i);
		z = (*Z)(i);

		if (x >= FLT_MAX / REAL(2)) {
			X->erase(i);
			Y->erase(i);
			Z->erase(i);
			continue;
		}

		if (y >= FLT_MAX / REAL(2)) {
			X->erase(i);
			Y->erase(i);
			Z->erase(i);
			continue;
		}

		if (z >= FLT_MAX / REAL(2)) {
			X->erase(i);
			Y->erase(i);
			Z->erase(i);
			continue;
		}
		
		if (i == 0)
			break;
	}

	pnt_cnt = Z->size();

	// now trying to find the OX axis
	bool founded;
	if (pnt_cnt <= 7)
		goto exit;

	for (i = 0; i < MAX(0,pnt_cnt-7); i++) {
		founded = true;
		x0 = (*X)(i);
		x1 = (*X)(i+1);
		y0 = (*Y)(i);
		y1 = (*Y)(i+1);
		dist1 = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);
		if (dist1 == 0)
			goto exit;
		dist1 = sqrt(dist1);
		for (j = 2; j < 6; j++) {
			x0 = x1;
			y0 = y1;
			x1 = (*X)(i+j);
			y1 = (*Y)(i+j);
			dist2 = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);
			dist2 = sqrt(dist2);
			REAL max_dist = MAX(dist1, dist2);
			if (max_dist)
				if ( fabs(dist1 - dist2) / max_dist > 0.01 ){
					founded = false;
					break;
				}
		}
		if (founded == true)
			break;
	}

	if (founded == false)
		goto exit;

	if (y1 != y0)
		cos_alpha = (x1-x0)/(y1-y0);
	cos_alpha = MAX(-1,MIN(1,cos_alpha));

	angle = REAL(180)*acos(cos_alpha)/3.1415926;

	div = (int)( floor( angle/REAL(90) + 0.5) );
	angle -= div*REAL(90);

	if ( fabs(angle) > 0.01 )
		goto exit;
	
	cx = x0;
	cy = y0;

	if (angle != 0)
		rotate(cx, cy, angle, X->begin(), X->end(), Y->begin(), Y->end());

	for (i = 0; i < pnt_cnt; i++) {
		x = (*X)(i);
		y = (*Y)(i);

		minx = MIN(minx, x);
		maxx = MAX(maxx, x);
		miny = MIN(miny, y);
		maxy = MAX(maxy, y);
	}

	// calculate stepX and stepY

	for (i = 0; i < pnt_cnt-1; i++) {
		x0 = (*X)(i);
		y0 = (*Y)(i);
		for (j = i+1; j < pnt_cnt; j++) {
			x1 = (*X)(j);
			y1 = (*Y)(j);
			if ( (y0 - y1)*(y0 - y1) < dist1/10e+3 ) {
				stepX = fabs(x1 - x0);
				break;
			}
			if ( (x0 - x1)*(x0 - x1) < dist1/10e+3 )
				continue;
		}
		if (stepX != 0)
			break;
	}
	nx = (int)floor( (maxx-minx)/stepX + 0.5 ) + 1;
	stepX = (maxx-minx)/(nx - 1);

	if (nx == 0)
		goto exit;
	if (stepX == 0)
		goto exit;

	for (i = 0; i < pnt_cnt-1; i++) {
		x0 = (*X)(i);
		y0 = (*Y)(i);
		for (j = i+1; j < pnt_cnt; j++) {
			x1 = (*X)(j);
			y1 = (*Y)(j);
			if ( (y0 - y1)*(y0 - y1) < dist1/10e+3 )
				continue;
			if ( (x0 - x1)*(x0 - x1) < dist1/10e+3 ) {
				stepY = fabs(y1 - y0);
				break;
			}
		}
		if (stepY != 0)
			break;
	}
	ny = (int)floor( (maxy-miny)/stepY + 0.5 ) + 1;
	stepY = (maxy-miny)/(ny - 1);
		
	if (ny == 0)
		goto exit;
	if (stepY == 0)
		goto exit;

	coeff = create_vec( nx*ny, undef_value, 1 );
	grd = create_grid(minx, maxx, stepX, miny, maxy, stepY);

	grd->getCoordNode(nx-1, ny-1, maxx, maxy);
	
	if (grd->getCountX() != nx)
		goto exit;

	if (grd->getCountY() != ny)
		goto exit;

	for (i = 0; i < pnt_cnt; i++) {
		x = (*X)(i);
		y = (*Y)(i);
		z = (*Z)(i);
		grd->getCoordPoint(x, y, I, J);
		
		REAL test_x, test_y;
		grd->getCoordNode(I, J, test_x, test_y);

		REAL dist = (test_x - x)*(test_x - x) + (test_y - y)*(test_y - y);
		if (dist > dist1/10e+3)
			goto exit;

		if (I >= nx)
			goto exit;

		if (J >= ny)
			goto exit;

		(*coeff)( I + J*nx ) = z;
	}
	
	if (angle != 0) {
		grd->release();
		grd = create_grid(minx, maxx, stepX, miny, maxy, stepY); // , angle
	}

	res = create_surf(coeff, grd);

	if (surfname)
		res->setName(surfname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;

exit:
	writelog(LOG_ERROR, "surf_load_xyz : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (grd)
		grd->release();
	if (X)
		X->release();
	if (Y)
		Y->release();
	if (Z)
		Z->release();
	if (coeff)
		coeff->release();

	return NULL;
};


};


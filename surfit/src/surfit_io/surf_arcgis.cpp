
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

// surfit includes
#include "surf.h"
#include "fileio.h"
#include "vec.h"
#include "variables_tcl.h"
#include "grid.h"
#include "surf_internal.h"

#include <float.h>
#include <errno.h>

namespace surfit {

d_surf * _surf_load_arcgis(const char * filename, const char * surfname) {
	
	writelog(LOG_MESSAGE, "loading surface from ArcGIS ASCII file %s",filename);

	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(LOG_ERROR, "surf_load_arcgis : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	size_t nx = UINT_MAX, ny = UINT_MAX;
	REAL xllcorner = FLT_MAX;
	REAL yllcorner = FLT_MAX;
	REAL xllcenter = FLT_MAX;
	REAL yllcenter = FLT_MAX;
	REAL step = FLT_MAX;
	d_grid * grd = NULL;
	d_surf * res = NULL;
	vec * data = NULL;
	REAL surf_undef = FLT_MAX;

	REAL minx, maxx, miny, maxy;

	char buf[200];
	char buf2[200];
	
	if ( fread(buf, sizeof(char), 6, file) != 6)
		goto exit;
	buf[6]='\0';
		
	if (strcmp(buf,"ncols ") != 0) 
		goto exit;

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	nx = atoi(buf);
	
	size_t ix, iy;

	while ( true ) 
	{
		if (fscanf(file, "%s", buf) != 1)
			goto exit;

		// if !word
		if ((buf[0] >= '0') && (buf[0] <='9'))
			break;

		if (fscanf(file, "%s", buf2) != 1)
			goto exit;

		if (strcmp(buf, "nrows") == 0) {
			ny = atoi(buf2);
			continue;
		}
		if (strcmp(buf, "xllcorner") == 0) {
			xllcorner = atof(buf2);
			continue;
		}
		if (strcmp(buf, "xllcenter") == 0) {
			xllcenter = atof(buf2);
			continue;
		}
		if (strcmp(buf, "yllcorner") == 0) {
			yllcorner = atof(buf2);
			continue;
		}
		if (strcmp(buf, "yllcenter") == 0) {
			yllcenter = atof(buf2);
			continue;
		}
		if (strcmp(buf, "cellsize") == 0) {
			step = atof(buf2);
			continue;
		}
		if (strcmp(buf, "nodata_value") == 0) {
			surf_undef = atof(buf2);
			continue;
		}
		
	}

	if (nx == UINT_MAX)
		goto exit;
	if (ny == UINT_MAX)
		goto exit;
	if ((xllcorner == FLT_MAX) && (xllcenter == FLT_MAX))
		goto exit;
	if ((yllcorner == FLT_MAX) && (yllcenter == FLT_MAX))
		goto exit;
	if (step == FLT_MAX)
		goto exit;
	
	data = create_vec(nx*ny);
	REAL value;

	for(iy=0; iy<ny; iy++) {
		for(ix=0; ix<nx; ix++) {
			
			value = atof(buf);
			if (value != surf_undef)
				(*data)(ix + (ny-1-iy)*nx) = value;
			else 
				(*data)(ix + (ny-1-iy)*nx) = undef_value;
			
			if (fscanf(file, "%s", buf) != 1)
				break;
	
		}
	}

	if ((iy != ny) || (ix+1 != nx))
		goto exit;

	if (fscanf(file, "%s", buf) == 1)
		goto exit;

	if (xllcenter != FLT_MAX) {
		minx = xllcenter;
		maxx = minx + step*(nx-1);
	} else {
		minx = xllcorner + step/REAL(2);
		maxx = minx + step*(nx-1);
	}

	if (yllcenter != FLT_MAX) {
		miny = yllcenter;
		maxy = miny + step*(ny-1);
	} else {
		miny = yllcorner + step/REAL(2);
		maxy = miny + step*(ny-1);
	}

	grd = create_grid(minx, maxx, step,
			  miny, maxy, step);

	nx = grd->getCountX();
	ny = grd->getCountY();

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
	writelog(LOG_ERROR, "surf_load_arcgis : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	if (grd)
		grd->release();
	fclose(file);
	return NULL;
};

bool _surf_save_arcgis(const d_surf * srf, const char * filename) {
	
	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_arcgis : no surf loaded");
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to ArcGIS ASCII file %s", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to ArcGIS ASCII file %s", filename);

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	int nx = srf->getCountX();
	int ny = srf->getCountY();

	REAL stepX = srf->getStepX();
	REAL stepY = srf->getStepY();

	const d_surf * save_srf = srf;
	d_surf * prj_srf = NULL;

	if (stepX != stepY) {
		d_grid * grd = create_grid(srf->getCoordNodeX(0), srf->getCoordNodeX(nx-1), MIN(stepX,stepY),
					   srf->getCoordNodeY(0), srf->getCoordNodeY(ny-1), MIN(stepX,stepY));

		prj_srf = _surf_project(srf, grd);
		nx = prj_srf->getCountX();
		ny = prj_srf->getCountY();
		if (grd)
			grd->release();
		save_srf = prj_srf;
		stepX = MIN(stepX, stepY);
	}

	REAL x_min = save_srf->getCoordNodeX(0);
	REAL x_max = save_srf->getCoordNodeX(nx-1);
	REAL y_min = save_srf->getCoordNodeY(0);
	REAL y_max = save_srf->getCoordNodeY(ny-1);

	fprintf(f, "ncols %d\n", nx);
	fprintf(f, "nrows %d\n", ny);
	fprintf(f, "xllcenter %g\n",  x_min);
	fprintf(f, "yllcenter %g\n",  y_min);
	fprintf(f, "cellsize %g\n", stepX);
	fprintf(f, "nodata_value %g\n",  save_srf->undef_value);
	
	int i,j;
	for (j = 0; j < ny; j++) {
		for (i = 0; i < nx; i++) {
			fprintf(f,"%g ", save_srf->getValueIJ(i,ny-1-j));
		}
		fprintf(f,"\n");
	}

	fclose(f);

	if (prj_srf)
		prj_srf->release();

	return true;
};

};


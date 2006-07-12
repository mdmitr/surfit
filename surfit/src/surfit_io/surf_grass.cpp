
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

#include <float.h>
#include <errno.h>

namespace surfit {

d_surf * _surf_load_grass(const char * filename, const char * surfname) {
	writelog(LOG_MESSAGE, "loading surface from GRASS ASCII file %s",filename);

	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(LOG_ERROR, "surf_load_grass : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	size_t nx = UINT_MAX, ny = UINT_MAX;
	REAL miny = FLT_MAX, maxy = FLT_MAX;
	REAL minx = FLT_MAX, maxx = FLT_MAX;
	REAL stepX, stepY;
	d_grid * grd = NULL;
	d_surf * res = NULL;
	vec * data = NULL;
	REAL surf_undef = FLT_MAX;

	char buf[200];
	char buf2[200];
	
	if ( fread(buf, sizeof(char), 6, file) != 6)
		goto exit;
	buf[6]='\0';
		
	if (strcmp(buf,"north:") != 0) 
		goto exit;

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxy = atof(buf);
	
	size_t ix, iy;

	while ( true ) 
	{
		if (fscanf(file, "%s", buf) != 1)
			goto exit;
		if (strchr(buf, ':') == NULL)
			break;
		if (fscanf(file, "%s", buf2) != 1)
			goto exit;
		if (strcmp(buf, "south:") == 0) {
			miny = atof(buf2);
			continue;
		}
		if (strcmp(buf, "west:") == 0) {
			minx = atof(buf2);
			continue;
		}
		if (strcmp(buf, "east:") == 0) {
			maxx = atof(buf2);
			continue;
		}
		if (strcmp(buf, "rows:") == 0) {
			ny = atoi(buf2);
			continue;
		}
		if (strcmp(buf, "cols:") == 0) {
			nx = atoi(buf2);
			continue;
		}
		if (strcmp(buf, "null:") == 0) {
			surf_undef = atof(buf2);
			continue;
		}
	}

	if (minx == FLT_MAX)
		goto exit;
	if (maxx == FLT_MAX)
		goto exit;
	if (miny == FLT_MAX)
		goto exit;
	if (maxy == FLT_MAX)
		goto exit;
	if (nx == UINT_MAX)
		goto exit;
	if (ny == UINT_MAX)
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

	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = create_grid(minx, maxx, stepX,
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
	writelog(LOG_ERROR, "surf_load_grass : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	if (grd)
		grd->release();
	fclose(file);
	return NULL;
};

bool _surf_save_grass(const d_surf * srf, const char * filename) {
	
	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_grass : no surf loaded");
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to GRASS ASCII file %s", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to GRASS ASCII file %s", filename);

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	int nx = srf->getCountX();
	int ny = srf->getCountY();

	REAL x_min = srf->getCoordNodeX(0);
	REAL x_max = srf->getCoordNodeX(nx-1);
	REAL y_min = srf->getCoordNodeY(0);
	REAL y_max = srf->getCoordNodeY(ny-1);

	fprintf(f, "north: %g\n", y_max);
	fprintf(f, "south: %g\n", y_min);
	fprintf(f, "east: %g\n",  x_max);
	fprintf(f, "west: %g\n",  x_min);
	fprintf(f, "rows: %d\n",  ny);
	fprintf(f, "cols: %d\n",  nx);
	fprintf(f, "null: %g\n",  srf->undef_value);
	fprintf(f, "type: float\n");

	int i,j;
	for (j = 0; j < ny; j++) {
		for (i = 0; i < nx; i++) {
			fprintf(f,"%g ", srf->getValueIJ(i,ny-1-j));
		}
		fprintf(f,"\n");
	}

	fclose(f);

	return true;
};

};


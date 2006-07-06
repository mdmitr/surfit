
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

#include "threads.h"

#include <math.h>
#include <float.h>
#include <errno.h>

#ifdef HAVE_NETCDF
#include <netcdf.h>
#endif

#ifdef HAVE_LIBJPEG
extern "C" {
#include <windows.h>
#include <jpeglib.h>
};
#endif

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
			if (grd)
				grd->release();
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
	writelog(LOG_ERROR, "surf_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	if (grd)
		grd->release();
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

#ifdef HAVE_NETCDF
static const schar ncmagic[] = {'C', 'D', 'F', 0x01};

bool check_nc_status (int status)
{
	if (status != NC_NOERR) {
		writelog(LOG_ERROR,"%s", nc_strerror(status));
		return false;
	}
	
	return true;
}

#define GRD_COMMAND_LEN	320
#define GRD_REMARK_LEN	160
#define GRD_TITLE_LEN	 80
#define GRD_UNIT_LEN	 80

struct GRD_HEADER {
	int nx;				// Number of columns 
	int ny;				// Number of rows 
	int node_offset;		// 0 for node grids, 1 for pixel grids 
	double x_min;			// Minimum x coordinate 
	double x_max;			// Maximum x coordinate 
	double y_min;			// Minimum y coordinate 
	double y_max;			// Maximum y coordinate 
	double z_min;			// Minimum z value 
	double z_max;			// Maximum z value 
	double x_inc;			// x increment 
	double y_inc;			// y increment 
	double z_scale_factor;		// grd values must be multiplied by this 
	double z_add_offset;		// After scaling, add this 
	char x_units[GRD_UNIT_LEN];	// units in x-direction 
	char y_units[GRD_UNIT_LEN];	// units in y-direction 
	char z_units[GRD_UNIT_LEN];	// grid value units 
	char title[GRD_TITLE_LEN];	// name of data set 
	char command[GRD_COMMAND_LEN];	// name of generating command 
	char remark[GRD_REMARK_LEN];	// comments re this data set 
};

#define IRINT(x) ((int)(floor((x)+0.5)))
#define GMT_make_fnan(x) (((size_t *) &x)[0] = 0x7fffffff)

int * GMT_grd_prep_io (struct GRD_HEADER *header, double *w, double *e, double *s, double *n, int *width, int *height, int *first_col, int *last_col, int *first_row, int *last_row)
{
	// Determines which rows and colums to extract, and if it is
	// a grid that is periodic and wraps around and returns indeces. 

	int one_or_zero, i, *k;
	int geo = 0;
	double Small, off, half_or_zero, x;


	if (*w == 0.0 && *e == 0.0) {	// Get entire file 
		*width  = header->nx;
		*height = header->ny;	
		*first_col = *first_row = 0;
		*last_col  = header->nx - 1;
		*last_row  = header->ny - 1;
		*w = header->x_min;	*e = header->x_max;
		*s = header->y_min;	*n = header->y_max;
	}
	else {				// Must deal with a subregion 

		if (*w < header->x_min || *e > header->x_max) geo = 1;	// Dealing with periodic grid 

		if (*s < header->y_min || *n > header->y_max) {	// Calling program goofed... 
			writelog(LOG_ERROR, "GMT ERROR: Trying to read beyond grid domain - abort!!");
			return NULL;
		}
		one_or_zero = (header->node_offset) ? 0 : 1;

		// Get dimension of subregion 
	
		*width  = IRINT ((*e - *w) / header->x_inc) + one_or_zero;
		*height = IRINT ((*n - *s) / header->y_inc) + one_or_zero;
	
		// Get first and last row and column numbers 
	
		Small = 0.1 * header->x_inc;
		*first_col = (int)floor ((*w - header->x_min + Small) / header->x_inc);
		*last_col  = (int)ceil  ((*e - header->x_min - Small) / header->x_inc) - 1 + one_or_zero;
		Small = 0.1 * header->y_inc;
		*first_row = (int)floor ((header->y_max - *n + Small) / header->y_inc);
		*last_row  = (int)ceil  ((header->y_max - *s - Small) / header->y_inc) - 1 + one_or_zero;

		if ((*last_col - *first_col + 1) > *width) (*last_col)--;
		if ((*last_row - *first_row + 1) > *height) (*last_row)--;
		if ((*last_col - *first_col + 1) > *width) (*first_col)++;
		if ((*last_row - *first_row + 1) > *height) (*first_row)++;
	}

	k = (int *) malloc ( (size_t)(*width) * sizeof (int));
	if (geo) {
		off = (header->node_offset) ? 0.0 : 0.5;
		half_or_zero = (header->node_offset) ? 0.5 : 0.0;
		Small = 0.1 * header->x_inc;	// Anything Smaller than 0.5 dx will do 
		for (i = 0; i < (*width); i++) {
			x = *w + (i + half_or_zero) * header->x_inc;
			if ((header->x_min - x) > Small)
				x += 360.0;
			else if ((x - header->x_max) > Small)
				x -= 360.0;
			k[i] = (int) floor (((x - header->x_min) / header->x_inc) + off);
		}
	}
	else {	// Normal ordering 
		for (i = 0; i < (*width); i++) k[i] = (*first_col) + i;
	}

	return (k);
};
#endif

d_surf * _surf_load_gmt(const char * filename, const char * surfname)
{
#ifndef HAVE_NETCDF
	writelog(LOG_ERROR, "this function not implemented because netCDF library wasn't found");
	return NULL;
#else
	if (!filename)
		return false;

	writelog(LOG_MESSAGE, "loading surface from GMT file %s",filename);

	GRD_HEADER header;
	int cdfid, nm[2];
	size_t start[2], edge[2];
	double dummy[2];
	char text[GRD_COMMAND_LEN+GRD_REMARK_LEN];

	// variable ids 
	int  x_range_id, y_range_id, z_range_id, inc_id, nm_id, z_id;

	int first_col, last_col, first_row, last_row;
	int i, j, ij, j2, width_in, width_out, height_in, i_0_out, kk, inc = 1;
	int *k;
	double w = 0, e = 0, s = 0, n = 0;
	int pad[4] = {0, 0, 0, 0};
	bool complex = false;
	REAL z_min, z_max;

	d_grid * grd = NULL;
	d_surf * res = NULL;

	float *tmp;
	vec * data = NULL;

	// Open file and get info
	if (check_nc_status (nc_open (filename, NC_NOWRITE, &cdfid)) == false)
		goto exit;

	memset ((void *)text, 0, (size_t)(GRD_COMMAND_LEN+GRD_REMARK_LEN));

	// Get variable ids 
	if (check_nc_status (nc_inq_varid (cdfid, "x_range", &x_range_id)) == false)
		goto exit;
	if (check_nc_status (nc_inq_varid (cdfid, "y_range", &y_range_id)) == false)
		goto exit;
	if (check_nc_status (nc_inq_varid (cdfid, "z_range", &z_range_id)) == false)
		goto exit;
        if (check_nc_status (nc_inq_varid (cdfid, "spacing", &inc_id)) == false)
		goto exit;
        if (check_nc_status (nc_inq_varid (cdfid, "dimension", &nm_id)) == false)
		goto exit;
        if (check_nc_status (nc_inq_varid (cdfid, "z", &z_id)) == false)
		goto exit;

	// Get attributes 
	if (check_nc_status (nc_get_att_text  (cdfid, x_range_id, "units", header.x_units)) == false)
		goto exit;
        if (check_nc_status (nc_get_att_text  (cdfid, y_range_id, "units", header.y_units)) == false)
		goto exit;
	if (check_nc_status (nc_get_att_text  (cdfid, z_range_id, "units", header.z_units)) == false)
		goto exit;
        if (check_nc_status (nc_get_att_double  (cdfid, z_id, "scale_factor", &header.z_scale_factor)) == false)
		goto exit;
        if (check_nc_status (nc_get_att_double  (cdfid, z_id, "add_offset", &header.z_add_offset)) == false)
		goto exit;
        if (check_nc_status (nc_get_att_int  (cdfid, z_id, "node_offset", &header.node_offset)) == false)
		goto exit;
        if (check_nc_status (nc_get_att_text  (cdfid, NC_GLOBAL, "title", header.title)) == false)
		goto exit;
        if (check_nc_status (nc_get_att_text  (cdfid, NC_GLOBAL, "source", text)) == false)
		goto exit;

	strncpy (header.command, text, GRD_COMMAND_LEN);
	strncpy (header.remark, &text[GRD_COMMAND_LEN], GRD_REMARK_LEN);
	
	// Get variables 
	
	start[0] = 0;
	edge[0] = 2;

	if (check_nc_status (nc_get_vara_double(cdfid, x_range_id, start, edge, dummy)) == false)
		goto exit;
	header.x_min = dummy[0];
	header.x_max = dummy[1];
	if (check_nc_status (nc_get_vara_double(cdfid, y_range_id, start, edge, dummy)) == false)
		goto exit;
	header.y_min = dummy[0];
	header.y_max = dummy[1];
	if (check_nc_status (nc_get_vara_double(cdfid, inc_id, start, edge, dummy)) == false)
		goto exit;
	header.x_inc = dummy[0];
	header.y_inc = dummy[1];
	if (check_nc_status (nc_get_vara_int(cdfid, nm_id, start, edge, nm)) == false)
		goto exit;
	header.nx = nm[0];
	header.ny = nm[1];
	if (check_nc_status (nc_get_vara_double(cdfid, z_range_id, start, edge, dummy)) == false)
		goto exit;
	header.z_min = dummy[0];
	header.z_max = dummy[1];

	k = GMT_grd_prep_io (&header, &w, &e, &s, &n, &width_in, &height_in, &first_col, &last_col, &first_row, &last_row);
	
	width_out = width_in;		// Width of output array 
	if (pad[0] > 0) width_out += pad[0];
	if (pad[1] > 0) width_out += pad[1];
	
	i_0_out = pad[0];		// Edge offset in output 
	if (complex) {	// Need twice as much space and load every 2nd cell 
		width_out *= 2;
		i_0_out *= 2;
		inc = 2;
	}
	
	tmp = (float *) malloc ( (size_t)header.nx * sizeof (float));
	edge[0] = header.nx;

	data = create_vec( header.nx*header.ny, 0, 0); // don't fill this vector

	z_min = header.z_min;
	z_max = header.z_max;
	float fnan;
	GMT_make_fnan(fnan);
	
	header.z_min = DBL_MAX;	header.z_max = -DBL_MAX;
	for (j = first_row, j2 = last_row; j <= last_row; j++, j2--) {
		start[0] = j * header.nx;
		// Get one row 
		check_nc_status (nc_get_vara_float (cdfid, z_id, start, edge, tmp));
		ij = (j2 + pad[3]) * width_out + i_0_out;	// Already has factor of 2 in it if complex 
		for (i = 0; i < width_in; i++) {
			kk = ij+i*inc;
			(*data)(kk) = tmp[k[i]];
			REAL val = (*data)(kk);
#ifdef WIN32
			if (_isnan(val)) {
#else
			if (isnan(val)) {
#endif
				(*data)(kk) = surfit::undef_value;
				continue;
			}
			if ((double)val < header.z_min) header.z_min = (double)val;
			if ((double)val > header.z_max) header.z_max = (double)val;
		}
	}

	free(k);
	
	header.nx = width_in;
	header.ny = height_in;
	header.x_min = w;
	header.x_max = e;
	header.y_min = s;
	header.y_max = n;

	check_nc_status (nc_close (cdfid));

	grd = create_grid(header.x_min, header.x_min + header.x_inc*(header.nx-1), header.x_inc,
			  header.y_min, header.y_min + header.y_inc*(header.ny-1), header.y_inc);

	grd->getCountX();
	grd->getCountY();
	
	res = create_surf(data, grd);
	
	if (surfname != NULL) 
		res->setName(surfname);
	else {
		if ( strlen(header.title) > 0 )
			res->setName(header.title);
	}

	return res;


exit:
	if (data)
		data->release();
	check_nc_status (nc_close (cdfid));
	return NULL;

#endif
}; 

bool _surf_save_gmt(const d_surf * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_gmt : no surf loaded");
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to GMT grd file %s (CDF format)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to GMT grd file %s (CDF format)", filename);

#ifndef HAVE_NETCDF
	writelog(LOG_ERROR, "this function not implemented because netCDF library wasn't found");
	return false;
#else

	size_t start[2], edge[2];
	int cdfid, nm[2];
	int i, i2, inc = 1, *k;
	int j, ij, j2, width_in, width_out, height_out;
	int first_col, last_col, first_row, last_row;
	
	double dummy[2];
	
	char text[GRD_COMMAND_LEN+GRD_REMARK_LEN];
	
	float *tmp;
	
	// dimension ids 
	int  side_dim, xysize_dim;

	// variable ids 
	int  x_range_id, y_range_id, z_range_id, inc_id, nm_id, z_id;

	// variable shapes 
	int dims[1];

	// Create file and enter define mode 

	GRD_HEADER header;
	header.nx = srf->getCountX();
	header.ny = srf->getCountY();
	strcpy(header.command,"");
	strcpy(header.remark,"");
	strcpy(header.x_units,"user_x_unit");
	strcpy(header.y_units,"user_y_unit");
	strcpy(header.z_units,"user_z_unit");
	if (srf->getName())
		strcpy(header.title, srf->getName());
	else
		strcpy(header.title,"");
	header.node_offset = 0;
	header.z_scale_factor = 1;
	header.z_add_offset = 0;
	header.x_min = srf->getCoordNodeX(0);
	header.x_max = srf->getCoordNodeX( header.nx-1 );
	header.x_inc = srf->getStepX();
	header.y_min = srf->getCoordNodeY(0);
	header.y_max = srf->getCoordNodeY( header.ny-1 );
	header.y_inc = srf->getStepY();
	//header.remark = strcpy("");
	double w = 0, e = 0, s = 0, n = 0;
	int pad[4] = {0, 0, 0, 0};
	bool complex = false;
	
	check_nc_status (nc_create (filename, NC_CLOBBER,&cdfid));

	k = GMT_grd_prep_io (&header, &w, &e, &s, &n, &width_out, &height_out, &first_col, &last_col, &first_row, &last_row);

	width_in = width_out;		// Physical width of input array 
	if (pad[0] > 0) width_in += pad[0];
	if (pad[1] > 0) width_in += pad[1];
	
	edge[0] = width_out;
	if (complex) inc = 2;

	header.x_min = w;
	header.x_max = e;
	header.y_min = s;
	header.y_max = n;
	
	// define dimensions 
	check_nc_status (nc_def_dim(cdfid, "side", 2, &side_dim));
	check_nc_status (nc_def_dim(cdfid, "xysize", (int) (width_out * height_out), &xysize_dim));

	// define variables 

	dims[0]		= side_dim;
	check_nc_status (nc_def_var (cdfid, "x_range", NC_DOUBLE, 1, dims, &x_range_id));
        check_nc_status (nc_def_var (cdfid, "y_range", NC_DOUBLE, 1, dims, &y_range_id));
        check_nc_status (nc_def_var (cdfid, "z_range", NC_DOUBLE, 1, dims, &z_range_id));
        check_nc_status (nc_def_var (cdfid, "spacing", NC_DOUBLE, 1, dims, &inc_id));
        check_nc_status (nc_def_var (cdfid, "dimension", NC_LONG, 1, dims, &nm_id));


	dims[0]		= xysize_dim;
	check_nc_status (nc_def_var (cdfid, "z", NC_FLOAT, 1, dims, &z_id));

	// assign attributes 
	
	memset ((void *)text, 0, (size_t)(GRD_COMMAND_LEN+GRD_REMARK_LEN));
	
	strcpy (text, header.command);
	strcpy (&text[GRD_COMMAND_LEN], header.remark);
	check_nc_status (nc_put_att_text (cdfid, x_range_id, "units", GRD_UNIT_LEN, header.x_units));
        check_nc_status (nc_put_att_text (cdfid, y_range_id, "units", GRD_UNIT_LEN, header.y_units));
        check_nc_status (nc_put_att_text (cdfid, z_range_id, "units", GRD_UNIT_LEN, header.z_units));
        check_nc_status (nc_put_att_double (cdfid, z_id, "scale_factor", NC_DOUBLE, 1, &header.z_scale_factor));
        check_nc_status (nc_put_att_double (cdfid, z_id, "add_offset", NC_DOUBLE, 1, &header.z_add_offset));
        check_nc_status (nc_put_att_int (cdfid, z_id, "node_offset", NC_LONG, 1, &header.node_offset));
        check_nc_status (nc_put_att_text (cdfid, NC_GLOBAL, "title", GRD_TITLE_LEN, header.title));
        check_nc_status (nc_put_att_text (cdfid, NC_GLOBAL, "source", (GRD_COMMAND_LEN+GRD_REMARK_LEN), text));
	
	// leave define mode 
	check_nc_status (nc_enddef (cdfid));

	// Find zmin/zmax 
	
	header.z_min = DBL_MAX;	header.z_max = -DBL_MAX;
	for (j = first_row, j2 = pad[3]; j <= last_row; j++, j2++) {
		for (i = first_col, i2 = pad[0]; i <= last_col; i++, i2++) {
			ij = (j2 * width_in + i2) * inc;
			if ((*(srf->coeff))(ij) == srf->undef_value) 
				continue;
			/*
			if (GMT_is_fnan (grid[ij])) {
				if (check) grid[ij] = (float)GMT_grd_out_nan_value;
				continue;
			}
			*/
			header.z_min = MIN (header.z_min, (*(srf->coeff))(ij));
			header.z_max = MAX (header.z_max, (*(srf->coeff))(ij));
		}
	}
	
	// store header information and array 
	
	start[0] = 0;
	edge[0] = 2;
	dummy[0] = header.x_min;
	dummy[1] = header.x_max;
	check_nc_status (nc_put_vara_double(cdfid, x_range_id, start, edge, dummy));
	dummy[0] = header.y_min;
	dummy[1] = header.y_max;
	check_nc_status (nc_put_vara_double(cdfid, y_range_id, start, edge, dummy));
	dummy[0] = header.x_inc;
	dummy[1] = header.y_inc;
	check_nc_status (nc_put_vara_double(cdfid, inc_id, start, edge, dummy));
	nm[0] = width_out;
	nm[1] = height_out;
	check_nc_status (nc_put_vara_int(cdfid, nm_id, start, edge, nm));
	dummy[0] = header.z_min;
	dummy[1] = header.z_max;
	check_nc_status (nc_put_vara_double(cdfid, z_range_id, start, edge, dummy));

	tmp = (float *) malloc( (size_t)width_in*sizeof(float) );
		
	edge[0] = width_out;
	i2 = first_col + pad[0];
	for (j = 0, j2 = last_row - first_row - pad[3]; j < height_out; j++, j2--) {
		ij = j2 * width_in + i2;
		start[0] = j * width_out;
		for (i = 0; i < width_out; i++) {
			REAL val = (*(srf->coeff))(inc * (ij+k[i]));
			if (val == srf->undef_value)
				GMT_make_fnan(tmp[i]);
			else 
				tmp[i] = (float)(*(srf->coeff))(inc * (ij+k[i]));
		}
		check_nc_status (nc_put_vara_float (cdfid, z_id, start, edge, tmp));
	}
	check_nc_status (nc_close (cdfid));

	free(k);
	free(tmp);
	
	return true;
#endif
};

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


d_surf * _surf_load_jpg(const char * filename, const char * surfname, REAL minz, REAL maxz, REAL startX, REAL startY, REAL stepX, REAL stepY) {
	
	writelog(LOG_MESSAGE, "loading surface from JPEG file %s",filename);

#ifndef HAVE_LIBJPEG
	writelog(LOG_ERROR, "this function not implemented because netCDF library wasn't found");
	return NULL;
#else
	
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	
	FILE * infile;		// source file 
	JSAMPARRAY buffer;	// Output row buffer
	int row_stride;		// physical row width in output buffer 
	size_t i;
	
	if ((infile = fopen(filename, "rb")) == NULL) {
		writelog(LOG_ERROR, "can't open %s : %s", filename, strerror(errno) );
		return NULL;
	}
	
	jpeg_stdio_src(&cinfo, infile);

	jpeg_read_header(&cinfo, TRUE);
	
	// set parameters for decompression 
	cinfo.out_color_space = JCS_GRAYSCALE;
	
	// Start decompressor 
	
	(void) jpeg_start_decompress(&cinfo);
	
	row_stride = cinfo.output_width * cinfo.output_components;
	// Make a one-row-high sample array that will go away when done with image 
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	vec * coeff = create_vec( cinfo.output_height * cinfo.output_width, 0, 0);
		
	// Here we use the library's state variable cinfo.output_scanline as the
	// loop counter, so that we don't have to keep track ourselves.
	
	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		for (i = 0; i < cinfo.output_width; i++) {
			if (maxz != minz)
				(*coeff)( i + (cinfo.output_height - cinfo.output_scanline)*cinfo.output_width ) = (maxz-minz)*buffer[0][i]/REAL(255) + minz;
			else
				(*coeff)( i + (cinfo.output_height - cinfo.output_scanline)*cinfo.output_width ) = buffer[0][i];
		}
	}

	// Finish decompression 
	
	(void) jpeg_finish_decompress(&cinfo);
	
	// Release JPEG decompression object 
	jpeg_destroy_decompress(&cinfo);
	
	fclose(infile);


	d_grid * grd = create_grid(startX, startX + stepX*(cinfo.output_width-1), stepX,
				   startY, startY + stepY*(cinfo.output_height-1), stepY);


	d_surf * res = create_surf(coeff, grd);

	if (surfname)
		res->setName(surfname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;
#endif
};

bool _surf_save_jpg(const d_surf * srf, const char * filename, int quality) {

	quality = MAX(255,MIN(0, quality));
	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_jpg : no surf loaded");
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to file %s (JPEG)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to file %s (JPEG)", filename);

#ifndef HAVE_LIBJPEG
	writelog(LOG_ERROR, "this function not implemented because netCDF library wasn't found");
	return false;
#else

	jpeg_compress_struct cinfo;
	jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	int row_stride = 1;

	size_t i;
	REAL minz, maxz;
	srf->getMinMaxZ(minz, maxz);
	int NN = srf->getCountX();
	int MM = srf->getCountY();

	JSAMPLE * row_data = (JSAMPLE *)malloc( NN*sizeof(JSAMPLE) );

	FILE * outfile;
	if ((outfile = fopen(filename, "wb")) == NULL) {
		writelog(LOG_ERROR, "can't open %s : %s", filename, strerror(errno));
		return false;
	}
	jpeg_stdio_dest(&cinfo, outfile);

	// Set parameters for compression, including image size & colorspace.
	cinfo.image_width = NN; 	/* image width and height, in pixels */
	cinfo.image_height = MM;
	cinfo.input_components = 1;	/* # of color components per pixel */
	cinfo.in_color_space = JCS_GRAYSCALE; /* colorspace of input image */

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, true);

	// start compress
	jpeg_start_compress(&cinfo, TRUE);

	while (cinfo.next_scanline < cinfo.image_height) {
		// fill row with grayscale colours
		for (i = 0; i < NN; i++) {
			REAL val = srf->getValueIJ(NN-1-i, MM-cinfo.next_scanline-1);
			int color = 0;
			if (val != srf->undef_value)
				color = 255 - MAX(0,MIN(254,floor((val-minz)/(maxz-minz)*254+0.5)));
			*(row_data + i) = color;
		}
		(void) jpeg_write_scanlines(&cinfo, &row_data, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	free(row_data);

	return true;
#endif

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

	size_t i,j;
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

#ifdef HAVE_THREADS
struct surf_project_job : public job 
{
	surf_project_job()
	{
		J_from = 0;
		J_to = 0;
		srf = NULL;
		grd = NULL;
	};
	void set(size_t iJ_from, size_t iJ_to, 
		 const d_surf * isrf, const d_grid * igrd,
		 vec * icoeff)
	{
		J_from = iJ_from;
		J_to = iJ_to;
		srf = isrf;
		grd = igrd;
		coeff = icoeff;
	};
	virtual void do_job() 
	{
		d_grid * g = srf->grd;
		REAL value, x, y, x0, y0;
		size_t I0, I1, J0, J1;
		REAL z0, z1, z2, z3;
		REAL delta_x, delta_y;

		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
		size_t size_x = grd->getCountX();
		size_t surf_sizeX = srf->getCountX();
		size_t surf_sizeY = srf->getCountY();

		size_t i,j;
		for (j = J_from; j < J_to; j++) {
			for (i = 0; i < (size_t)size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
								
				I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
				J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));

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
				
				// ������ ��� �������� ������������
				REAL z11 = (z2-z1)*delta_y/hY+z1;
				REAL z22 = (z3-z0)*delta_y/hY+z0;
				
				// ������ ��� �������� ������������
				REAL res = (z11-z22)*delta_x/hX+z22;
								
				(*coeff)(i + j*size_x) = res;
				
								
			}
		}
	};

	size_t J_from, J_to;
	const d_surf * srf;
	const d_grid * grd;
	vec * coeff;
};

surf_project_job surf_project_jobs[MAX_CPU];
#endif

d_surf * _surf_project(const d_surf * srf, d_grid * grd) {

	size_t size_x = grd->getCountX();
	size_t size_y = grd->getCountY();

	vec * coeff = create_vec(size_x*size_y,0,0);  // do not fill this vector
	
	size_t surf_size = srf->coeff->size();
	size_t surf_sizeX = srf->getCountX();
	size_t surf_sizeY = srf->getCountY();

	if (srf->getName())
		writelog(LOG_MESSAGE,"Projecting surf \"%s\" (%d x %d) => (%d x %d)",srf->getName(), surf_sizeX, surf_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting surf (%d x %d) => (%d x %d)", surf_sizeX, surf_sizeY, size_x, size_y);

	{

		REAL x, y;
		size_t I0, J0, I1, J1;
		REAL value;
		size_t i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
#ifdef HAVE_THREADS
		if (cpu == 1) {
#endif
		d_grid * g = srf->grd;
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
								
				I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
				J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));

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
				
				// ������ ��� �������� ������������
				REAL z11 = (z2-z1)*delta_y/hY+z1;
				REAL z22 = (z3-z0)*delta_y/hY+z0;
				
				// ������ ��� �������� ������������
				REAL res = (z11-z22)*delta_x/hX+z22;
								
				(*coeff)(i + j*size_x) = res;
				
								
			}
		}
#ifdef HAVE_THREADS
		} else {
			size_t step = size_y / (cpu);
			size_t ost = size_y % (cpu);
			size_t J_from = 0;
			size_t J_to = 0;
			size_t work;
			for (work = 0; work < cpu; work++) {
				J_to = J_from + step;
				if (work == 0)
					J_to += ost;
				
				surf_project_job & f = surf_project_jobs[work];
				f.set(J_from, J_to, srf, grd, coeff);
				set_job(&f, work);
				J_from = J_to;
			}

			do_jobs();
		}
#endif
	}
	
	d_grid * new_grd = create_grid(grd);
	d_surf * res = create_surf(coeff, new_grd, srf->getName());
	res->undef_value = srf->undef_value;
	return res;
};

d_surf * _surf_project(d_surf * srf, d_grid * grd, grid_line * fault_grd_line) {

	if (!fault_grd_line)
		return _surf_project(srf, grd);

	size_t size_x = grd->getCountX();
	size_t size_y = grd->getCountY();

	vec * coeff = create_vec(size_x*size_y,0,0);  // do not fill this vector
	
	size_t surf_size = srf->coeff->size();
	size_t surf_sizeX = srf->getCountX();
	size_t surf_sizeY = srf->getCountY();

	if (srf->getName())
		writelog(LOG_MESSAGE,"Projecting surf \"%s\" (%d x %d) => (%d x %d)",srf->getName(), surf_sizeX, surf_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting surf (%d x %d) => (%d x %d)", surf_sizeX, surf_sizeY, size_x, size_y);

	{

		REAL x, y;
		size_t I0, J0, I1, J1;
		REAL value;
		size_t i,j;
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
				I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
				J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));

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
	
	d_grid * new_grd = create_grid(grd);
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

	size_t i,j;
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	REAL * ptr = srf->coeff->begin();

	REAL v1, v2;

	REAL dx = 0;
	size_t dx_cnt = 0;
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

	size_t i,j;
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	REAL * ptr = srf->coeff->begin();

	REAL v1, v2, v3, v4;

	REAL dx2 = 0;
	size_t dx2_cnt = 0;
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
	size_t dxdy_cnt = 0;
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
	size_t dy2_cnt = 0;
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
	
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	bool first_x, second_x;
	bool first_y, second_y;

	vec * coeff = create_vec(NN*MM);

	size_t i, j, pos, pos1;
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

	d_grid * grd = create_grid(srf->grd);
	d_surf * res = create_surf(coeff, grd, srf->getName());
	return res;

};

d_grid * adopt_surf_grid(const d_surf * srf, d_grid * grd,
			 size_t & from_x, size_t & to_x,
			 size_t & from_y, size_t & to_y) {

	REAL g_x0, g_xn, g_y0, g_yn; // ������ � ����� ���������
	REAL f_x0, f_xn, f_y0, f_yn; // ������ � ����� �������
	REAL x0, xn, y0, yn;     // �������� ������ � �����

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
	
	d_grid * new_geom = create_grid(x0, xn, grd->stepX, y0, yn, grd->stepY);
	return new_geom;

};

REAL _surf_mean_area(const d_surf * srf, const d_area * area) {
	
	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return srf->undef_value;
	
	size_t i, N = 0;
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
	
	size_t i;
	
	if (mask == NULL) 
		return srf->undef_value;
	
	size_t aux_X_from, aux_X_to;
	size_t aux_Y_from, aux_Y_to;
	_grid_intersect1(srf->grd, wsrf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_grid * aux_grid = _create_sub_grid(srf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_surf * w_srf = _surf_project(wsrf, aux_grid);
	size_t nn = aux_grid->getCountX();
	size_t mm = aux_grid->getCountY();
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();
	
	if (aux_grid)
		aux_grid->release();

	REAL denom = 0;
	size_t ii, jj;
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
			size_t I = ii-aux_X_from;
			size_t J = jj-aux_Y_from;
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

	size_t i;

	REAL sum = 0;
	REAL value;
	for (i = 0; i < (size_t)mask->size(); i++) {
		
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



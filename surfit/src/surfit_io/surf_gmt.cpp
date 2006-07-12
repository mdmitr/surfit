
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

#ifdef HAVE_NETCDF
#include <netcdf.h>
#endif

#include <float.h>

namespace surfit {

#ifdef HAVE_NETCDF
static const char ncmagic[] = {'C', 'D', 'F', 0x01};

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
#endif // HAVE_NETCDF

d_surf * _surf_load_gmt(const char * filename, const char * surfname)
{
#ifndef HAVE_NETCDF
	writelog(LOG_ERROR, "this function is not implemented because netCDF library wasn't found");
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
	writelog(LOG_ERROR, "this function is not implemented because netCDF library wasn't found");
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

};


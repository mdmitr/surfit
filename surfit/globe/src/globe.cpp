
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

#include "ie_globe.h"
#include "globe.h"

#include <stdlib.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#include <stdarg.h>
#include <stdio.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "real.h"
#include "func.h"
#include "func_internal.h"
#include "grid.h"
#include "vec.h"
#include "fileio.h"

#define GLOBE_UNDEF FLT_MAX

namespace surfit {

void read_variable(FILE * f, char * read_buf, char * name, double & value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		fscanf(f, "%s", read_buf);
		value = atof(read_buf);
	}
}

void read_variable(FILE * f, char * read_buf, char * name, int & value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		fscanf(f, "%s", read_buf);
		value = atoi(read_buf);
	}
}

bool read_globe_func(const char * hdr_file, const char * bin_file) {


	FILE * hdr = fopen(hdr_file, "r");
	if (!hdr) {
		surfit::writelog(SURFIT_ERROR, "The file %s was not opened: %s",hdr_file,strerror( errno ));
		return false;
	}
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	int bin = open(bin_file, O_RDONLY|O_BINARY);
#else
	int bin = open(bin_file, O_RDONLY);
#endif
	if (bin == -1) {
		surfit::writelog(SURFIT_ERROR, "The file %s was not opened: %s",bin_file,strerror( errno ));
		return false;
	}

	surfit::writelog(SURFIT_MESSAGE, "Processing %s->%s", hdr_file, bin_file);

	char read_buf[2048];
	
	double upper_map_y;
	double lower_map_y;
	double left_map_x;
	double right_map_x;
	int number_of_rows;
	int number_of_columns;
	double grid_size_x_;
	double grid_size_y_;
	double missing_flag;
	
	while (!feof(hdr)) {
		fscanf(hdr, "%s", read_buf);
		read_variable(hdr, read_buf, "upper_map_y", upper_map_y);
		read_variable(hdr, read_buf, "lower_map_y", lower_map_y);
		read_variable(hdr, read_buf, "left_map_x",  left_map_x);
		read_variable(hdr, read_buf, "right_map_x", right_map_x);
		read_variable(hdr, read_buf, "number_of_rows", number_of_rows);
		read_variable(hdr, read_buf, "number_of_columns", number_of_columns);
		read_variable(hdr, read_buf, "grid_size(x)", grid_size_x_);
		read_variable(hdr, read_buf, "grid_size(y)", grid_size_y_);
		read_variable(hdr, read_buf, "missing_flag", missing_flag);
	}

	fclose (hdr);

	int i,j, read_bytes;
#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
	__int16 * val = NULL;
	int size_int16 = sizeof(__int16);
	val = (__int16*) malloc( number_of_rows*number_of_columns*size_int16 );
#else
	int16_t * val = NULL;
	int size_int16 = sizeof(int16_t);
	val = (int16_t*) malloc( number_of_rows*number_of_columns*size_int16 );
#endif

	if (!val) {
		surfit::writelog(SURFIT_ERROR,"Not enougth memory.");
		return false;
	}
	int cnt = 0;

	surfit::writelog(SURFIT_MESSAGE,"%d grid nodes", number_of_rows*number_of_columns);

	read_bytes = read(bin,val,size_int16*number_of_rows*number_of_columns);
	if (read_bytes != size_int16*number_of_rows*number_of_columns) {
		surfit::writelog(SURFIT_ERROR,"Read error!");
		free(val);
		return false;
	}

	surfit::grid * grd = new surfit::grid(left_map_x, left_map_x + grid_size_x_*(number_of_columns-1), grid_size_x_,
		                                       lower_map_y, lower_map_y + grid_size_y_*(number_of_rows-1), grid_size_y_);
											   
	surfit::vec * coeff = new surfit::vec(number_of_rows*number_of_columns);
	
	int N = number_of_columns;
	int M = number_of_rows;
	int I, J;
	REAL res_val;
	
	for (j = 0; j < M; j++) {
		for (i = 0; i < N; i++) {
			I = N-1-i;
			I = i;
			J = M-1-j;
			res_val = (REAL)*(val + I + J*N );
			if (res_val == missing_flag)
				res_val = GLOBE_UNDEF;
			*(coeff->begin() + i + j*N) = res_val;
		}
	}
	
	free(val);

	surfit::func * res = new surfit::func(coeff, grd, NULL);
	res->undef_value = GLOBE_UNDEF;

	int sizex = grd->getCountX();
	int sizey = grd->getCountY();
	int size = coeff->size();

	if (sizex != number_of_columns)
		surfit::writelog(SURFIT_ERROR,"sizex = %d, number_of_columns = %d", sizex, number_of_columns);
	if (sizey != number_of_rows)
		surfit::writelog(SURFIT_ERROR,"sizey = %d, number_of_rows = %d", sizey, number_of_rows);

	surfit::_set_surfit_func(res);

	close (bin);

	return true;
};

}; // namespace surfit;

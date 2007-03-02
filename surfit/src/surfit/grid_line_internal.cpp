
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

#include "datafile.h"
#include "fileio.h"
#include "intvec.h"
#include "vec.h"

#include "grid_line.h"
#include "grid_line_internal.h"
#include "curv.h"
#include "curv_internal.h"
#include "grid.h"
#include "variables_tcl.h"
#include "variables_internal.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

bool _grid_line_check() {
	return (surfit_grid_line != NULL);
};

bool _grid_line_unload() {
	if (_grid_line_check()) {
		if (surfit_grid_line)
			surfit_grid_line->release();
		surfit_grid_line = NULL;
		return true;
	} 
	return false;
};

bool _grid_line_write(const grid_line * contour, d_grid * grd, const char * filename, const char * mask) {
	if (!contour)
		return false;
	d_curv * cc = _grid_line_to_curv(contour, grd);
	_curv_write(cc, filename, mask);
	if (cc)
		cc->release();
	return true;
};

bool _grid_line_save(const grid_line * contour, d_grid * grd, const char * filename) {
	if (!contour)
		return false;
	d_curv * cc = _grid_line_to_curv(contour, grd);
	_curv_save(cc, filename);
	if (cc)
		cc->release();
	return true;
};

void _grid_line_info(const grid_line * contour) {
	if (!contour) {
		writelog(LOG_WARNING, "_grid_line_info : NULL pointer given");
		return;
	}
	writelog(LOG_MESSAGE,"grid_line (%s)",contour->getName());
};

grid_line * _get_surfit_grid_line() {
	return surfit_grid_line;
};

void _set_surfit_grid_line(grid_line * contour) {
	if (surfit_grid_line)
		surfit_grid_line->release();
	surfit_grid_line = contour;
};

d_curv * _grid_line_to_curv(const grid_line * grd_line, const d_grid * grd) {

	if (!grd)
		return false;

	size_t N = grd_line->size();
	
	vec * X = create_vec(2*N);
	vec * Y = create_vec(2*N);
	
	size_t i;
	size_t J1, J2;

	REAL stepX2 = grd->stepX/REAL(2);
	REAL stepY2 = grd->stepY/REAL(2);
	size_t pos = 0;
	
	for (i = 0; i < N; i++) {

		J1 = grd_line->get_first_cell(i);
		J2 = grd_line->get_second_cell(i);
		/*
		J1 = *(grd_line->first->begin() + i);
		J2 = *(grd_line->second->begin() + i);
		*/
		
		REAL x, y;
		size_t NN = grd->getCountX();
			
		size_t n = J1 % NN;
		size_t m = (J1 - n)/NN;
		
		grd->getCoordNode(n,m,x,y);
		
		int diff = (J2-J1);
		
		// right line
		if (diff == 1) {
			(*X)(pos) = x+stepX2;
			(*Y)(pos) = y-stepY2;
			pos++;
			
			(*X)(pos) = x+stepX2;
			(*Y)(pos) = y+stepY2;
			pos++;
		}
		
		// left line
		if (diff == -1) {
			(*X)(pos) = x-stepX2;
			(*Y)(pos) = y-stepY2;
			pos++;
			
			(*X)(pos) = x-stepX2;
			(*Y)(pos) = y+stepY2;
			pos++;
		}
		
		// up line 
		if (diff == NN) {
			(*X)(pos) = x-stepX2;
			(*Y)(pos) = y+stepY2;
			pos++;
			
			(*X)(pos) = x+stepX2;
			(*Y)(pos) = y+stepY2;
			pos++;
		}
		
		// down line
		if (diff == -(int)NN) {
			(*X)(pos) = x-stepX2;
			(*Y)(pos) = y-stepY2;
			pos++;
			
			(*X)(pos) = x+stepX2;
			(*Y)(pos) = y-stepY2;
			pos++;
		}
		
	}
	
	d_curv * res = create_curv(X, Y, grd_line->getName());
		
	return res;
};

}; // namespace surfit;




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

#include "ie.h"
#include "grid_line.h"
#include "grid_line_internal.h"
#include "curv.h"
#include "curv_internal.h"
#include "vec.h"
#include "grid.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "fileio.h"

#include "grid_user.h"
#include "grid_line_user.h"

namespace surfit {

bool _grid_line_check() {
	return (surfit_grid_line != NULL);
};

bool _grid_line_unload() {
	if (_grid_line_check()) {
		delete surfit_grid_line;
		surfit_grid_line = NULL;
		return true;
	} 
	return false;
};

bool _grid_line_write(grid_line * contour, const char * filename, const char * mask) {
	if (!_grid_line_check())
		return false;
	curv * cc = _grid_line_to_curv(surfit_grid_line);
	_curv_write(cc, filename, mask);
	delete cc;
	return true;
};

bool _grid_line_save(grid_line * contour, const char * filename, int mode) {
	if (!_grid_line_check())
		return false;
	curv * cc = _grid_line_to_curv(surfit_grid_line);
	_curv_save(cc, filename, get_rw_mode());
	delete cc;
	return true;
};

void _grid_line_info(grid_line * contour) {
	if (!contour) {
		writelog(SURFIT_WARNING, "_grid_line_info : NULL pointer given");
		return;
	}
	if (contour->getName())
		writelog(SURFIT_MESSAGE,"grid_line (%s)",contour->getName());
	else
		writelog(SURFIT_MESSAGE,"grid_line noname");	
};

grid_line * _get_surfit_grid_line() {
	return surfit_grid_line;
};

void _set_surfit_grid_line(grid_line * contour) {
	delete surfit_grid_line;
	surfit_grid_line = contour;
};

curv * _grid_line_to_curv(grid_line * grd_line) {

	if (!surfit_grid)
		return false;
	
	int N = grd_line->size();
	
	vec * X = new vec(N+1);
	vec * Y = new vec(N+1);
	
	int i;
	int J1, J2;

	REAL stepX2 = surfit_grid->stepX/REAL(2);
	REAL stepY2 = surfit_grid->stepY/REAL(2);
	int pos = 0;
	
	for (i = 0; i < N; i++) {
		J1 = *(grd_line->first_begin + i);
		J2 = *(grd_line->second_begin + i);
		
		REAL x, y;
		int NN = surfit_grid->getCountX();
			
		int n = J1 % NN;
		int m = (J1 - n)/NN;
		
		surfit_grid->getCoordNode(n,m,x,y);
		
		int diff = (J2-J1);
		
		// right line
		if (diff == 1) {
			if (i == 0) {
				(*X)(pos) = x+stepX2;
				(*Y)(pos) = y-stepY2;
				pos++;
			}
			(*X)(pos) = x+stepX2;
			(*Y)(pos) = y+stepY2;
			pos++;
		}
		
		// left line
		if (diff == -1) {
			if (i == 0) {
				(*X)(pos) = x-stepX2;
				(*Y)(pos) = y-stepY2;
				pos++;
			}
			(*X)(pos) = x-stepX2;
			(*Y)(pos) = y+stepY2;
			pos++;
		}
		
		// up line 
		if (diff == NN) {
			if (i == 0) {
				(*X)(pos) = x-stepX2;
				(*Y)(pos) = y+stepY2;
				pos++;
			}
			(*X)(pos) = x+stepX2;
			(*Y)(pos) = y+stepY2;
			pos++;
		}
		
		// down line
		if (diff == -NN) {
			if (i == 0) {
				(*X)(pos) = x-stepX2;
				(*Y)(pos) = y-stepY2;
				pos++;
			}
			(*X)(pos) = x+stepX2;
			(*Y)(pos) = y-stepY2;
			pos++;
		}
		
	}
	
	curv * res = new curv(X->begin(), X->end(), Y->begin(), Y->end(), grd_line->getName());
	
	X->drop_data();
	Y->drop_data();
	delete X;
	delete Y;

	return res;
};

}; // namespace surfit;



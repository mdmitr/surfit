
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

#ifdef HAVE_GL_WORKS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <windows.h>
#endif

#include "trend_show.h"
#include "func_show.h"
#include "fileio.h"
#include "vec.h"
#include "grid.h"
#include "trend.h"
#include "trend_internal.h"
#include "trend.h"
#include "trend_internal.h"
#include "color_scale.h"
#include "draw.h"
#include "draw_object.h"

#include <GL/gl.h>
#include <math.h>
#include <float.h>


int conrec(REAL **d,
	   int ilb,
	   int iub,
	   int jlb,
	   int jub,
	   REAL *x,
	   REAL *y,
	   int nc,
	   REAL *z,
	   REAL show_x_from, REAL show_x_to,
	   REAL show_y_from, REAL show_y_to,
	   REAL undef_value);

namespace surfit {

void _trend_show(trend * fnc, const char * filename) {
	_func_show(fnc, draw_trend, filename);
};

void trend_show(const char * filename, const char * trendname) {
	
	trend * fnc = NULL;
	
	if (filename)
		fnc = _trend_load(filename, trendname, 0);
	else 
		fnc = _get_surfit_trend();

	_trend_show(fnc, filename);
	
	if (filename)
		delete fnc;
};

}; // namespace surfit;

#endif 


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

#ifndef __surfit_gl__trend__
#define __surfit_gl__trend__

namespace surfit {

#ifdef HAVE_GL_WORKS

class trend;

SURFIT_EXPORT
/*! \ingroup tcl_gl
    \fn void trend_show(const char * filename, const char * trendname = NULL);
    \brief shows trend from ROFF file. If no filename specified, then shows \ref surfit_trend
*/
void trend_show(const char * filename = NULL, const char * trendname = NULL);

SURFIT_EXPORT
void _trend_show(trend * fnc, const char * filename = NULL);

#endif

}; // namespace surfit;

#endif

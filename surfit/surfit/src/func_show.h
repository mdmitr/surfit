
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


#ifndef __surfit_gl__func__
#define __surfit_gl__func__

namespace surfit {


#ifdef HAVE_GL_WORKS

class func;

SURFIT_EXPORT
/*! \ingroup tcl_func_gl
    \fn void func_show(const char * filename, const char * funcname = NULL);
    \brief shows func from ROFF file. If no filename specified, then shows \ref surfit_func
*/
void func_show(const char * filename = NULL, const char * funcname = NULL);

SURFIT_EXPORT
void _func_show(func * fnc, int surf_draw, const char * filename = NULL);

#endif

}; // namespace surfit;

#endif


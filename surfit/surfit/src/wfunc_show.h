
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

#ifdef HAVE_GL_WORKS

#ifndef __surfit_gl__wfunc__
#define __surfit_gl__wfunc__

namespace surfit {

class wfunc;

SURFIT_EXPORT
/*! \ingroup tcl_gl
    \fn void wfunc_show(const char * filename, const char * wfuncname = NULL);
    \brief shows wfunc from ROFF file. If no filename specified, then shows \ref surfit_wfunc
*/
void wfunc_show(const char * filename = NULL, const char * wfuncname = NULL);

SURFIT_EXPORT
void _wfunc_show(wfunc * fnc, const char * filename = NULL);

}; // namespace surfit;

#endif

#endif


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

#ifndef __surfit_gl__defarea__
#define __surfit_gl__defarea__

namespace surfit {

class defarea;

SURFIT_EXPORT
/*! \ingroup tcl_gl
    \fn void defarea_show(const char * filename, const char * defareaname = NULL);
    \brief shows defarea from ROFF file. If no filename specified, then shows \ref surfit_defarea
*/
void defarea_show(const char * filename = NULL, const char * defareaname = NULL);

SURFIT_EXPORT
void _defarea_show(defarea * def, const char * filename = NULL);

}; // namespace surfit;

#endif

#endif

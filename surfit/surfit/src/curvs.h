
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

#ifndef __surfit_curvs_included__
#define __surfit_curvs_included__

namespace surfit {

class curv;

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn bool curvs_delall();
    \brief removes all curves from \ref surfit_curvs collection
*/
bool curvs_delall();

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn bool curvs_del(int pos);
    \brief removes \ref curv from \ref surfit_curvs collection at 'pos' position
*/
bool curvs_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn bool curvs_read(const char * filename, const char * curvname, int columns, int col1, int col2, const char * delimiter, int grow_by);
    \brief reads \ref curv from formatted text file and adds it to \ref surfit_curv collection 
*/
bool curvs_read(const char * filename, const char * curvname,
		int columns=2, 
		int col1=1, int col2=2, 
		const char * delimiter=" ", int grow_by=250);

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn bool curvs_load(const char * filename, const char * curvname = NULL);
    \brief reads \ref curv from ROFF file (see \ref datafile for details) and adds it to \ref surfit_curvs collection 
*/
bool curvs_load(const char * filename, const char * curvname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn curv * curvs_at(int pos);
    \brief returns \ref curv at 'pos' position in \ref surfit_curvs collection 
*/
curv * curvs_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn curv * curvs_first();
    \brief returns first \ref curv in \ref surfit_curvs collection 
*/
curv * curvs_first();

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn curv * curvs_last();
    \brief returns last \ref curv in \ref surfit_curvs collection 
*/
curv * curvs_last();

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn int curvs_size();
    \brief returns amount of elements in \ref surfit_curvs collection 
*/
int curvs_size();

SURFIT_EXPORT
/*! \ingroup tcl_curvs
    \fn int curvs_info();
    \brief prints information about all curves in \ref surfit_curvs collection 
*/
int curvs_info();

}; // namespace surfit;

#endif



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

#ifndef __surfit__defareas__
#define __surfit__defareas__

namespace surfit {

class defarea;

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn bool defareas_delall();
    \brief removes all \ref defarea's from \ref surfit_defareas
*/
bool defareas_delall();

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn bool defareas_del(int pos);
    \brief removes \ref defarea from \ref surfit_defareas at "pos" position
*/
bool defareas_del(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn bool defareas_load(const char * filename, const char * defareaname = 0)
    \brief loads \ref defarea from ROFF file (see \ref datafile for details) and adds it to \ref surfit_defareas
*/
bool defareas_load(const char * filename, const char * defareaname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn bool defareas_load_grd(const char * filename, const char * defareaname = 0)
    \brief loads \ref defarea from SURFER grd file (ASCII format) and adds it to \ref surfit_defareas
*/
bool defareas_load_grd(const char * filename, const char * defareaname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn bool defareas_unload(const char * name);
    \brief removes first defarea from \ref surfit_defareas named with "name"
*/
bool defareas_unload(const char * name);

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn defarea * defareas_at(int pos);
    \brief returns \ref defarea at "pos" position from \ref surfit_defareas
*/
defarea * defareas_at(int pos);

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn defarea * defareas_first();
    \brief returns first \ref defarea from \ref surfit_defareas
*/
defarea * defareas_first();

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn defarea * defareas_last();
    \brief returns last \ref defarea from \ref surfit_defareas
*/
defarea * defareas_last();

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn int defareas_size();
    \brief returns amount of defareations in \ref surfit_defareas
*/
int defareas_size();

SURFIT_EXPORT
/*! \ingroup tcl_defareas
    \fn int defareas_info();
    \brief prints information about defareations in \ref surfit_defareas
*/
int defareas_info();

}; // namespace surfit

#endif




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

#ifndef __surfit__defarea_tcl__
#define __surfit__defarea_tcl__

namespace surfit {

class func;
class grid;
class defarea;
class boolvec;
class datafile;

//
// SAVE_LOAD
//

SURFIT_EXPORT
/*! \ingroup tcl_defarea_save_load
    \fn bool defarea_load(const char * filename, const char * defname = 0);
    \brief loads defarea from file. If no defname specified, then first defarea will be loaded.
    \param filename filename
    \param defname name for defarea (optional)
*/
bool defarea_load(const char * filename, const char * defname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_defarea_save_load
    \fn void defarea_unload();
    \brief unloads \ref surfit_defarea from memory
*/
void defarea_unload();

SURFIT_EXPORT
/*! \ingroup tcl_defarea_save_load
    \fn bool defarea_save(const char * filename, const char * defname = 0);
    \brief saves \ref surfit_defarea to file
    \param filename filename
    \param defname name for defarea (optional)
*/
bool defarea_save(const char * filename, const char * defname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_defarea_save_load
    \fn bool defarea_save_grd(const char * filename);
    \brief saves defarea to surfer grd file (ASCII format)
*/
bool defarea_save_grd(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_defarea_save_load
    \fn bool defarea_save_xyz(const char * filename);
    \brief saves defarea to xyz-file (ASCII format)
*/
bool defarea_save_xyz(const char * filename);

//
// math
//

SURFIT_EXPORT
/*! \ingroup tcl_defarea_math
    \fn bool defarea_getValue(REAL x, REAL y);
    \brief calculates \ref surfit_defarea value at point (x,y)
*/
bool defarea_getValue(REAL x, REAL y);

SURFIT_EXPORT
/*! \ingroup tcl_defarea_math
    \fn bool defarea_and(defarea * def);
    \brief makes XOR operation of \ref surfit_defarea with "def" \ref defarea
*/
bool defarea_and(defarea * def);

SURFIT_EXPORT
/*! \ingroup tcl_defarea_math
    \fn bool defarea_not(defarea * def);
    \brief makes NOT operation of \ref surfit_defarea with "def" \ref defarea
*/
bool defarea_not(defarea * def=NULL);

SURFIT_EXPORT
/*! \ingroup tcl_defarea_math
    \fn bool defarea_or(defarea * def);
    \brief makes OR operation of \ref surfit_defarea with "def" \ref defarea
*/
bool defarea_or(defarea * def);

SURFIT_EXPORT
/*! \ingroup tcl_defarea_math
    \fn bool defarea_xor(defarea * def);
    \brief makes XOR operation of \ref surfit_defarea with "def" \ref defarea
*/
bool defarea_xor(defarea * def);



//
// CONVERTING
//

SURFIT_EXPORT
/*! \ingroup tcl_defarea_conv
    \fn bool defarea_to_func();
    \brief makes \ref surfit_func from \ref surfit_defarea
*/
bool defarea_to_func();

SURFIT_EXPORT
/*! \ingroup tcl_defarea_conv
    \fn bool defarea_to_funcs();
    \brief makes \ref surfit_func from \ref surfit_defarea and adds it to \ref surfit_funcs
*/
bool defarea_to_funcs();

SURFIT_EXPORT
/*! \ingroup tcl_defarea_conv
    \fn bool defarea_to_defareas();
    \brief moves \ref surfit_func to \ref surfit_funcs
*/
bool defarea_to_defareas();

//
// OTHER
//

SURFIT_EXPORT
/*! \ingroup tcl_defarea_other
    \fn bool defarea_check();
    \brief checks for \ref surfit_defarea existance
*/
bool defarea_check();

SURFIT_EXPORT
/*! \ingroup tcl_defarea_other
    \fn bool defarea_by_func();
    \brief makes \ref surfit_defarea with the same undefined values as \ref surfit_func
*/
bool defarea_by_func();

SURFIT_EXPORT
/*! \ingroup tcl_defarea_other
    \fn bool defarea_apply_to_func();
    \brief sets undefined values to \ref surfit_func using \ref surfit_defarea
*/
bool defarea_apply_to_func();

SURFIT_EXPORT
/*! \ingroup tcl_defarea_other
    \fn bool defarea_name(const char * new_name, defarea * def = NULL);
    \brief sets name of \ref surfit_defarea or def
*/
bool defarea_name(const char * new_name, defarea * def = NULL);

}; // namespace surfit

#endif




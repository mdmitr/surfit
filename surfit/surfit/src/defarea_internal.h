
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

#ifndef __surfit__defarea_internal__
#define __surfit__defarea_internal__

namespace surfit {

class func;
class grid;
class defarea;
class boolvec;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn bool _defarea_check();
    \brief checks for \ref surfit_defarea existance
*/
bool _defarea_check();

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn bool _defarea_save(defarea * def, const char * filename, const char * defname);
    \brief saves defearea to ROFF file (see \ref datafile for details) in current \ref rw_mode
    \param def \ref defarea class to save
    \param filename data file
    \param defname defarea name
*/
bool _defarea_save(defarea * def, const char * filename, const char * defname);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn bool _defarea_save_df(defarea * def, datafile * df);
    \brief writes defarea tags to \ref datafile
*/
bool _defarea_save_df(defarea * def, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn defarea * _defarea_load(const char * filename, const char * defname, int mode);
    \brief loads defarea from data ROFF file (see \ref datafile for details) in current \ref rw_mode
    \param filename data file
    \param defname name
    \param mode \ref rw_mode
    \param defname name for defarea
*/
defarea * _defarea_load(const char * filename, const char * defname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn defarea * _defarea_load_df(datafile * df, const char * defareaname);
    \brief loads defarea named 'defareaname' from \ref datafile 
*/
defarea * _defarea_load_df(datafile * df, const char * defareaname);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn bool _defarea_load_grd(const char * filename, const char * defareaname)
    \brief loads defarea from SURFER grd file (ASCII format)
*/
defarea * _defarea_load_grd(const char * filename, const char * defareaname); 

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn void _defarea_unload(defarea *& def);
    \brief unloads defarea from memory
*/
bool _defarea_unload(defarea *& def);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn defarea * _get_surfit_defarea();
    \brief returns pointer to \ref surfit_defarea
*/
defarea * _get_surfit_defarea();

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn void _set_surfit_defarea(defarea * def);
    \brief sets \ref surfit_defarea to def
*/
void _set_surfit_defarea(defarea * def);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn defarea * _defarea_by_func(func * fnc);
    \brief makes \ref defarea by \ref func using undefined values
*/
defarea * _defarea_by_func(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn bool _defarea_apply_to_func(defarea * def, func * fnc);
    \brief sets fnc coefficients to \ref undef_value using defarea
*/
bool _defarea_apply_to_func(defarea * def, func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_defarea
    \fn void _defarea_info(defarea * def);
    \brief prints some info about definition area
*/
void _defarea_info(defarea * def);

}; // namespace surfit

#endif




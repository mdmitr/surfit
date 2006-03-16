
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit__mask_tcl__
#define __surfit__mask_tcl__

namespace surfit {

class d_grid;
class boolvec;
class datafile;
class d_mask;

//
// SAVE_LOAD
//

SURFIT_EXPORT
/*! \ingroup tcl_mask_save_load
    \fn bool mask_load(const char * filename, const char * defname = 0);
    \brief loads mask from file. If no defname specified, then first mask will be loaded.
    \param filename filename
    \param defname name for mask (optional)
*/
bool mask_load(const char * filename, const char * defname = 0);

SURFIT_EXPORT
/*! \ingroup tcl_mask_save_load
    \fn bool mask_save(const char * filename, const char * pos = "0");
    \brief saves \ref mask to file
*/
bool mask_save(const char * filename, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_save_load
    \fn bool mask_save_grd(const char * filename, const char * pos = "0");
    \brief saves \ref mask to surfer grd file (ASCII format)
*/
bool mask_save_grd(const char * filename, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_save_load
    \fn bool mask_save_xyz(const char * filename, const char * pos = "0");
    \brief saves \ref mask to xyz-file (ASCII format)
*/
bool mask_save_xyz(const char * filename, const char * pos = "0");

//
// math
//

SURFIT_EXPORT
/*! \ingroup tcl_mask_math
    \fn bool mask_getValue(REAL x, REAL y, const char * pos = "0");
    \brief calculates \ref mask value at point (x,y)
*/
bool mask_getValue(REAL x, REAL y, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_math
    \fn bool mask_and(const char * pos1 = "0", const char * pos2 = "0");
    \brief makes AND operation 
*/
bool mask_and(const char * pos1 = "0", const char * pos2 = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_math
    \fn bool mask_not(const char * pos1 = "0", const char * pos2 = "0");
    \brief makes NOT operation 
*/
bool mask_not(const char * pos1 = "0", const char * pos2 = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_math
    \fn bool mask_or(const char * pos1 = "0", const char * pos2 = "0");
    \brief makes OR operation 
*/
bool mask_or(const char * pos1 = "0", const char * pos2 = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_math
    \fn bool mask_xor(const char * pos1 = "0", const char * pos2 = "0");
    \brief makes XOR operation 
*/
bool mask_xor(const char * pos1 = "0", const char * pos2 = "0");

//
// CONVERTING
//

SURFIT_EXPORT
/*! \ingroup tcl_mask_conv
    \fn bool mask_to_func(const char * pos = "0");
    \brief makes \ref surfit_func from \ref surfit_mask
*/
bool mask_to_func(const char * pos = "0");

//
// OTHER
//

SURFIT_EXPORT
/*! \ingroup tcl_mask_other
    \fn bool mask_by_func(const char * func_pos = "0");
    \brief makes \ref mask with the same undefined values as \ref func have
*/
bool mask_by_func(const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_other
    \fn bool mask_apply_to_func(const char * def_pos = "0", const char * func_pos = "0");
    \brief sets undefined values to \ref func using \ref mask
*/
bool mask_apply_to_func(const char * def_pos = "0", const char * func_pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_other
    \fn const char * mask_getName(const char * pos = "0");
    \brief returns name of \ref mask 
*/
const char * mask_getName(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_mask_other
    \fn bool mask_setName(const char * new_name, const char * pos = "0");
    \brief sets name of \ref mask 
*/
bool mask_setName(const char * new_name, const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_masks
    \fn bool mask_delall();
    \brief removes all \ref mask's from \ref surfit_masks
*/
bool mask_delall();

SURFIT_EXPORT
/*! \ingroup tcl_masks
    \fn bool mask_del(const char * pos = "0");
    \brief removes \ref mask from \ref surfit_masks 
*/
bool mask_del(const char * pos = "0");

SURFIT_EXPORT
/*! \ingroup tcl_masks
    \fn int mask_size();
    \brief returns amount of masks in \ref surfit_masks
*/
int mask_size();

SURFIT_EXPORT
/*! \ingroup tcl_masks
    \fn void masks_info();
    \brief prints information about masks in \ref surfit_masks
*/
void masks_info();

SURFIT_EXPORT
/*! \ingroup tcl_masks
    \fn void surfit_mask_add(d_mask * msk)
    \brief adds d_mask into \ref surfit_masks
*/
void surfit_mask_add(d_mask * msk);

}; // namespace surfit

#endif




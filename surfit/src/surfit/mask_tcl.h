
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

/*! \ingroup tcl_mask_save_load
    \fn bool mask_load(const char * filename, const char * maskname = 0);
    
    \par Tcl syntax:
    mask_load "filename" "maskname"

    \par Description:
    loads \ref d_mask "mask" from surfit datafile. If no maskname specified, then first mask will be loaded.
    \param filename surfit datafile
    \param maskname name for mask (optional)
*/
bool mask_load(const char * filename, const char * maskname = 0);

/*! \ingroup tcl_mask_save_load
    \fn bool mask_save(const char * filename, const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask_save "filename" "mask_name_or_position"

    \par Description:
    saves \ref d_mask "mask" to surfit datafile
*/
bool mask_save(const char * filename, const char * mask_name_or_position = "0");

/*! \ingroup tcl_mask_save_load
    \fn bool mask_save_grd(const char * filename, const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask_save_grd "filename" "mask_name_or_position"

    \par Description:
    saves \ref d_mask "mask" to Surfer grd file (ASCII format)
*/
bool mask_save_grd(const char * filename, const char * mask_name_or_position = "0");

/*! \ingroup tcl_mask_save_load
    \fn bool mask_save_xyz(const char * filename, const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask_save_xyz "filename" "mask_name_or_position"
    
    \par Description:
    saves \ref d_mask "mask" to xyz-file (ASCII format)
*/
bool mask_save_xyz(const char * filename, const char * mask_name_or_position = "0");

//
// math
//

/*! \ingroup tcl_mask_math
    \fn bool mask_getValue(REAL x, REAL y, const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask_getValue x y "mask_name_or_position"

    \par Description:
    calculates \ref d_mask "mask" value at point (x,y)
*/
bool mask_getValue(REAL x, REAL y, const char * mask_name_or_position = "0");

/*! \ingroup tcl_mask_math
    \fn bool mask_and(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");

    \par Tcl syntax:
    mask_and "mask1_name_or_position" "mask2_name_or_position"

    \par Description:
    makes AND operation:
    mask1 = mask1 AND mask2
*/
bool mask_and(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");

/*! \ingroup tcl_mask_math
    \fn bool mask_not(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");

    \par Tcl syntax:
    mask_not "mask1_name_or_position" "mask2_name_or_position"
    
      
    \par Description:
    makes NOT operation:
    mask1 = NOT mask2
*/
bool mask_not(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");

/*! \ingroup tcl_mask_math
    \fn bool mask_or(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");

    \par Tcl syntax:
    mask_or "mask1_name_or_position" "mask2_name_or_position"
    
    \par Description: 
    makes OR operation:
    mask1 = mask1 OR mask2
*/
bool mask_or(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");

/*! \ingroup tcl_mask_math
    \fn bool mask_xor(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");
    
    \par Tcl syntax:
    mask_xor "mask1_name_or_position" "mask2_name_or_position"
      
    \par Description:
    makes XOR operation:
    mask1 = mask1 XOR mask2
*/
bool mask_xor(const char * mask1_name_or_position = "0", const char * mask2_name_or_position = "0");

//
// CONVERTING
//

/*! \ingroup tcl_mask_conv
    \fn bool mask_to_surf(const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask_to_surf "mask_name_or_position"

    \par Description:
    makes \ref d_surf "surface" from \ref d_mask "mask"
*/
bool mask_to_surf(const char * mask_name_or_position = "0");

//
// OTHER
//

/*! \ingroup tcl_mask_other
    \fn bool mask_by_surf(const char * surface_name_or_position = "0");

    \par Tcl syntax:
    mask_by_surf "surface_name_or_position"

    \par Description:
    makes \ref d_mask "mask" from \ref d_surf "surface". Resulting mask will have
    false values for all cells, where surface have undefined values.
*/
bool mask_by_surf(const char * surface_name_or_position = "0");

/*! \ingroup tcl_mask_other
    \fn bool mask_apply_to_surf(const char * mask_name_or_position = "0", const char * surface_name_or_position = "0");

    \par Tcl syntax:
    mask_apply_to_surf "mask_name_or_position" "surface_name_or_position"

    \par Description:
    sets undefined values for all  \ref d_surf "surface" cells where \ref d_mask "mask" have false values.
*/
bool mask_apply_to_surf(const char * mask_name_or_position = "0", const char * surface_name_or_position = "0");

/*! \ingroup tcl_mask_other
    \fn const char * mask_getName(const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask_getName "mask_name_or_position"

    \par Description:
    returns name of the \ref d_mask "mask"
*/
const char * mask_getName(const char * mask_name_or_position = "0");

/*! \ingroup tcl_mask_other
    \fn bool mask_setName(const char * new_name, const char * mask_name_or_position = "0");
    
    \par Tcl syntax:
    mask_setName "new_name" "mask_name_or_position"

    \par Description:
    sets name for the \ref d_mask "mask"
*/
bool mask_setName(const char * new_name, const char * mask_name_or_position = "0");

/*! \ingroup tcl_mask_other
    \fn bool mask_delall();

    \par Tcl syntax:
    mask_delall

    \par Description:
    removes all \ref d_mask "masks" from memory
*/
bool mask_delall();

/*! \ingroup tcl_mask_other
    \fn bool mask_del(const char * mask_name_or_position = "0");

    \par Tcl syntax:
    mask_del "mask_name_or_position"

    \par Description:
    removes \ref d_mask mask from memory
*/
bool mask_del(const char * mask_name_or_position = "0");

/*! \ingroup tcl_mask_other
    \fn int mask_size();

    \par Tcl syntax:
    mask_size

    \par Description:
    returns number of \ref d_mask masks in memory
*/
int mask_size();

/*! \ingroup tcl_mask_other
    \fn void masks_info();

    \par Tcl syntax:
    masks_info

    \par Description:
    prints information about \ref d_mask masks in memory
*/
void masks_info();

}; // namespace surfit

#endif




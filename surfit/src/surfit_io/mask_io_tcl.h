
/*------------------------------------------------------------------------------
 *	$Id: pnts_io_tcl.h 852 2006-08-04 05:19:00Z mishadm $
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

namespace surfit {

/*! \ingroup tcl_mask_save_load
    \fn bool mask_save_grd(const char * filename, const char * mask_name = "*");

    \par Tcl syntax:
    mask_save_grd \ref file "filename" \ref str "mask_name"

    \par Description:
    saves first \ref d_mask "mask" with name matching \ref str "mask_name" to Surfer grd file (ASCII format)

    \par Implemented in library:
    libsurfit_io
*/
bool mask_save_grd(const char * filename, const char * mask_name = "*");

/*! \ingroup tcl_mask_save_load
    \fn bool mask_save_xyz(const char * filename, const char * mask_name = "*");

    \par Tcl syntax:
    mask_save_xyz \ref file "filename" \ref str "mask_name"
    
    \par Description:
    saves first \ref d_mask "mask" with name matching \ref str "mask_name" to xyz-file (ASCII format)

    \par Implemented in library:
    libsurfit_io
*/
bool mask_save_xyz(const char * filename, const char * mask_name = "*");

}; // namespace surfit;


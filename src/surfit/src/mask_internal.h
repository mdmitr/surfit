
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

#ifndef __surfit__mask_internal__
#define __surfit__mask_internal__

namespace surfit {

class d_surf;
class d_grid;
class d_mask;
class boolvec;
class datafile;

//! saves \ref d_mask to surfit \ref datafile 
SURFIT_EXPORT
bool _mask_save(const d_mask * msk, const char * filename);

//! writes \ref d_mask tags to \ref datafile
SURFIT_EXPORT
bool _mask_save_df(const d_mask * msk, datafile * df);

//! loads \ref d_mask from surfit \ref datafile 
SURFIT_EXPORT
d_mask * _mask_load(const char * filename, const char * mskname);

//! loads \ref d_mask named 'maskname' from \ref datafile 
SURFIT_EXPORT
d_mask * _mask_load_df(datafile * df, const char * maskname);

//! loads \ref d_mask from SURFER grd file (ASCII format)
SURFIT_EXPORT
d_mask * _mask_load_grd(const char * filename, const char * maskname); 

//! makes \ref d_mask by \ref d_surf using undefined values
SURFIT_EXPORT
d_mask * _mask_by_surf(const d_surf * srf);

//! sets \ref d_surf coefficients to undef_value using \ref d_mask
SURFIT_EXPORT
bool _mask_apply_to_surf(const d_mask * msk, d_surf * srf);

//! prints some info about \ref d_mask
SURFIT_EXPORT
void _mask_info(const d_mask * msk);

//! adds \ref d_mask into container
SURFIT_EXPORT
void _surfit_mask_add(d_mask * msk);

}; // namespace surfit

#endif





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

#ifndef __surfit_hist_internal_included__
#define __surfit_hist_internal_included__

#include <float.h>

namespace surfit {

class d_hist;
class datafile;
class d_surf;
class d_points;
class bitvec;

/*! \brief reads \ref d_hist from formatted text file
    \return pointer to \ref d_points class
    \param filename filename
    \param minz minimum value for X axis
    \param maxz maximum value for X axis
    \param histname histogram name 
    \param col1 column number in text file for histogram values
    \param mask mask for scanf
    \param grow_by vector's grow factor
    \param skip_lines number of lines to skip header
*/
SURFIT_EXPORT
d_hist * _hist_read(const char * filename, REAL minz, REAL maxz, const char * histname, 
		    int col1, const char * mask, int skip_lines, int grow_by);

//! saves \ref d_hist to formatted text file
SURFIT_EXPORT
bool _hist_write(const d_hist * hist, const char * filename, bool three_columns = false);

//! prints some info about \ref d_hist
SURFIT_EXPORT
void _hist_info(const d_hist * hist);

//! adds \ref d_hist to collection
SURFIT_EXPORT
void _add_surfit_hists(d_hist * hist);

//! adjusts (modifies) surface in the way that the histogram of the resulting surface is close to given histogram
SURFIT_EXPORT
bool _surf_adj_hist(d_surf * srf, const d_hist * hist);

//! makes \ref d_hist from \ref vec
SURFIT_EXPORT
d_hist * _hist_from_vec(const vec * data, REAL minz, REAL maxz, size_t intervs,
			REAL undef_value = FLT_MAX, const bitvec * mask = NULL, const bitvec * mask_undef = NULL);

//! makes \ref d_hist from \ref extvec
SURFIT_EXPORT
d_hist * _hist_from_extvec(const extvec * data, REAL minz, REAL maxz, size_t intervs,
			   REAL undef_value = FLT_MAX, const bitvec * mask = NULL, const bitvec * mask_undef = NULL);

//! makes \ref d_hist from \ref d_surf
SURFIT_EXPORT
d_hist * _hist_from_surf(const d_surf * srf, size_t intervs, REAL from = FLT_MAX, REAL to = FLT_MAX);

//! makes \ref d_hist from \ref d_points
SURFIT_EXPORT
d_hist * _hist_from_points(const d_points * pnts, size_t intervs, REAL from = FLT_MAX, REAL to = FLT_MAX);

//! function for surface adjustment
SURFIT_EXPORT
REAL get_eq_value(const vec * T, const vec * Z, REAL val,
		  REAL surf_minz, REAL surf_maxz,
		  REAL dest_minz, REAL dest_maxz);

//! adjusts (modifies) \ref extvec in the way that the histogram of the resulting surface is close to given histogram
SURFIT_EXPORT
extvec * _extvec_adj_hist(const extvec * X, const d_hist * hst, const bitvec * mask, const bitvec * mask_undef, REAL uval);

}; // namespace surfit;

#endif


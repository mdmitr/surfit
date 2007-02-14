
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

namespace surfit {

class d_hist;
class datafile;
class d_surf;

SURFIT_EXPORT
/*! \ingroup internal
     \fn d_hist * _hist_read(const char * filename, REAL minz, REAL maxz, const char * histname, 
			     int col1, const char * mask, int skip_lines, int grow_by);
    \brief reads points from formatted text file
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
d_hist * _hist_read(const char * filename, REAL minz, REAL maxz, const char * histname, 
		    int col1, const char * mask, int skip_lines, int grow_by);

SURFIT_EXPORT
/*! \ingroup internal
    \fn bool _hist_write(const d_hist * hist, const char * filename);
    \brief saves \ref d_hist to formatted text file
    \param hist pointer to \ref d_hist
    \param filename filename
*/
bool _hist_write(const d_hist * hist, const char * filename);

SURFIT_EXPORT
void _hist_info(const d_hist * hist);

SURFIT_EXPORT
void _add_surfit_hists(d_hist * hist);

SURFIT_EXPORT
bool _surf_histeq(d_surf * srf, const d_hist * hist);

}; // namespace surfit;

#endif


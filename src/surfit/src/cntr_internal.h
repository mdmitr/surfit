
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

#ifndef __surfit_cntr_internal_included__
#define __surfit_cntr_internal_included__

namespace surfit {

class d_cntr;
class datafile;

//! reads \ref d_cntr from formatted text file
SURFIT_EXPORT
d_cntr * _cntr_read(const char * filename, const char * cntrname,
		  int col1, int col2, int col3, int skip_lines,
		  int grow_by, const char * mask);

//! loads \ref d_cntr from surfit datafile
SURFIT_EXPORT
d_cntr * _cntr_load(const char * filename, const char * cntrname);

//! writes \ref d_cntr to formatted text file. 
SURFIT_EXPORT
bool _cntr_write(const d_cntr * contour, const char * filename, const char * mask);

//! writes \ref d_cntr to surfit datafile (see \ref datafile for details)
SURFIT_EXPORT
bool _cntr_save(const d_cntr * contour, const char * filename);

//! writes \ref d_cntr tags to \ref datafile
SURFIT_EXPORT
bool _cntr_save_df(const d_cntr * contour, datafile * df);

//! reads \ref d_cntr tags from \ref datafile
SURFIT_EXPORT
d_cntr * _cntr_load_df(datafile * df, const char * cntrname);

//! prints some info about \ref d_cntr
SURFIT_EXPORT
void _cntr_info(const d_cntr * contour);

//! adds \ref d_cntr to collection
SURFIT_EXPORT
void _add_surfit_cntrs(d_cntr * contour);

//! smooths \ref d_cntr by adding points
SURFIT_EXPORT
bool _cntr_smooth(d_cntr * contour);

}; // namespace surfit;

#endif


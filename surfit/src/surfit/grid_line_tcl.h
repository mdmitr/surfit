
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

#ifndef __surfit_grd_line_tcl_included__
#define __surfit_grd_line_tcl_included__

namespace surfit {

SURFIT_EXPORT
/*! \ingroup tcl_grid_line
    \fn bool grid_line_check();
    checks for \ref surfit_grid_line existance
*/
bool grid_line_check();
	
SURFIT_EXPORT
/*! \ingroup tcl_grid_line
    \fn bool grid_line_write(const char * filename, const char * delimiter);
    saves \ref grid_line to formatted text file. 
*/
bool grid_line_write(const char * filename, const char * delimiter = "\t");

SURFIT_EXPORT
/*! \ingroup tcl_grid_line
    \fn bool grid_line_save(const char * filename, const char * grid_linename = NULL);
    saves \ref grid_line to datafile (binary format). 
*/
bool grid_line_save(const char * filename, const char * grid_linename = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_grid_line
    \fn bool grid_line_unload();
    unloads \ref surfit_grid_line from memory
*/
bool grid_line_unload();

SURFIT_EXPORT
bool trace_grid_line();

}; // namespace surfit;

#endif



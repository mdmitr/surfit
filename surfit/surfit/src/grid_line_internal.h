
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

#ifndef __surfit_grd_line_internal_included__
#define __surfit_grd_line_internal_included__

namespace surfit {

class grid_line;
class curv;
class datafile;

SURFIT_EXPORT
/*! \ingroup internal_grid_line
    \fn bool _grid_line_check();
    \brief checks for \ref surfit_grid_line existance
*/
bool _grid_line_check();

SURFIT_EXPORT
/*! \ingroup internal_grid_line
    \fn bool _grid_line_unload();
    \brief unloads \ref surfit_grid_line from memory
*/
bool _grid_line_unload();

SURFIT_EXPORT
/*! \ingroup internal_grid_line
    \fn bool _grid_line_write(grid_line * contour, const char * filename, const char * mask);
    \brief writes \ref grid_line to formatted text file. 
*/
bool _grid_line_write(grid_line * contour, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_grid_line
    \fn bool _grid_line_save(grid_line * contour, const char * filename, int mode);
    \brief writes \ref grid_line to ROFF file (see \ref datafile for details)
*/
bool _grid_line_save(grid_line * contour, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_grid_line
    \fn void _grid_line_info(grid_line * contour);
    \brief prints some info about \ref grid_line
*/
void _grid_line_info(grid_line * contour);

SURFIT_EXPORT
/*! \ingroup internal_grid_line
    \fn grid_line * _get_surfit_grid_line();
    \brief returns \ref surfit_grid_line
*/
grid_line * _get_surfit_grid_line();

SURFIT_EXPORT
/*! \ingroup internal_grid_line
    \fn void _set_surfit_grid_line(grid_line * contour);
    \brief sets \ref surfit_grid_line
*/
void _set_surfit_grid_line(grid_line * contour);

/*! \ingroup internal_grid_line
    \fn curv * _grid_line_to_curv(grid_line * gline);
    \brief converts \ref grid_line to \ref curv
*/
SURFIT_EXPORT
curv * _grid_line_to_curv(grid_line * gline);

}; // namespace surfit;

#endif



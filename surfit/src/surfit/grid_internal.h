
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

#ifndef __surfit__grid_internal_
#define __surfit__grid_internal_

#include <vector>

namespace surfit {

class datafile;
class d_points;
class d_surf;
class d_grid;

//! checks for \ref surfit_grid existance 
SURFIT_EXPORT
bool _grid_check();

//! saves \ref d_grid to surfit \ref datafile
SURFIT_EXPORT
bool _grid_save(d_grid * grd, const char * filename);

//! saves \ref d_grid to \ref datafile 
SURFIT_EXPORT
bool _grid_save_df(d_grid * grd, datafile * df);

//! loads \ref d_grid from surfit \ref datafile with tag "grid" already readed
SURFIT_EXPORT
bool _grid_load_df_tag_readed(datafile *df, d_grid *& grd);

//! loads \ref d_grid from \ref datafile then "grid" already readed
SURFIT_EXPORT
d_grid * _grid_load_df(datafile * df, const char * grid_name);

//! reads \ref d_grid from \ref datafile
SURFIT_EXPORT
d_grid * _grid_load(const char * filename, const char * gridname);

//! constructs \ref d_grid which covers \ref d_points and consists of Xnodes*Ynodes nodes 
SURFIT_EXPORT
d_grid * _grid_get_for_pnts(d_points * pnts, int Xnodes, int Ynodes, const char * name = NULL);

//! constructs \ref d_grid with steps stepX and stepY and which covers \ref d_points 
SURFIT_EXPORT
d_grid * _grid_get_for_pnts_step(d_points * pnts, REAL stepX, REAL stepY, const char * name = NULL);

//! constructs \ref d_grid which covers \ref d_surf and consists of Xnodes*Ynodes nodes
SURFIT_EXPORT
d_grid * _grid_get_for_surf(d_surf * srf, int Xnodes, int Ynodes, const char * name = NULL);

//! constructs \ref d_grid with steps stepX and stepY which covers \ref d_surf 
SURFIT_EXPORT
d_grid * _grid_get_for_surf_step(d_surf * srf, REAL stepX, REAL stepY, const char * name = NULL);

/*! \brief constructs \ref d_grid
    \param startX X-coordinate of the first node of the grid
    \param endX X-coordinate of the last node of the grid
    \param stepX distance between two neighbour X-nodes 
    \param startY Y-coordinate of the first node of the grid
    \param endY  Y-coordinate of the last node of the grid 
    \param stepY distance between two neighbour Y-nodes 
    \param name name for \ref d_grid (optional)
*/
SURFIT_EXPORT
d_grid * _grid_get(REAL startX, REAL endX, REAL stepX,
                   REAL startY, REAL endY, REAL stepY,
                   const char * name = NULL);

//! returns copy of \ref d_surf's \ref d_grid
SURFIT_EXPORT
d_grid * _grid_from_surf(d_surf * srf, const char * name);

//! returns \ref surfit_grid
SURFIT_EXPORT
d_grid * _get_surfit_grid();

//! sets \ref surfit_grid
SURFIT_EXPORT
void _set_surfit_grid(d_grid * grd);

//! calculates two grids intersection
SURFIT_EXPORT
void _grid_intersect1(const d_grid * grd1, const d_grid * grd2,
		      size_t & x_from, size_t & x_to,
		      size_t & y_from, size_t & y_to);

//! creates new \ref d_grid which is a smaller part of the parent \ref d_grid
SURFIT_EXPORT
d_grid * _create_sub_grid(const d_grid * grd, int x_from, int x_to, int y_from, int y_to);

//! calculates one \ref d_grid from array of grids
SURFIT_EXPORT
d_grid * _grid_get_best( std::vector<d_grid *> * grids );

}; // namespace surfit;

#endif



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

namespace surfit {

class datafile;
class d_points;
class d_surf;
class d_grid;

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_check();
    \brief checks for \ref surfit_grid existance 
*/
bool _grid_check();

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_save(grid * grd, const char * filename);
    \brief saves grid to ROFF file (see \ref datafile for details) 
*/
bool _grid_save(d_grid * grd, const char * filename);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_save_df(grid * grd, datafile * df);
    \brief saves grid to \ref datafile 
*/
bool _grid_save_df(d_grid * grd, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_load_df_tag_readed(datafile *df, grid *& grd);
    \brief loads grid from ROFF file (see \ref datafile for details) from current position 
    with tag "grid" already readed
*/
bool _grid_load_df_tag_readed(datafile *df, d_grid *& grd);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_load_df(datafile * df, const char * grid_name);
    \brief loads grid from \ref datafile 
*/
d_grid * _grid_load_df(datafile * df, const char * grid_name);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_load(const char * filename, const char * gridname);
    \brief reads grid from \ref datafile
    \return pointer to grid class
    \param filename filename
    \param gridname grid name
*/
d_grid * _grid_load(const char * filename, const char * gridname);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_pnts(d_points * pnts, int Xnodes, int Ynodes, const char * name = NULL);
    \brief constructs grid which covers points and consists of Xnodes*Ynodes nodes 
    \return pointer to grid class
    \param name geometry name
    \param Xnodes amount of X-nodes
    \param Ynodes amount of Y-nodes
    \param pnts scattered data-points
*/
d_grid * _grid_get_for_pnts(d_points * pnts, int Xnodes, int Ynodes, const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_pnts_step(d_points * pnts, REAL stepX, REAL stepY, const char * name = NULL);
    \brief constructs grid which covers points and with steps stepX and stepY
    \return pointer to grid class
*/
d_grid * _grid_get_for_pnts_step(d_points * pnts, REAL stepX, REAL stepY, const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_pnts_and_geom(const grid * grd, const d_points * pnts);
    \brief constructs grid which covers points and nodes are coincident with grd
*/
d_grid * _grid_get_for_pnts_and_geom(const d_grid * grd, const d_points * pnts);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_surf(d_surf * srf, int Xnodes, int Ynodes, const char * name = NULL);
    \brief constructs grid which covers surf and consists of Xnodes*Ynodes nodes
*/
d_grid * _grid_get_for_surf(d_surf * srf, int Xnodes, int Ynodes, const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_surf_step(d_surf * srf, REAL stepX, REAL stepY, const char * name = NULL);
    \brief constructs grid with steps stepX and stepY which covers surf 
*/
d_grid * _grid_get_for_surf_step(d_surf * srf, REAL stepX, REAL stepY, const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid* _grid_get(REAL startX, REAL endX, REAL stepX, REAL startY, REAL endY, REAL stepY, const char * name = NULL);
    \brief constructs grid
    \param startX X-coordinate of the first node of the grid
    \param endX X-coordinate of the last node of the grid
    \param stepX distance between two neighbour X-nodes 
    \param startY Y-coordinate of the first node of the grid
    \param endY  Y-coordinate of the last node of the grid 
    \param stepY distance between two neighbour Y-nodes 
    \param name name for geometry (optional)
*/
d_grid * _grid_get(REAL startX, REAL endX, REAL stepX,
                   REAL startY, REAL endY, REAL stepY,
                   const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_from_surf(d_surf * srf, const char * name);
    \brief returns copy of surface srf grid
*/
d_grid * _grid_from_surf(d_surf * srf, const char * name);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _get_surfit_grid();
    \brief returns \ref surfit_grid
*/
d_grid * _get_surfit_grid();

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn void _set_surfit_grid(grid * grd);
    \brief sets \ref surfit_grid
*/
void _set_surfit_grid(d_grid * grd);

SURFIT_EXPORT
void _grid_intersect1(const d_grid * grd1, const d_grid * grd2,
		      size_t & x_from, size_t & x_to,
		      size_t & y_from, size_t & y_to);

SURFIT_EXPORT
d_grid * _create_sub_grid(const d_grid * grd, int x_from, int x_to, int y_from, int y_to);

}; // namespace surfit;

#endif


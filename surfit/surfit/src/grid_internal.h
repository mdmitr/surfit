
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

#ifndef __surfit__grid_internal_
#define __surfit__grid_internal_

namespace surfit {

class datafile;
class task;
class func;
class grid;

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_check();
    \brief checks for \ref surfit_grid existance 
*/
bool _grid_check();

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_save(grid * grd, const char * filename, int mode);
    \brief saves grid to ROFF file (see \ref datafile for details) in active \ref rw_mode 
*/
bool _grid_save(grid * grd, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_save_df(grid * grd, datafile * df);
    \brief saves grid to \ref datafile 
*/
bool _grid_save_df(grid * grd, datafile * df);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn bool _grid_load_df_tag_readed(datafile *df, grid *& grd);
    \brief loads grid from ROFF file (see \ref datafile for details) from current position 
    with tag "grid" already readed
*/
bool _grid_load_df_tag_readed(datafile *df, grid *& grd);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_load_df(datafile * df, const char * grid_name);
    \brief loads grid from \ref datafile 
*/
grid * _grid_load_df(datafile * df, const char * grid_name);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_load(const char * filename, const char * gridname, int mode);
    \brief reads grid from \ref datafile
    \return pointer to grid class
    \param filename filename
    \param gridname grid name
    \param mode rw_mode (0 = binary, 1 = ascii)
*/
grid * _grid_load(const char * filename, const char * gridname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_task(task * tsk, int Xnodes, int Ynodes, const char * name = NULL);
    \brief constructs grid which covers task and consists of Xnodes*Ynodes nodes 
    \return pointer to grid class
    \param name geometry name
    \param Xnodes amount of X-nodes
    \param Ynodes amount of Y-nodes
    \param tsk scattered data-points
*/
grid * _grid_get_for_task(task * tsk, int Xnodes, int Ynodes, const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_task_step(task * tsk, REAL stepX, REAL stepY, const char * name = NULL);
    \brief constructs grid which covers task and with steps stepX and stepY
    \return pointer to grid class
*/
grid * _grid_get_for_task_step(task * tsk, REAL stepX, REAL stepY, const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_task_and_geom(const grid * grd, const task * tsk);
    \brief constructs grid which covers task and nodes are coincident with grd
*/
grid * _grid_get_for_task_and_geom(const grid * grd, const task * tsk);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_func(func * fnc, int Xnodes, int Ynodes, const char * name = NULL);
    \brief constructs grid which covers func and consists of Xnodes*Ynodes nodes
*/
grid * _grid_get_for_func(func * fnc, int Xnodes, int Ynodes, const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_get_for_func_step(func * fnc, REAL stepX, REAL stepY, const char * name = NULL);
    \brief constructs grid with steps stepX and stepY which covers func 
*/
grid * _grid_get_for_func_step(func * fnc, REAL stepX, REAL stepY, const char * name = NULL);

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
grid * _grid_get(REAL startX, REAL endX, REAL stepX,
                 REAL startY, REAL endY, REAL stepY,
                 const char * name = NULL);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _grid_from_func(func * fnc);
    \brief returns copy of function fnc grid
*/
grid * _grid_from_func(func * fnc);

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn grid * _get_surfit_grid();
    \brief returns \ref surfit_grid
*/
grid * _get_surfit_grid();

SURFIT_EXPORT
/*! \ingroup internal_grid
    \fn void _set_surfit_grid(grid * grd);
    \brief sets \ref surfit_grid
*/
void _set_surfit_grid(grid * grd);

}; // namespace surfit;

#endif


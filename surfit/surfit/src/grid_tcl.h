
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

#ifndef __surfit__grid_tcl__
#define __surfit__grid_tcl__

namespace surfit {

class datafile;
class task;
class func;

/////////////////
// save and load

/*! \ingroup tcl_grid_save_load
    \fn bool grid_save(const char * filename);
    \brief saves \ref surfit_grid to file named filename in active \ref rw_mode. 
    This function uses ROFF format (see \ref datafile for details)
*/
bool grid_save(const char * filename);

/*! \ingroup tcl_grid_save_load
    \fn bool grid_load(const char * filename, const char * gridname = NULL);
    \brief loads \ref surfit_grid named 'geomname' from ROFF file (see \ref datafile for details)
    \param filename filename
    \param gridname name
*/
bool grid_load(const char * filename, const char * gridname = NULL);

/*! \ingroup tcl_grid_save_load
    \fn void grid_unload();
    \brief unloads \ref surfit_grid from memory
*/
void grid_unload();

///////////////////
// create

/*! \ingroup tcl_grid_create
    \fn bool grid_auto(REAL stepX, REAL stepY, REAL percent);
    \brief constructs \ref surfit_grid with cells size stepX and stepY, which covers all \ref data.
*/
bool grid_auto(REAL stepX = 0, REAL stepY = 0, REAL percent = 2);

/*! \ingroup tcl_grid_create
    \fn bool grid_auto2(REAL stepX, REAL stepY, REAL percent = 2);
    \brief constructs \ref surfit_grid with cells size stepX and stepY, which covers all \ref data.
    Amount of nodes in each direction is a number equal to \f$ 2^n \f$, where n is a number.
*/
bool grid_auto2(REAL stepX, REAL stepY, REAL percent = 2);

/*! \ingroup tcl_grid_create
    \fn bool grid_get(REAL startX, REAL endX, REAL stepX,
                      REAL startY, REAL endY, REAL stepY,
                      const char * name = NULL);
    \brief constructs \ref surfit_grid
    \param startX X-coordinate of the first node of the grid
    \param endX   X-coordinate of the last node of the grid
    \param stepX  distance between two neighbour X-nodes
    \param startY Y-coordinate of the first node of the grid
    \param endY   Y-coordinate of the last node of the grid
    \param stepY  distance between two neighbour Y-nodes 
    \param name   name for grid (optional)
*/
bool grid_get(REAL startX, REAL endX, REAL stepX,
              REAL startY, REAL endY, REAL stepY,
              const char * name = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get2(REAL startX, REAL endX, REAL stepX,
                      REAL startY, REAL endY, REAL stepY,
                      const char * name = NULL);
    \brief constructs \ref surfit_grid 
    Amount of nodes in each direction is a number equal to \f$ 2^n \f$, where n is a number.
    \param startX X-coordinate of the first node of the grid
    \param endX   X-coordinate of the last node of the grid
    \param stepX  distance between two neighbour X-nodes
    \param startY Y-coordinate of the first node of the grid
    \param endY   Y-coordinate of the last node of the grid
    \param stepY  distance between two neighbour Y-nodes 
    \param name   name for grid (optional)
*/
bool grid_get2(REAL startX, REAL endX, REAL stepX,
               REAL startY, REAL endY, REAL stepY,
               const char * name = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_for_task(int Xnodes, int Ynodes, const char * name = NULL);
    \brief constructs \ref surfit_grid which covers \ref surfit_task, and consists of Xnodes*Ynodes nodes. 
*/
bool grid_get_for_task(int Xnodes, int Ynodes, const char * name = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_for_task_step(REAL stepX, REAL stepY, const char * name = NULL);
    \brief constructs \ref surfit_grid which covers \ref surfit_task, with steps stepX and stepY. 
*/
bool grid_get_for_task_step(REAL stepX, REAL stepY, const char * name = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_from_func(const char * name = NULL);
    \brief constructs \ref surfit_grid equal to \ref surfit_func grid
*/
bool grid_get_from_func(const char * name = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_for_func(int Xnodes, int Ynodes, const char * name = NULL);
    \brief constructs \ref surfit_grid which covers \ref surfit_task and nodes are 
    coincident with grid of \ref surfit_func
*/
bool grid_get_for_func(int Xnodes, int Ynodes, const char * name = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_for_func_step(REAL stepX, REAL stepY, const char * name = NULL);
    \brief constructs \ref surfit_grid with steps stepX and stepY and covers \ref surfit_func 
*/
bool grid_get_for_func_step(REAL stepX, REAL stepY, const char * name = NULL);

/////////////////
// other

/*! \ingroup tcl_grid_other
    \fn bool grid_check();
    \brief checks for \ref surfit_grid existance 
*/
bool grid_check();

/*! \ingroup tcl_grid_other
    \fn void grid_info();
    \brief prints \ref surfit_grid parametes
*/
void grid_info();

/*! \ingroup tcl_grid_other
    \fn int grid_getCountX();
    \brief returns the amount of X-nodes for \ref surfit_grid
*/
int grid_getCountX();

/*! \ingroup tcl_grid_other
    \fn int grid_getCountY();
    \brief returns the amount of Y-nodes for \ref surfit_grid
*/
int grid_getCountY();

/*! \ingroup tcl_grid_other
    \fn REAL grid_getCoordNodeX(int i);
    \brief returns X-coordinate of i-th node for \ref surfit_grid
*/
REAL grid_getCoordNodeX(int i);

/*! \ingroup tcl_grid_other
    \fn REAL grid_getCoordNodeY(int j);
    \brief returns Y-coordinate of j-th node for \ref surfit_grid
*/
REAL grid_getCoordNodeY(int j);

/*! \ingroup tcl_grid_other
    \fn REAL grid_getStepX();
    \brief returns X-step of \ref surfit_grid
*/
REAL grid_getStepX();

/*! \ingroup tcl_grid_other
    \fn REAL grid_getStepY();
    \brief returns Y-step of \ref surfit_grid
*/
REAL grid_getStepY();
 
}; // namespace surfit;

#endif


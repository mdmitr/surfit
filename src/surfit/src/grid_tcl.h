
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

#ifndef __surfit__grid_tcl__
#define __surfit__grid_tcl__

namespace surfit {

class datafile;

/////////////////
// save and load

/*! \ingroup tcl_grid_save_load
    \fn bool grid_save(const char * filename);
    
    \par Tcl syntax:
    grid_save "filename"

    \par Description:
    saves \ref d_grid "grid" to surfit datafile. 

    \param filename surfit datafile
*/
bool grid_save(const char * filename);

/*! \ingroup tcl_grid_save_load
    \fn bool grid_load(const char * filename, const char * gridname = NULL);

    \par Tcl syntax:
    grid_load "filename" "gridname"

    \par Description:
    loads \ref d_grid "grid" with name "gridname" from surfit datafile. If no
    gridname specified, then loads first \ref d_grid "grid" from file.
    
    \param filename surfit datafile
    \param gridname name of \ref d_grid "grid"
*/
bool grid_load(const char * filename, const char * gridname = NULL);

/*! \ingroup tcl_grid_save_load
    \fn void grid_unload();

    \par Tcl syntax:
    grid_unload

    \par Description:
    unloads \ref d_grid "grid" from memory
*/
void grid_unload();

///////////////////
// create

/*! \ingroup tcl_grid_create
    \fn bool grid(REAL stepX = 0, REAL stepY = 0, REAL percent = 2, const char * gridname = NULL);

    \par Tcl syntax:
    grid stepX stepY percent

    \par Description:
    constructs \ref d_grid "grid" with cells size stepX and stepY. Resulting grid will
    cover all loaded datasets with overcome border.

    \param stepX cell length in X direction
    \param stepY cell length in Y direction
    \param percent border length in percent
    \param gridname name of \ref d_grid "grid"
*/
bool grid(REAL stepX = 0, REAL stepY = 0, REAL percent = 2, const char * gridname = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid2(REAL stepX = 0, REAL stepY = 0, REAL percent = 2, const char * gridname = NULL);

    \par Tcl syntax:
    grid2 stepX stepY percent

    \par Description:
    constructs \ref d_grid "grid" with cells size stepX and stepY. Resultin grid will
    cover all loaded datasets with overcome border.   
    Number of nodes in each direction is a number equal to \f$ 2^n \f$, where n is 
    an integer number.

    \param stepX cell length in X direction
    \param stepY cell length in Y direction
    \param percent border length in percent
    \param gridname name of \ref d_grid "grid"
*/
bool grid2(REAL stepX=0, REAL stepY=0, REAL percent = 2, const char * gridname = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get(REAL startX, REAL endX, REAL stepX,
                      REAL startY, REAL endY, REAL stepY,
                      const char * gridname = NULL);

    \par Tcl syntax:
    grid_get startX endX stepX startY endY stepY "gridname"

    \par Description:
    constructs \ref d_grid "grid"

    \param startX X-coordinate of the first node of the grid
    \param endX   X-coordinate of the last node of the grid
    \param stepX  distance between two neighbour X-nodes
    \param startY Y-coordinate of the first node of the grid
    \param endY   Y-coordinate of the last node of the grid
    \param stepY  distance between two neighbour Y-nodes 
    \param gridname   name for grid (optional)
*/
bool grid_get(REAL startX, REAL endX, REAL stepX,
              REAL startY, REAL endY, REAL stepY,
              const char * gridname = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get2(REAL startX, REAL endX, REAL stepX,
                       REAL startY, REAL endY, REAL stepY,
                       const char * gridname = NULL);
  
    \par Tcl syntax:
    grid_get startX endX stepX startY endY stepY "name"

    \par Description:
    constructs \ref d_grid "grid".
    Number of nodes in each direction is a number equal to \f$ 2^n \f$, where n is 
    an integer number.

    \param startX X-coordinate of the first node of the grid
    \param endX   X-coordinate of the last node of the grid
    \param stepX  distance between two neighbour X-nodes
    \param startY Y-coordinate of the first node of the grid
    \param endY   Y-coordinate of the last node of the grid
    \param stepY  distance between two neighbour Y-nodes 
    \param gridname   name for grid (optional)
*/
bool grid_get2(REAL startX, REAL endX, REAL stepX,
               REAL startY, REAL endY, REAL stepY,
               const char * gridname = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_for_pnts(int Xnodes, int Ynodes, const char * points_name = "*", const char * gridname = NULL);

    \par Tcl syntax:
    grid_get_for_pnts Xnodex Ynodes "points_name" "gridname"

    \par Description:
    constructs \ref d_grid "grid" which covers \ref d_points "points", and consists of Xnodes*Ynodes nodes. 
*/
bool grid_get_for_pnts(int Xnodes, int Ynodes, const char * points_name = "*", const char * gridname = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_for_pnts_step(REAL stepX, REAL stepY, const char * points_name = "*", const char * gridname = NULL);
    
    \par Tcl syntax:
    grid_get_for_pnts_step steX stepY "points_name" "gridname" 

    \par Description:
    constructs \ref d_grid "grid" with cell size stepX and stepY. Resulting grid will
    cover \ref d_points "points" dataset. 
*/
bool grid_get_for_pnts_step(REAL stepX, REAL stepY, const char * points_name = "*", const char * gridname = NULL);

/*! \ingroup tcl_grid_create
    \fn bool grid_get_from_surf(const char * surface_name = "*", const char * gridname = NULL);

    \par Tcl syntax:
    grid_get_from_surf

    \par Description:
    constructs \ref d_grid "grid" equal to \ref d_surf "surface" grid
*/
bool grid_get_from_surf(const char * surface_name = "*", const char * gridname = NULL);

/////////////////
// other

/*! \ingroup tcl_grid_other
    \fn bool grid_check();

    \par Tcl syntax:
    grid_check

    \par Description:
    checks for \ref d_grid "grid" existance 
*/
bool grid_check();

/*! \ingroup tcl_grid_other
    \fn void grid_info();

    \par Tcl syntax:
    grid_info

    \par Description:
    prints \ref d_grid "grid" parametes
*/
void grid_info();

/*! \ingroup tcl_grid_other
    \fn int grid_getCountX();
    
    \par Tcl syntax:
    grid_getCountX

    \par Description:
    returns the number of X-nodes for \ref d_grid "grid"
*/
int grid_getCountX();

/*! \ingroup tcl_grid_other
    \fn void grid_setCountX(int countX);

    \par Tcl syntax:
    grid_setCountX countX

    \par Description:
    sets the number of X-nodes for \ref d_grid "grid"
*/
bool grid_setCountX(int countX);

/*! \ingroup tcl_grid_other
    \fn int grid_getCountY();

    \par Tcl syntax:
    grid_getCountY

    \par Description:
    returns the amount of Y-nodes for \ref d_grid "grid"
*/
int grid_getCountY();

/*! \ingroup tcl_grid_other
    \fn void grid_setCountY(int countY);

    \par Tcl syntax:
    grid_setCountY countY
    
    \par Description:
    sets the amount of Y-nodes for \ref d_grid "grid"
*/
bool grid_setCountY(int countY);

/*! \ingroup tcl_grid_other
    \fn REAL grid_getCoordNodeX(int i);

    \par Tcl syntax:
    grid_getCoordNodeX i
    
    \par Description:
    returns X-coordinate of i-th node for \ref d_grid "grid"
*/
REAL grid_getCoordNodeX(int i);

/*! \ingroup tcl_grid_other
    \fn REAL grid_getCoordNodeY(int j);

    \par Tcl syntax:
    grid_getCoordNodeY j

    \par Description:
    returns Y-coordinate of j-th node for \ref d_grid "grid"
*/
REAL grid_getCoordNodeY(int j);

/*! \ingroup tcl_grid_other
    \fn REAL grid_getStepX();

    \par Tcl syntax:
    grid_getStepX

    \par Description:
    returns X-step of \ref d_grid "grid"
*/
REAL grid_getStepX();

/*! \ingroup tcl_grid_other
    \fn REAL grid_getStepY();

    \par Tcl syntax:
    grid_getStepY

    \par Description:
    returns Y-step of \ref d_grid "grid"
*/
REAL grid_getStepY();
 
}; // namespace surfit;

#endif



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
%{
#include "grid_tcl.h"
#include "grid_user.h"
%}

namespace surfit {

//
// 2D
//

//saveload
bool grid_save(const char *filename);
bool grid_load(const char *filename, const char *gridname=NULL);
void grid_unload();
//contruction
bool grid(REAL stepX=0, REAL stepY=0, REAL percent=2);
bool grid2(REAL stepX=0, REAL stepY=0, REAL percent=2);
bool grid_get(REAL startX, REAL endX, REAL stepX, REAL startY, REAL endY, REAL stepY, const char *name=NULL);
bool grid_get2(REAL startX, REAL endX, REAL stepX, REAL startY, REAL endY, REAL stepY, const char *name=NULL);
bool grid_get_for_pnts(int Xnodes, int Ynodes, const char *name=NULL, const char * pos = "0");
bool grid_get_for_pnts_step(REAL stepX, REAL stepY, const char *name=NULL, const char * pos = "0");
bool grid_get_from_surf(const char * pos = "0");
bool grid_get_for_surf(int Xnodes, int Ynodes, const char *name=NULL);
bool grid_get_for_surf_step(REAL stepX, REAL stepY, const char *name=NULL);
//other
bool grid_check();
void grid_info();
int grid_getCountX();
bool grid_setCountX(int countX);
int grid_getCountY();
bool grid_setCountY(int countY);
REAL grid_getCoordNodeX(int i);
REAL grid_getCoordNodeY(int j);
REAL grid_getStepX();
REAL grid_getStepY();

int basis_cnt;

}; // namespace surfit;


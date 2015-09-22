
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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


namespace surfit {

/*! \ingroup tcl_surf_save_load
    \fn bool surf_load_png(const char * filename, const char * surfname = 0,
			   REAL minz = 0, REAL maxz = 0, 
			   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1)

    \par Tcl syntax:
    surf_load_png "filename" "surfname" 

    \par Description:
    loads surface from PNG image file
*/
bool surf_load_png(const char * filename, const char * surfname = 0,
		   REAL minz = 0, REAL maxz = 0, 
		   REAL startX = 0, REAL startY = 0, REAL stepX = 1, REAL stepY = 1);

};

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

#ifndef __surfit_grd_line_included__
#define __surfit_grd_line_included__

#include "data.h"

#include <vector> // for floodfill

namespace surfit {

class grid;    // for floodfill
class intvec;  // for floodfill
class boolvec; // for floodfill
class bitvec;  // for floodfill

/*! \class grid_line
    \brief \ref grid based line
    This simple class describes line passing between cells. 
    Each line described with two cells (first and second).
    See \ref tcl_grid_line "Tcl commands" for \ref grid_line.
    
    Loading this class into surfit memory have no effect on functional sequence (see \ref data)
*/
class SURFIT_EXPORT grid_line : public data {
public:
	/*! constructor
	    \param ifirst_begin pointer to begin of array of first cell-numbers 
	    \param ifirst_end pointer to end of array of first cell-numbers 
	    \param isecond_begin pointer to begin of array of second cell-numbers 
	    \param isecond_end pointer to end of array of second cell-numbers 
	*/
	grid_line(int * ifirst_begin,  int * ifirst_end,
		  int * isecond_begin, int * isecond_end);

	//! destructor
	~grid_line();

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! returns amount of grid lines
	int size() const;

	//! adds another grid_line
	void add(int *& ifirst_begin,  int *& ifirst_end,
		 int *& isecond_begin, int *& isecond_end);
	
	//! adds another grid_line
	void add(grid_line * line);

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! sort :)
	void sort();
	//! compress :)
	void compress();

	//! pointer to begin of array of first cell-numbers 
	int * first_begin;
	//! pointer to end of array of first cell-numbers 
	int * first_end;
	//! pointer to begin of array of second cell-numbers 
	int * second_begin;
	//! pointer to end of array of second cell-numbers 
	int * second_end;

	//! pointer to begin of array of sorted first cell-numbers 
	int ** sort_by_first_begin;
	//! pointer to end of array of sorted first cell-numbers 
	int ** sort_by_first_end;
	//! pointer to begin of array of sorted second cell-numbers 
	int ** sort_by_second_begin;
	//! pointer to end of array of sorted second cell-numbers 
	int ** sort_by_second_end;
};

SURFIT_EXPORT
void fault_points_D1(int n, int m, int NN, int MM, 
		     grid_line * fault,
		     bool & first_x, bool & second_x, 
		     bool & first_y, bool & second_y,
		     int offset_x = 0, int offset_y = 0);

SURFIT_EXPORT
void fault_points_D2(int n, int m, int NN, int MM, 
		     grid_line * fault,
		     bool & first_x,  bool & second_x,  bool & third_x, 
		     bool & first_xx, bool & second_xx,
		     bool & first_yy, bool & second_yy,
		     bool & first_y,  bool & second_y,  bool & third_y,
		     int offset_x = 0, int offset_y = 0);

SURFIT_EXPORT
bool check_for_node(grid_line * fault, int nn);

SURFIT_EXPORT
bool check_for_pair(grid_line * fault, int nn1, int nn2);

SURFIT_EXPORT
void flood_fill(grid * grd,
		grid_line * line, 
		std::vector<short int> * data,
		int fill_pos,
		short int fill_val,
		bitvec * mask_undefined);

SURFIT_EXPORT
void flood_fill_boolvec(grid * grd,
			grid_line * line, 
			boolvec * data,
			int fill_pos,
			bitvec * mask_undefined);

SURFIT_EXPORT
void fill_all_areas(std::vector<short int> *& flood_areas, 
		    grid * grd, 
		    grid_line * line, 
		    int & flood_areas_cnt,
		    bitvec * mask_undefined);

SURFIT_EXPORT
std::vector<int> * nodes_in_area(grid_line * line, grid * grd, bitvec * mask_undefined);

}; // namespace surfit;

#endif


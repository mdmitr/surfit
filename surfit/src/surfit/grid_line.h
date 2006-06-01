
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

#ifndef __surfit_grd_line_included__
#define __surfit_grd_line_included__

#include "surfit_data.h"

#include <vector> // for floodfill

namespace surfit {

class d_grid;    // for floodfill
class boolvec; // for floodfill
class bitvec;  // for floodfill
class grid_line;
class d_area;
class d_curv;

SURFIT_EXPORT
grid_line * create_grid_line(std::vector<size_t> * ifirst, std::vector<size_t> * isecond);

/*! \class grid_line
    \brief \ref grid based line
    This simple class describes line passing between cells. 
    Each line described with two cells (first and second).
    See \ref tcl_grid_line "Tcl commands" for \ref grid_line.
    
    Loading this class into surfit memory have no effect on functional sequence (see \ref data)
*/
class SURFIT_EXPORT grid_line : public data {
protected:
	/*! constructor
	    \param ifirst_begin pointer to begin of array of first cell-numbers 
	    \param ifirst_end pointer to end of array of first cell-numbers 
	    \param isecond_begin pointer to begin of array of second cell-numbers 
	    \param isecond_end pointer to end of array of second cell-numbers 
	*/
	grid_line(std::vector<size_t> * ifirst, std::vector<size_t> * isecond);

	//! destructor
	~grid_line();

public:

	friend SURFIT_EXPORT
	grid_line * create_grid_line(std::vector<size_t> * ifirst, std::vector<size_t> * isecond);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! returns amount of grid lines
	size_t size() const;

	//! adds another grid_line
	void add(std::vector<size_t> *& ifirst, std::vector<size_t> *& isecond);
	
	//! adds another grid_line
	void add(grid_line * line);

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! sort :)
	void sort();
	//! compress :)
	void compress();

	//! pointer to array of first cell-numbers 
	std::vector<size_t> * first;
	//! pointer to array of second cell-numbers 
	std::vector<size_t> * second;
	
	//! pointer to begin of array of sorted first cell-numbers 
	std::vector<size_t>::iterator * sort_by_first_begin;
	//! pointer to end of array of sorted first cell-numbers 
	std::vector<size_t>::iterator * sort_by_first_end;
	//! pointer to begin of array of sorted second cell-numbers 
	std::vector<size_t>::iterator * sort_by_second_begin;
	//! pointer to end of array of sorted second cell-numbers 
	std::vector<size_t>::iterator * sort_by_second_end;
};

SURFIT_EXPORT
void fault_points_D1(size_t n, size_t m, size_t NN, size_t MM, 
		     grid_line * fault,
		     bool & first_x, bool & second_x, 
		     bool & first_y, bool & second_y,
		     size_t offset_x = 0, size_t offset_y = 0);

SURFIT_EXPORT
void fault_points_D2(size_t n, size_t m, size_t NN, size_t MM, 
		     grid_line * fault,
		     bool & first_x,  bool & second_x,  bool & third_x, 
		     bool & first_xx, bool & second_xx,
		     bool & first_yy, bool & second_yy,
		     bool & first_y,  bool & second_y,  bool & third_y,
		     size_t offset_x = 0, size_t offset_y = 0);

SURFIT_EXPORT
bool check_for_node(grid_line * fault, size_t nn);

SURFIT_EXPORT
bool check_for_pair(grid_line * fault, size_t nn1, size_t nn2);

SURFIT_EXPORT
void flood_fill(d_grid * grd,
		grid_line * line, 
		std::vector<short int> * data,
		size_t fill_pos,
		short int fill_val,
		const bitvec * mask_undefined);

SURFIT_EXPORT
void flood_fill_boolvec(d_grid * grd,
			grid_line * line, 
			boolvec * data,
			size_t fill_pos,
			const bitvec * mask_undefined);

SURFIT_EXPORT
void fill_all_areas(std::vector<short int> *& flood_areas, 
		    d_grid * grd, 
		    grid_line * line, 
		    int & flood_areas_cnt,
		    const bitvec * mask_undefined);

SURFIT_EXPORT
std::vector<size_t> * nodes_in_curv(grid_line * line, d_grid * grd, bitvec * mask_undefined = NULL);

SURFIT_EXPORT
bitvec * nodes_in_curv_mask(grid_line * line, d_grid * grd, bitvec * mask_undefined = NULL);

SURFIT_EXPORT
bitvec * nodes_in_curv_mask(const d_curv * crv, d_grid * grd, bitvec * mask_undefined = NULL);

SURFIT_EXPORT
bitvec * nodes_in_area_mask(const d_area * area, d_grid * grd, bitvec * mask_undefined = NULL);

SURFIT_EXPORT
grid_line * trace_undef_grd_line(const bitvec * mask_undefined, size_t NN);

}; // namespace surfit;

#endif


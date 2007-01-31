
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
#include "shortvec.h"

#include <vector> // for floodfill

namespace surfit {

class d_grid;    // for floodfill
class boolvec; // for floodfill
class bitvec;  // for floodfill
class grid_line;
class d_area;
class d_curv;

#ifdef XXL
//#include <stxxl>
//typedef stxxl::VECTOR_GENERATOR<size_t,2,2,128*1024>::result grid_line_vec;
typedef std::vector<size_t> grid_line_vec;
#else
typedef std::vector<size_t> grid_line_vec;
#endif

SURFIT_EXPORT
grid_line * create_grid_line(size_t iNN, size_t iMM, grid_line_vec * ifirst, grid_line_vec * isecond);

/*! \class grid_line
    \brief \ref grid based line
    This simple class describes lines passing between cells. 
    
	Each line described with two cells (first and second). To describe cell it is
	necessary to give cell number. grid_line uses extended grid.

    
    
*/
class SURFIT_EXPORT grid_line : public data {
protected:
	/*! constructor
	    \param iNN number of cells in OX direction
	    \param iMM number of cells in OY direction
	    \param ifirst pointer to array of first cell-numbers 
	    \param isecond pointer to array of second cell-numbers 
	*/
	grid_line(size_t iNN, size_t iMM, grid_line_vec * ifirst, grid_line_vec * isecond);

	//! destructor
	~grid_line();

public:

	friend SURFIT_EXPORT
	grid_line * create_grid_line(size_t iNN, size_t iMM, 
				     grid_line_vec * ifirst, grid_line_vec * isecond);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! returns amount of grid lines
	size_t size() const;

	//! adds another grid_line
	void add(grid_line_vec *& ifirst, grid_line_vec *& isecond);
	
	//! adds another grid_line
	void add(grid_line * line);

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! sort :)
	void sort();
	//! compress :)
	void compress();

	class cell_finder {
	public:
		cell_finder(size_t ipos, const grid_line * grd_line);

		bool find_next(size_t & near_cell);

	private:
		size_t pos, NN, MM;
		size_t ** find_from_first;
		size_t ** find_to_first;
		size_t ** find_from_second;
		size_t ** find_to_second;
		size_t ** ptr;
		size_t * it;
		const grid_line_vec * first;
		const grid_line_vec * second;
	};

	friend class cell_finder;

	cell_finder get_cell_finder(size_t pos) const;
	bool check_for_node(size_t pos) const;
	bool check_for_pair(size_t pos1, size_t pos2) const;
	
	void get_minmax(size_t & min_i, size_t & max_i, 
			size_t & min_j, size_t & max_j) const;
	
	void resize(size_t move_i, size_t move_j, size_t newNN, size_t newMM, 
		    bool minus_i, bool minus_j);

	size_t get_first_cell(size_t pos) const;
	size_t get_second_cell(size_t pos) const;
	
protected:

	//! number of cells in OX direction
	size_t NN;
	//! number of cells in OY direction
	size_t MM;

	//! pointer to begin of array of sorted first cell-numbers 
	size_t ** sort_by_first_begin;
	//! pointer to end of array of sorted first cell-numbers 
	size_t ** sort_by_first_end;
	//! pointer to begin of array of sorted second cell-numbers 
	size_t ** sort_by_second_begin;
	//! pointer to end of array of sorted second cell-numbers 
	size_t ** sort_by_second_end;

	//! pointer to array of first cell-numbers 
	grid_line_vec * first;
	//! pointer to array of second cell-numbers 
	grid_line_vec * second;

};

SURFIT_EXPORT
void fault_points_D1(size_t n, size_t m, size_t NN, size_t MM, 
		     grid_line * fault,
		     bool & first_x, bool & second_x, 
		     bool & first_y, bool & second_y,
		     size_t offset_x = 0, size_t offset_y = 0);

SURFIT_EXPORT
void fault_points_D1_aniso(size_t n, size_t m, size_t NN, size_t MM, 
			   grid_line * fault,
			   bool & first_x, bool & second_x, 
			   bool & first_y, bool & second_y,
			   bool & first_xy, bool & first_yx,
			   bool & second_xy, bool & second_yx,
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
void flood_fill(d_grid * grd,
		grid_line * line, 
		shortvec * data,
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
void fill_all_areas(shortvec *& flood_areas, 
		    d_grid * grd, 
		    grid_line * line, 
		    int & flood_areas_cnt,
		    const bitvec * mask_undefined);

SURFIT_EXPORT
bitvec * nodes_in_curv_mask(grid_line * line, const d_grid * grd, bitvec * mask_undefined = NULL);

SURFIT_EXPORT
bitvec * nodes_in_curv_mask(const d_curv * crv, d_grid * grd, bitvec * mask_undefined = NULL);

SURFIT_EXPORT
bitvec * nodes_in_area_mask(const d_area * area, d_grid * grd, bitvec * mask_undefined = NULL);

SURFIT_EXPORT
grid_line * trace_undef_grd_line(const bitvec * mask_undefined, size_t NN);

}; // namespace surfit;

#endif


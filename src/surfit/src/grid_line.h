
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
#include "sizetvec.h"

#include <vector> // for floodfill

namespace surfit {

class d_grid;    // for floodfill
class boolvec; // for floodfill
class bitvec;  // for floodfill
class grid_line;
class d_area;
class d_curv;

//! struct for comparsion of two numbers
struct nums_less_compare
{
	//! constructor
	nums_less_compare(const sizetvec * idata)
	{
		data = idata;
	}

	//! operator for comparsion
	bool operator ()( size_t left, size_t right )
	{
		return ((*data)(left) < (*data)(right));
	}

private:

	//! data for comparsion
	const sizetvec * data;
};

//! constructor for \ref grid_line 
SURFIT_EXPORT
grid_line * create_grid_line(size_t iNN, size_t iMM, sizetvec * ifirst, sizetvec * isecond);

/*! \class grid_line
    \brief \ref d_grid based line
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
	grid_line(size_t iNN, size_t iMM, sizetvec * ifirst, sizetvec * isecond);

	//! destructor
	~grid_line();

public:

	friend SURFIT_EXPORT
	grid_line * create_grid_line(size_t iNN, size_t iMM, 
				     sizetvec * ifirst, sizetvec * isecond);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;

	//! returns amount of grid lines
	size_t size() const;

	//! adds another grid_line
	void add(sizetvec *& ifirst, sizetvec *& isecond);
	
	//! adds another grid_line
	void add(grid_line * line);

	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! sort :)
	void sort();
	//! compress :)
	void compress();

	//! special class for fast cells searching
	class cell_finder {

	public:
		//! constructor
		cell_finder(size_t ipos, const grid_line * grd_line);

		//! returns true if next cell was founded
		bool find_next(size_t & near_cell);

	private:
		size_t pos;
		
		//! number of grid nodes in OX direction
		size_t NN;
		//! number of grid nodes in OY direction
		size_t MM;

		//! pointer to grid_line's sorted first cells
		const sizetvec * sorted_first;
		//! pointer to grid_line's sorted second cells
		const sizetvec * sorted_second;
		
		//! pointer to grid_line's first cells
		const sizetvec * first;
		//! pointer to grid_line's second cells
		const sizetvec * second;

		sizetvec::const_iterator ptr;

		//! pointer for the last founded first cell
		sizetvec::const_iterator last_first;
		//! pointer for the last founded second cell
		sizetvec::const_iterator last_second;
	};

	friend class cell_finder;

	//! returns structure for fast finding of cells
	cell_finder get_cell_finder(size_t pos) const;

	//! returns true if given node is a part of grid_line
	bool check_for_node(size_t pos) const;

	//! returns true if given nodes are a part of grid_line
	bool check_for_pair(size_t pos1, size_t pos2) const;
	
	//! returns rect for grid_line
	void get_minmax(size_t & min_i, size_t & max_i, 
			size_t & min_j, size_t & max_j) const;
	
	//! moves and resizing grid_line
	void resize(size_t move_i, size_t move_j, size_t newNN, size_t newMM, 
		    bool minus_i, bool minus_j);

	//! returns number of the first cell of the grid_line sect
	size_t get_first_cell(size_t pos) const;
	//! returns number of the second cell of the grid_line sect
	size_t get_second_cell(size_t pos) const;
	
protected:

	//! number of cells in OX direction
	size_t NN;
	//! number of cells in OY direction
	size_t MM;

	//! pointer to array of first cell-numbers 
	sizetvec * first;
	//! pointer to array of second cell-numbers 
	sizetvec * second;

	//! pointer to array of sorted first cells
	sizetvec * sorted_first;
	//! pointer to array of sorted second cells
	sizetvec * sorted_second;

};

//! special function for \ref f_completer for taking faults into account
SURFIT_EXPORT
void fault_points_D1(size_t n, size_t m, size_t NN, size_t MM, 
		     const grid_line * fault,
		     bool & first_x, bool & second_x, 
		     bool & first_y, bool & second_y,
		     size_t offset_x = 0, size_t offset_y = 0);

//! special function for \ref f_completer for taking faults into account
SURFIT_EXPORT
void fault_points_D1_aniso(size_t n, size_t m, size_t NN, size_t MM, 
			   const grid_line * fault,
			   bool & first_x, bool & second_x, 
			   bool & first_y, bool & second_y,
			   bool & first_xy, bool & first_yx,
			   bool & second_xy, bool & second_yx,
			   size_t offset_x = 0, size_t offset_y = 0);

//! special function for \ref f_completer for taking faults into account
SURFIT_EXPORT
void fault_points_D2(size_t n, size_t m, size_t NN, size_t MM, 
		     const grid_line * fault,
		     bool & first_x,  bool & second_x,  bool & third_x, 
		     bool & first_xx, bool & second_xx,
		     bool & first_yy, bool & second_yy,
		     bool & first_y,  bool & second_y,  bool & third_y,
		     size_t offset_x = 0, size_t offset_y = 0);

//! special function for \ref f_completer for taking faults into account
SURFIT_EXPORT
void flood_fill(d_grid * grd,
		const grid_line * line, 
		shortvec * data,
		size_t fill_pos,
		short int fill_val,
		const bitvec * mask_undefined);

//! floodfill algorithm for boolvec
SURFIT_EXPORT
void flood_fill_boolvec(d_grid * grd,
			grid_line * line, 
			boolvec * data,
			size_t fill_pos,
			const bitvec * mask_undefined);

//! floodfill algorithm, fills whole rect
SURFIT_EXPORT
void fill_all_areas(shortvec *& flood_areas, 
		    d_grid * grd, 
		    grid_line * line, 
		    int & flood_areas_cnt,
		    const bitvec * mask_undefined);

//! calculates cells inside \ref d_curv
SURFIT_EXPORT
bitvec * nodes_in_curv_mask(grid_line * line, const d_grid * grd, const bitvec * mask_undefined = NULL);

//! calculates cells inside \ref d_curv
SURFIT_EXPORT
bitvec * nodes_in_curv_mask(const d_curv * crv, d_grid * grd, const bitvec * mask_undefined = NULL);

//! calculates cells inside \ref d_area
SURFIT_EXPORT
bitvec * nodes_in_area_mask(const d_area * area, d_grid * grd, const bitvec * mask_undefined = NULL);

//! traces \ref grid_line that lies between cells with normal and undefined values
SURFIT_EXPORT
grid_line * trace_undef_grd_line(const bitvec * mask_undefined, size_t NN);

}; // namespace surfit;

#endif


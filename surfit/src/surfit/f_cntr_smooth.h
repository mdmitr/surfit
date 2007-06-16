
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

#ifndef __surfit_f_cntr_smooth_included__
#define __surfit_f_cntr_smooth_included__

#include "functional.h"

namespace surfit {

class d_points;
class f_points;
class d_cntr;
class bitvec;
class vec;
class sizetvec;

struct sect
{
	//! distance to neighbour cell
	REAL d; 
	
	//! desired value
	REAL z; 
	
	//! lower cell number
	size_t pos1;

	//! higher cell number
	size_t pos2;

};

class SURFIT_EXPORT f_cntr_smooth : public functional {
public:
	//! constructor
	f_cntr_smooth(REAL imult = 1);
	//! destructor
	~f_cntr_smooth();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();
	bool make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined);
	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);
	
	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);

	virtual void cleanup();

	void add_contour(const d_cntr * cntr);
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! contour for approximation
	std::vector<const d_cntr *> * contours;

private:
	d_grid * sects_grid;
	std::vector<sect> * sects;
	REAL mult;

};

bool calc_sects(d_grid *& sects_grid, 
		std::vector<sect> *& sects,
		std::vector<const d_cntr *> * contours,
		bitvec * mask_solved, 
		bitvec * mask_undefined);

}; // namespace surfit


#endif
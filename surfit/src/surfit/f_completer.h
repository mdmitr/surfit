
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

#ifndef __surfit_f_completer_included__
#define __surfit_f_completer_included__

#include "functional.h"
#include "vec.h"

namespace surfit {

class d_area;
class d_mask;
class grid_line;
class d_surf;
class bitvec;
class matr;

/*! \class f_completer
    \brief Functional that tells how resulting surface should be in areas 
    of low information density.
*/
class f_completer : public faultable {
public:

	//! constructor
	f_completer(REAL iD1 = 1, REAL iD2 = 0, REAL ialpha = 0, REAL iw = 1);
	//! destructor
	~f_completer();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, extvec *& v);
	
	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);
	
	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	void set_area(const d_area * iarea, bool iinside);
	void set_mask(const d_mask * imask);

protected:
	
	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

private:

	bool minimize_step();
	//! informational weight 
	REAL D1;
	//! informational weight 
	REAL D2;
	
	//! anisothropy angle
	REAL angle;
	//! anisothropy factor
	REAL w;

	// for area_completer
	const d_area * area;
	bool area_inside;

	// for mask_completer
	const d_mask * mask;

	bitvec * saved_mask_solved;
	bitvec * saved_mask_undefined;

};

SURFIT_EXPORT
size_t calcVecV(size_t size, 
	        const extvec * X,
	        matr * T, 
	        extvec *& res,
	        size_t NN, size_t MM,
	        const bitvec * mask_solved,
	        const bitvec * mask_undefined,
	        size_t use_x_from = UINT_MAX, size_t use_x_to = UINT_MAX,
	        size_t use_y_from = UINT_MAX, size_t use_y_to = UINT_MAX,
	        const d_surf * trend = NULL);

SURFIT_EXPORT
bool completer_solvable(int points, REAL D1, REAL D2);

SURFIT_EXPORT
void set_solved(bitvec * mask_solved, bitvec * mask_undefined);

}; // namespace surfit;

#endif


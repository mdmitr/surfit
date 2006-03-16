
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

namespace surfit {

class d_curv;
class grid_line;
class d_func;
class bitvec;
class matr;
class vec;

class f_completer : public functional, public faultable {
public:

	//! constructor
	f_completer(REAL iD1 = 1, REAL iD2 = 0);
	//! destructor
	~f_completer();

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, vec *& v);
	
	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const vec * X);
	
	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);
	
protected:
	
	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

private:

	bool minimize_step();
	//! informational weight 
	REAL D1;
	//! informational weight 
	REAL D2;

};

SURFIT_EXPORT
int calcVecV(int size, 
	     vec * X,
	     matr * T, 
	     vec *& res,
	     int NN, int MM,
	     const bitvec * mask_solved,
	     const bitvec * mask_undefined,
	     int use_x_from = -1, int use_x_to = -1,
	     int use_y_from = -1, int use_y_to = -1,
	     d_func * trend = NULL);

SURFIT_EXPORT
bool completer_solvable(int points, REAL D1, REAL D2);

SURFIT_EXPORT
void set_solved(bitvec * mask_solved, bitvec * mask_undefined);

}; // namespace surfit;

#endif


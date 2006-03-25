
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

#ifndef __surfit_approx_trend_included__
#define __surfit_approx_trend_included__

#include "functional.h"

namespace surfit {

class d_surf;
class matr;
class vec;
class bitvec;
class d_grid;

class SURFIT_EXPORT f_trend : public functional, public faultable {
public:
	f_trend(REAL iD1, REAL iD2, const d_surf * isrf);
	~f_trend();

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, vec *& v);

	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const vec * X);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	void drop_private_data();
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;
	
	bool minimize_step();
	const d_surf * srf;
	REAL D1;
	REAL D2;

	d_surf * tr_srf;
	void get_tr_srf(int & i_from, int & i_to, int & j_from, int & j_to);

};

SURFIT_EXPORT
d_grid * adopt_surf_grid(const d_surf * srf, d_grid * grd,
			 int & from_x, int & to_x,
			 int & from_y, int & to_y);

}; // namespace surfit;

#endif


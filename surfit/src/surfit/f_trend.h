
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
class bitvec;
class d_grid;

/*! \class f_trend
    \brief Functional that looks like \ref f_completer, but uses surface 
    to calculate differences between cells values.
*/
class SURFIT_EXPORT f_trend : public functional {
public:
	//! constructor
	f_trend(REAL iD1, REAL iD2, const d_surf * isrf);
	//! desctructor
	~f_trend();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, extvec *& v);

	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	void drop_private_data();
	void cleanup();
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;
	
	//! minimization procedure
	bool minimize_step();

	//! surface that will be used as trend
	const d_surf * srf;

	//! multiplier for matrD1
	REAL D1;

	//! multiplier for matrD2
	REAL D2;

	//! reprojected surface (trend)
	d_surf * tr_srf;

	bitvec * trend_mask_solved;
	bitvec * trend_mask_undefined;

	//! calculates surface for limits
	void get_tr_srf(size_t & i_from, size_t & i_to, size_t & j_from, size_t & j_to);

	//! fault lines projected on \ref d_grid
	grid_line * gfaults;

};

}; // namespace surfit;

#endif


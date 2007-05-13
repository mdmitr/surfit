
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

#ifndef __surfit_f_curv_included__
#define __surfit_f_curv_included__

#include "functional.h"

namespace surfit {

class d_points;
class f_points;
class bitvec;

/*! \class f_curv
    \brief functional for approximating curve with constant value
*/
class SURFIT_EXPORT f_curv : public functional {
public:
	//! constructor
	f_curv(REAL ivalue, const d_curv * icrv);
	//! destructor
	~f_curv();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined);

	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	void cleanup();
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! function for converting curve to points (with constant value) and creating \ref f_points functional
	void create_f_approx_points();

	//! curve for approximation
	const d_curv * crv;
	//! real number for curve approximation
	REAL value;

	//! functional for points approximation
	f_points * f_pnts;
	//! points, received from curve and "value"
	d_points * pnts;
};

}; // namespace surfit

#endif


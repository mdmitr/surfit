
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

#ifndef __surfit_f_curv_ineq_included__
#define __surfit_f_curv_ineq_included__

#include "functional.h"

namespace surfit {

class d_curv;
class d_points;
class f_points_ineq;

/*! \class f_curv_ineq
    \brief functional that sets inequality condition for curv
*/
class SURFIT_EXPORT f_curv_ineq : public functional {
public:
	//! constructor
	f_curv_ineq(REAL ivalue, const d_curv * icurv, bool ileq, REAL imult);
	//! destructor
	~f_curv_ineq();

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

private:

	void create_f_points_ineq();

	//! curv, that defines region
	const d_curv * crv;

	//! equation flag
	bool leq;

	//! value
	REAL value;

	//! parameter for penalty algorithm
	REAL mult;

	f_points_ineq * f_pnts_ineq;
	d_points * pnts;

};

}; // namespace surfit

#endif


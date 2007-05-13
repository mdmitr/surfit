
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

#ifndef __surfit_f_cntr_ineq_included__
#define __surfit_f_cntr_ineq_included__

#include "functional.h"

namespace surfit {

class d_cntr;
class d_points;
class f_points_ineq;

/*! \class f_cntr_ineq
    \brief functional that sets inequality condition for cntr
*/
class SURFIT_EXPORT f_cntr_ineq : public functional {
public:
	//! constructor
	f_cntr_ineq(const d_cntr * icntr, bool ileq, REAL imult);
	//! destructor
	~f_cntr_ineq();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined);

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

	//! cntr, that defines region
	const d_cntr * cntr;

	//! equation flag
	bool leq;

	//! parameter for penalty algorithm
	REAL mult;

	f_points_ineq * f_pnts_ineq;
	d_points * pnts;

};

}; // namespace surfit

#endif


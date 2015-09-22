
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

#ifndef __surfit_f_ineq_included__
#define __surfit_f_ineq_included__

#include "functional.h"

namespace surfit {

class bitvec;

//! functional of "conditional" type. Sets inequality for resulting surface
class f_ineq : public functional {
public:
	//! constructor
	f_ineq(REAL value, bool ileq, REAL imult);

	//! destructor
	~f_ineq();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);
	
	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);

protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

protected:
	
	//! value for inequality
	REAL value;

	//! if true, then inequality is leq, else - geq
	bool leq;

	//! multiplier coefficient
	REAL mult;

	//! mask where should apply inequality condition
	bitvec * mask;
};

}; // namespace surfit;


#endif


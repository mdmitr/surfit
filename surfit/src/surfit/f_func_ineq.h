
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

#ifndef __surfit_func_ineq_defined__
#define __surfit_func_ineq_defined__

#include "functional.h"

namespace surfit {

class func;
class bitvec;
class d_func;

class f_func_ineq : public functional {
public:
	f_func_ineq(const d_func * ifnc, bool ileq, REAL imult);
	~f_func_ineq();

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, vec *& v);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const vec * X);
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;
	
	const d_func * fnc;
	bool leq;
	REAL mult;
};

}; // namespace surfit;

#endif 


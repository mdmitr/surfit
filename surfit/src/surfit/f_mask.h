
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

#ifndef __surfit_approx_mask_included__
#define __surfit_approx_mask_included__

#include "functional.h"

namespace surfit {

class d_mask;
class matr;
class vec;
class bitvec;

/*! \class f_mask
    \brief functional that approximates constant real number in some area, defined by \ref d_mask
*/
class SURFIT_EXPORT f_mask : public functional {
public:
	//! constructor
	f_mask(const d_mask * idef, REAL ivalue);
	//! desctructor
	~f_mask();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, vec *& v);

	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const vec * X);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	void cleanup();
	
	
protected:
	
	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! fast minimization procedure
	bool minimize_only_mask();

	//! mask for applying functional
	const d_mask * msk;

	//! mask
	bitvec * mask;

	//! value to approximate with
	REAL value;
	
};

}; // namespace surfit;

#endif


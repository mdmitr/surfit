
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

#ifndef __surfit_f_hist_included__
#define __surfit_f_hist_included__

#include "functional.h"

namespace surfit {

class d_hist;
class bitvec;

//! functional of "condition" type. Sets the following condition: histogram of the resulting surface should be as equal as possible to the given histogram
class f_hist : public functional {
public:

	//! constructor
	f_hist(const d_hist * ihst, REAL imult, size_t itrshold );
	//! destructor
	~f_hist();

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

	void drop_private_data();
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

private:

	const d_hist * hist;
	REAL mult;
	bitvec * mask;
	size_t trshold;
};

}; // namespace surfit;

#endif


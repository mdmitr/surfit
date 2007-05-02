
/*------------------------------------------------------------------------------
 *	$Id: f_curv.h 940 2007-01-31 12:56:27Z mishadm $
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

#ifndef __surfit_f_fault_included__
#define __surfit_f_fault_included__

#include "functional.h"

namespace surfit {

/*! \class f_fault
    \brief functional modifier (fault line)
*/
class SURFIT_EXPORT f_fault : public functional {
public:
	//! constructor
	f_fault(const d_curv * icrv);
	//! destructor
	~f_fault();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, extvec *& v);

	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	void cleanup();

	const d_curv * get_fault() const;
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! fault curve
	const d_curv * crv;
};

}; // namespace surfit;

#endif


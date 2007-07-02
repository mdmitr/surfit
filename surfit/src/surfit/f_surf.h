
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

#ifndef __surfit_approx_surf_included__
#define __surfit_approx_surf_included__

#include "functional.h"
#include "vec.h"

namespace surfit {

class d_surf;
class matr;
class bitvec;

/*! \class f_surf
    \brief Functional for approximation surface with other surface values
*/
class SURFIT_EXPORT f_surf : public functional {
public:
	//! constructor
	f_surf(const d_surf * isrf, REAL imult = 1, const char * iname = NULL);

	//! destructor
	~f_surf();

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

	const d_surf * get_surf() const;
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! fast minimization procedure
	bool minimize_only_surf();

	//! data for functional
	const d_surf * srf;

	//! mask for functional
	bitvec * mask;

private:

	//! name for printing
	char * name;

	//! flag to complete solution - mark all unsolved cells as undefined
	bool need_complete;

	REAL mult;

};

}; // namespace surfit;

#endif


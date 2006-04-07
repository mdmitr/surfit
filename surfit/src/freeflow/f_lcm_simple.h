
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

#ifndef __surfit_f_lcm_simple_included__
#define __surfit_f_lcm_simple_included__

#include "functional.h"

namespace surfit {

class curv;
class grid_line;
class bitvec;

class f_lcm_simple : public faultable {
public:

	//! constructor
	f_lcm_simple(REAL ipermeability, REAL iviscosity, REAL imultiplier);
	//! destructor
	~f_lcm_simple();

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, vec *& v);

	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const vec * X);

	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);
	
	void add_flow(functional * fnc);

protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	std::vector<functional *> * flows;

private:

	bool minimize_step();
	
	//! formation permeability (constant for all area)
	REAL permeability; 

	//! fluid viscosity (constant for all area)
	REAL viscosity;    

	//! multiplier coefficient for Darcy law: speed = - permeability/viscosity*multiplier * grad(pressure)
	REAL multiplier;   

};

}; // namespace surfit;

#endif


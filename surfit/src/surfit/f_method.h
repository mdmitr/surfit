
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

#ifndef __surfit_f_method_included__
#define __surfit_f_method_included__

#include "functional.h"
#include "vec.h"

namespace surfit {

class d_surf;
class f_surf;

class f_method : public functional
{
public:
	//! constructor
	f_method(const char * method_name, REAL imult = 1);
	//! destructor
	~f_method();

	virtual const char * getManagerName() const { return "surfit"; };

	virtual bool minimize();
	virtual bool make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined);

	virtual bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);

	virtual void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);

	virtual void cleanup();

	virtual d_surf * get_method_surf() = 0;
	virtual const char * get_method_name() = 0;
	
protected:

	virtual int this_get_data_count() const;
	virtual const data * this_get_data(int pos) const;
	
private:
	f_surf * f_srf;
	void create_f_surf();
	d_surf * method_surf;
	REAL mult;

};

}; // namespace surfit

#endif


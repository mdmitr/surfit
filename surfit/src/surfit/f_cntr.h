
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

#ifndef __surfit_f_cntr_included__
#define __surfit_f_cntr_included__

#include "functional.h"

namespace surfit {

class d_points;
class f_points;
class d_cntr;
class bitvec;

/*! \class f_cntr
    \brief functional for approximating contour
*/
class SURFIT_EXPORT f_cntr : public functional {
public:
	//! constructor
	f_cntr(const d_cntr * icontour);
	//! destructor
	~f_cntr();

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
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! function for converting contour to points and making \ref f_points functional
	void create_f_approx_points();

	//! contour for approximation
	const d_cntr * contour;

	//! functional for approximation of points (received from contour)
	f_points * f_pnts;
	//! contour for apprixmation converted to points
	d_points * pnts;
};

}; // namespace surfit

#endif



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

#ifndef __surfit_approx_points_included__
#define __surfit_approx_points_included__

#include "functional.h"

namespace surfit {

class d_points;
class sub_points;

//! vector of \ref sub_points
typedef std::vector<sub_points *> sub_pnts;

class bitvec;
class d_grid;

/*! \class f_points
    \brief points approximation functional
*/
class SURFIT_EXPORT f_points : public functional {
public:
	//! constructor
	f_points(const d_points * ipnts, const char * iprint_name = NULL);
	//! destructor
	~f_points();

	const char * getManagerName() const { return "surfit"; };

	bool minimize();
	bool make_matrix_and_vector(matr *& matrix, extvec *& v, bitvec * mask_solved, bitvec * mask_undefined);
	void mark_solved_and_undefined(bitvec * mask_solved, 
				       bitvec * mask_undefined,
				       bool i_am_cond);
	
	bool solvable_without_cond(const bitvec * mask_solved, 
				   const bitvec * mask_undefined,
				   const extvec * X);

	virtual void cleanup();

protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! very fast minimization
	bool minimize_only_points();

	//! scattered data points for approximation
	const d_points * pnts;

	//! subset of points for cells
	sub_pnts * f_sub_pnts;
	
	//! mask for matrix
	bitvec * mask;
	
	//! \ref d_grid for binding points 
	d_grid * binded_grid;

private:

	char * print_name;

};

/*! \class f_points_user
    \brief parent functional for all other functionals, who use f_points functional
*/
class SURFIT_EXPORT f_points_user : public functional
{
	public:
	//! constructor
	f_points_user(const char * ifunctional_name);
	//! destructor
	~f_points_user();

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

	//! returns points to approximate/interpolate
	virtual d_points * get_points() = 0;
	
protected:

	int this_get_data_count() const = 0;
	const data * this_get_data(int pos) const = 0;

	//! function for creating f_points functional
	void create_f_points();

	//! functional for approximation of points (received from contour)
	f_points * f_pnts;

	//! points for f_points functional
	d_points * pnts;

	//! name of functional for printing into log file
	const char * functional_name;

};

}; // namespace surfit

#endif


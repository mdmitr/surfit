
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

#ifndef __freeflow_approx_pcntr_included__
#define __freeflow_approx_pcntr_included__

#include "functional.h"

namespace surfit {

class d_points;
class f_flow_points;
class d_cntr;
class d_grid;

class FLOW_EXPORT f_flow_cntr : public functional {
public:
	f_flow_cntr(d_cntr * icontour);
	~f_flow_cntr();

	const char * getManagerName() const { return "freeflow"; };

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

	void create_f_flow_points();

	const d_cntr * contour;
	f_flow_points * f_points;
	d_points * d_pnts;
};

FLOW_EXPORT
d_points * discretize_pcntr(const d_cntr * pcrv, d_grid * grd, const char * task_name);


}; // namespace surfit;

#endif


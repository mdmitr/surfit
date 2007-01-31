
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

#ifndef __freeflow_flow_curv_included__
#define __freeflow_flow_curv_included__

#include "functional.h"

namespace surfit {

class d_points;
class f_flow_points;
class d_curv;
class d_grid;

class FLOW_EXPORT f_flow_curv : public functional {
public:
	f_flow_curv(REAL ivalue, d_curv * icrv);
	~f_flow_curv();

	const char * getManagerName() const { return "freeflow"; };

	bool minimize();

	bool make_matrix_and_vector(matr *& matrix, extvec *& v);

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

	void create_f_flow_points();

	const d_curv * crv;
	REAL value;

	f_flow_points * f_points;
	d_points * d_pnts;
};

FLOW_EXPORT
d_points * discretize_pcurv(const d_curv * crv, d_grid * grd, REAL value, const char * task_name);

}; // namespace surfit;

#endif


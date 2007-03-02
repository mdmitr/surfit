
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

#include "flow_ie.h"

#include "fileio.h"

#include "flow_points.h"
#include "points.h"
#include "bitvec.h"
#include "vec.h"
#include "matr.h"
#include "solvers.h"
#include "variables_tcl.h"
#include "free_elements.h"
#include "pnts_internal.h"
#include "grid.h"

#include "grid_user.h"

namespace surfit {

f_flow_points::f_flow_points(const d_points * itsk) :
functional("f_flow_points", F_USUAL) 
{
	f_task = itsk;
	if (f_task->getName()) {
		setNameF("f_flow_points %s", f_task->getName());
	}
	f_sub_tasks = NULL;
	binded_grid = NULL;
}

f_flow_points::~f_flow_points() {
	cleanup();	
};

void f_flow_points::cleanup() {
	if (f_sub_tasks)
		free_scattered_points( f_sub_tasks );
	f_sub_tasks = NULL;
	if (binded_grid)
		binded_grid->release();
	binded_grid = NULL;
};

int f_flow_points::this_get_data_count() const {
	return 1;
};

const data * f_flow_points::this_get_data(int pos) const {
	if (pos == 0)
		return f_task;
	return NULL;
};

bool f_flow_points::minimize() {
	return false;
};

bool f_flow_points::make_matrix_and_vector(matr *& matrix, extvec *& v) {

	if (f_sub_tasks == NULL) {
		prepare_scattered_points(f_task, f_sub_tasks);
	}
	
	size_t i;
	
	size_t matrix_size = method_basis_cntX*method_basis_cntY;
	v = create_extvec(matrix_size);

	size_t task_size = f_task->size();
		
	writelog(LOG_MESSAGE,"flow points : (%s), %d points", f_task->getName(), f_task->size());
	
	// avoiding two-times bind_points_to_grid calling for the same grid
	if (binded_grid) {
		if (binded_grid->operator ==(method_grid) == false) {
			bind_points_to_grid(method_sub_grid, f_task, f_sub_tasks, method_grid);
			if (binded_grid)
				binded_grid->release();
			binded_grid = create_grid(method_grid);
		}
	} else {
		bind_points_to_grid(method_sub_grid, f_task, f_sub_tasks, method_grid);
		if (binded_grid)
			binded_grid->release();
		binded_grid = create_grid(method_grid);
	}
	
	size_t points = 0;

	for (i = 0; i < f_sub_tasks->size(); i++) {
		
		sub_points * sub_pnts = (*f_sub_tasks)[i];
		
		if ( (!method_mask_solved->get(sub_pnts->cell_number)) && 
		     (!method_mask_undefined->get(sub_pnts->cell_number)) ) 
		{
			REAL value = sub_pnts->sum_value(f_task);
			(*v)(sub_pnts->cell_number) = value;
			points++;
		}
	}

	matrix = NULL;

	bool solvable = (points > 0);

	solvable = wrap_sums(matrix, v) || solvable;
	
	return solvable;
};

void f_flow_points::mark_solved_and_undefined(bitvec * mask_solved, bitvec * mask_undefined, bool i_am_cond) {
	if ((functionals_add->size() == 0) && ( !cond() ) && (i_am_cond == false) )
		return;	

	mark_sums(mask_solved, mask_undefined);
};

bool f_flow_points::solvable_without_cond(const bitvec * mask_solved,
					  const bitvec * mask_undefined,
					  const extvec * X)
{

	size_t i;
	for (i = 0; i < mask_solved->size(); i++) {
		if (mask_solved->get(i))
			goto sss;
	}

	return false;

sss:
	
	return true;

};

}; // namespace surfit;



/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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
#include "vec.h"
#include "intvec.h"
#include "fileio.h"
#include "grid_line.h"
#include "wtask.h"
#include "operD1.h"
#include "oper_points.h"
#include "variables_tcl.h"
#include "bitvec.h"
#include "solvers.h"
#include "grid.h"
#include "lcm_simple.h"
#include "flow_variables.h"
#include "lcm_simple_tcl.h"

#include "grid_user.h"
#include "lcm_simple_user.h"
#include "wtask_user.h"
#include "wfunc_user.h"
#include "warea_user.h"
#include "area_user.h"
#include "completer_user.h"
#include "flt_user.h"
#include "ptask_user.h"

#include <algorithm>

namespace surfit {

/////////////////////////////////////////////////////////////////////
//
//  L C M _ S I M P L E _ U S E R  V A R I A B L E S
//
/////////////////////////////////////////////////////////////////////
lcm_simple *  flow_lcm_simple = NULL;
vec * lcm_simple_weights = NULL;
intvec * lcm_simple_weights_cnt = NULL;

/////////////////////////////////////////////////////////////////////
//
//  L C M _ S I M P L E _ U S E R  USEFUL  FUNCTIONS
//
/////////////////////////////////////////////////////////////////////

bool lcm_simple_solvable(int points) {
	return points > 0;
};

void use_lcm_simple( REAL stepX, REAL stepY,
                     vec *& X, 
                     bitvec * mask_solved,
                     bitvec * mask_undefined,
                     grid_line * fault_grid_line,
                     int NN, int MM,
                     int cnt,
                     wtask * wtsk,
		     std::vector<sub_points *> * sub_wtsks,
		     modifier1 * usr
                  ) 
{
	int matrix_size = NN*MM;
	
	operD1 * oD1 = new operD1(matrix_size, NN, 
				  stepX, stepY,
				  mask_solved, mask_undefined, 
				  fault_grid_line);
	
	vec * V = NULL;
	
	V = new vec(matrix_size);

	int cnt_points = 0;
	cnt_points += calcVecV(matrix_size, X, oD1, V, NN, MM, mask_solved, mask_undefined);
	
	cnt_points += calcVecV_points(usr, V, wtsk, sub_wtsks, mask_solved, mask_undefined);
	cnt_points += calcVecV_wfuncs(usr, V, mask_solved, mask_undefined);
	cnt_points += calcVecV_wareas(usr, V, mask_solved, mask_undefined);
	
	oper_points * op_pnts = NULL;

	if (lcm_simple_weights != NULL) {
		op_pnts = new oper_points(lcm_simple_weights, 
			lcm_simple_weights_cnt, 
			mask_solved,
			mask_undefined,
			NN);
	}

	oper * T = new oper_complex(1, oD1, 1, op_pnts);

	cnt_points += calcVecV_ptask(flow_lcm_simple, V, mask_solved, mask_undefined);
		
	if (write_mat) {
		
		char mname[10];
		sprintf(&mname[0],"T%d",cnt);
		char vname[10];
		sprintf(&vname[0],"V%d",cnt);
		
		T->writeMAT(SURFIT_MAT,mname);
		matlabWriteVector(V->begin(), V->end(), SURFIT_MAT, vname);
		
		
		char delname[10];
		sprintf(&delname[0],"D%d",cnt);
		vec del;
		del.reserve(matrix_size);  /// !!!
		int i;
		for (i = 0; i < mask_solved->size(); i++) {
			if (mask_solved->get(i))
				del.push_back(i);
		}
		for (i = 0; i < mask_undefined->size(); i++) {
			if (mask_undefined->get(i))
				del.push_back(i);
		}
		std::sort(del.begin(), del.end());
		matlabWriteVector(del.begin(), del.end(), SURFIT_MAT, delname);
		
		char xname[10];
		sprintf(&xname[0],"X%d",cnt);
		matlabWriteVector(X->begin(), X->end(), SURFIT_MAT, xname);
		
	}
	

	if ( lcm_simple_solvable(cnt_points) )
		solve(T, V, solver_code, X);
	else {
		// fill undef
		int i;
		for (i = 0; i < mask_solved->size(); i++) {
			if (!mask_solved->get(i))
				mask_undefined->set_true(i);
		}
	}

	usr->remove_weights();
	usr->remove_weights_cnt();

	if (write_mat) {
		char xname[10];
		sprintf(&xname[0],"x%d",cnt);
		matlabWriteVector(X->begin(), X->end(), SURFIT_MAT, xname);
	}
	
	delete T;
	delete V;

	set_solved(mask_solved, mask_undefined);
	
};

void lcm_simple_with_faults(modifier1 * usr) {

	if (!fault_grd_line)
		return;
		
	writelog(SURFIT_MESSAGE,"reprojecting solution with faults...");
	
	int NN = method_prev_grid->getCountX();
	int MM = method_prev_grid->getCountY();

	int newNN = NN;
	int newMM = MM;

	if (doubleX)
		newNN *= 2;
	if (doubleY)
		newMM *= 2;

	int matrix_size = NN*MM;

	bitvec * local_mask_solved = new bitvec(method_mask_solved->size());
	
	int size = method_mask_solved->size();
	int i;
	for (i = 0; i < size; i++) {
		if (!check_for_node(fault_grd_line, i)) 
			local_mask_solved->set_true(i);
	};
	
	use_lcm_simple(method_stepX, method_stepY,
		       method_X, 
		       local_mask_solved,
		       method_mask_undefined,
		       fault_grd_line,
		       method_grid->getCountX(),
		       method_grid->getCountY(),
		       method_phase_counter,
		       wtsk, sub_wtsks, usr);

	delete local_mask_solved;
	
};

void lcm_simple_with_undef_areas(modifier1 * usr) {

	if (!area_grd_line)
		return;
		
	writelog(SURFIT_MESSAGE,"reprojecting solution with undef-valued areas...");
	
	int NN = method_prev_grid->getCountX();
	int MM = method_prev_grid->getCountY();

	int newNN = NN;
	int newMM = MM;

	if (doubleX)
		newNN *= 2;
	if (doubleY)
		newMM *= 2;

	int matrix_size = NN*MM;

	bitvec * local_mask_solved = new bitvec(method_mask_solved->size());

	int size = method_mask_solved->size();
	int i;

	
	for (i = 0; i < size; i++) {
		if (!check_for_node(area_grd_line, i)) 
			local_mask_solved->set_true(i);
	};

	use_lcm_simple(method_stepX, method_stepY,
		       method_X, 
		       local_mask_solved,
		       method_mask_undefined,
		       area_grd_line,
		       method_grid->getCountX(),
		       method_grid->getCountY(),
		       method_phase_counter,
		       wtsk, sub_wtsks, usr);

	delete local_mask_solved;
};

/////////////////////////////////////////////////////////////////////
//
//  L C M _ S I M P L E _ U S E R 
//
/////////////////////////////////////////////////////////////////////

lcm_simple_user::lcm_simple_user() : user("lcm_simple") {};

lcm_simple_user::~lcm_simple_user() {};
	
int lcm_simple_user::max_priority() {
	return lcm_simple_info();
};

void lcm_simple_user::init() {
	if (!flow_lcm_simple) 
		return;
	lcm_simple_weights = NULL;
	lcm_simple_weights_cnt = NULL;

};

void lcm_simple_user::prepare() {};
void lcm_simple_user::begin() {};
void lcm_simple_user::stage1(int priority) {};
void lcm_simple_user::stage2(int priority) {};
void lcm_simple_user::stage3(int priority) {};
void lcm_simple_user::stage4(int priority) {};
void lcm_simple_user::stage5(int priority) {};

void lcm_simple_user::finish() {
	
	if (!flow_lcm_simple)
		return;

	writelog(SURFIT_MESSAGE,"lcm_simple : processing...");

	int matrix_size = method_basis_cntX*method_basis_cntY;

	if ( method_mask_solved->true_size() + method_mask_undefined->true_size() == matrix_size ) {
		writelog(SURFIT_MESSAGE,"lcm_simple : nothing to do");
		return;
	}

	int NN = method_basis_cntX;
	int MM = method_basis_cntY;

	std::vector<short int> * flood_areas = new std::vector<short int>(matrix_size);
	int flood_areas_cnt = 0;

	if (method_phase_counter > 1) {
		
		lcm_simple_with_faults(this);
		lcm_simple_with_undef_areas(this);
		//lcm_simple_with_defareas(this);
		
	}

	// floodfill stage
	fill_all_areas(flood_areas, method_grid, fault_grd_line, flood_areas_cnt, method_mask_undefined);
	
	use_flood_areas(1, 0,
		flood_areas, flood_areas_cnt,
		method_grid,
		this);

	delete flood_areas;

	use_lcm_simple( method_stepX, method_stepY,
			method_X,
			method_mask_solved, method_mask_undefined,
			fault_grd_line,
			method_basis_cntX, method_basis_cntY,
			method_phase_counter,
			wtsk, sub_wtsks, this );
	
};

void lcm_simple_user::release() {

	if (!flow_lcm_simple)
		return;

	if (lcm_simple_weights) 
		writelog(SURFIT_DEBUG,"lcm_simple_weights was not removed!");
	delete lcm_simple_weights;
	lcm_simple_weights = NULL;
	if (lcm_simple_weights) 
		writelog(SURFIT_DEBUG,"lcm_simple_weights_cnt was not removed!");
	delete lcm_simple_weights_cnt;
	lcm_simple_weights_cnt = NULL;
};

vec * lcm_simple_user::get_weights() const {

	if (!flow_lcm_simple)
		return NULL;

	if (!lcm_simple_weights)
		lcm_simple_weights = new vec(method_basis_cntX*method_basis_cntY);
	return lcm_simple_weights;
};

intvec * lcm_simple_user::get_weights_cnt() const {

	if (!flow_lcm_simple)
		return NULL;

	if (!lcm_simple_weights_cnt)
		lcm_simple_weights_cnt = new intvec(method_basis_cntX*method_basis_cntY);
	return lcm_simple_weights_cnt;
};

void lcm_simple_user::remove_weights() {

	if (!flow_lcm_simple)
		return;

	delete lcm_simple_weights;
	lcm_simple_weights = NULL;
};

void lcm_simple_user::remove_weights_cnt() {

	if (!flow_lcm_simple)
		return;

	delete lcm_simple_weights_cnt;
	lcm_simple_weights_cnt = NULL;	
};

}; // namespace surfit;




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

#include "ie.h"
#include "real.h"

#include "completer.h"
#include "completer_tcl.h"
#include "fileio.h"
#include "grid_line.h"
#include "flt_user.h"
#include "operD1.h"
#include "operD2.h"
#include "oper_points.h"
#include "grid.h"
#include "vec.h"
#include "intvec.h"
#include "bitvec.h"
#include "solvers.h"
#include "func.h"
#include "variables_tcl.h"

#include "completer_user.h"
#include "grid_user.h"
#include "wtask_user.h"
#include "wfunc_user.h"
#include "flt_user.h"
#include "area_user.h"
#include "warea_user.h"
#include "defarea_user.h"

#include "wtask.h"
#include "points.h"

#include <algorithm>

namespace surfit {

///////////////////////////////////////////////////////////
//
//  C O M P L E T E R   V A R I A B L E S
//
///////////////////////////////////////////////////////////

completer    *  surfit_completer    = NULL;

vec * completer_weights = NULL;
intvec * completer_weights_cnt = NULL;

/*! \struct completer_garbage
    \brief struct for deletion of \ref completer pointers
*/
struct completer_garbage : public binman {
	//! inits \ref surfit_completer
	completer_garbage() {
		surfit_completer = new completer(1,2);
	};
	//! removes \ref surfit_completer
	~completer_garbage() {
		delete surfit_completer;
	};

};

completer_garbage completer_garb;

///////////////////////////////////////////////////////////
//
//  C O M P L E T E R   U S E F U L   F U N C T I O N S
//
///////////////////////////////////////////////////////////

bool completer_solvable(int points, REAL D1, REAL D2) {
	if (D1 != 0)
		return (points > 0);
	return (points > 2);
};

void set_solved(bitvec * mask_solved, bitvec * mask_undefined) {
	int N = mask_solved->size();
	int i;
	for (i = 0; i < N; i++) {
		if (!mask_undefined->get(i))
			mask_solved->set_true(i);
	}
};

int calcVecV(int size, 
	     vec * X,
	     oper * T, 
	     vec *& res,
	     int NN, int MM,
	     bitvec * mask_solved,
	     bitvec * mask_undefined,
	     int x_from, int x_to,
	     int y_from, int y_to,
	     func * trend) 
{
	int points = 0;

	if (!res)
		res = new vec(size);

	int i,j;
	int pos, pos_x, pos_y;
	REAL val, mult;

	bool use_rect = ( (x_from != -1) && (x_to != -1) && (y_from != -1) && (y_to != -1) );
	int nn = NN;
	if (use_rect) {
		nn = x_to - x_from + 1;
	}

	pos_x = INT_MAX;
	pos_y = INT_MAX;

	for (pos = 0; pos < mask_solved->size(); pos++) {

		int local_pos = pos;

		if (use_rect) {

			pos_x = pos % NN;
			pos_y = (pos - pos_x)/NN;

			if  (!( (pos_x >= x_from) && (pos_x <= x_to) && (pos_y >= y_from) && (pos_y <= y_to) ))
				continue;
			local_pos = pos_x-x_from + (pos_y-y_from)*nn;

		}

		if (trend) {
			
			REAL trend_val = (*(trend->coeff))(local_pos);
			if (trend_val == undef_value)
				continue;
			for (j = 0; j < T->rows();) {
				int prev_j = j;
				mult = T->operator()(pos,j,&j);
				if (trend && (mult != 0)) {
					(*res)(prev_j) += mult*trend_val;
				}
			}

		}

		if (!mask_solved->get(pos))
			continue;

		val = (*X)(pos);

		for (j = 0; j < T->rows();) {
			int prev_j = j;
			mult = T->operator()(pos,j,&j);
			(*res)(prev_j) -= val*mult;
		}

		
	}
	
	for (i = 0; i < mask_solved->size(); i++) {
		if (mask_solved->get(i)) {
			(*res)(i) = 0;
			points++;
		}
	}

	if (use_rect) {
		int n,m;
		for (m = 0; m < MM; m++) {
			for (n = 0; n < NN; n++) {
				if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
					(*res)(n + m*NN) = 0;
			}
		}
	}

	return points;
};

void use_completer( REAL stepX, REAL stepY,
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
	
	operD2 * oD2 = new operD2(matrix_size, NN, 
		stepX, stepY,
		mask_solved, mask_undefined, 
		fault_grid_line);
	
	oper_complex *  T = new oper_complex(surfit_completer->D1, oD1, surfit_completer->D2, oD2);

	vec * V = NULL;
	
	V = new vec(matrix_size);

	int points = 0;
	points += calcVecV(matrix_size, X, T, V, NN, MM, mask_solved, mask_undefined);

	points += calcVecV_points(usr, V, wtsk, sub_wtsks, mask_solved, mask_undefined);
	points += calcVecV_wfuncs(usr, V, mask_solved, mask_undefined);
	points += calcVecV_wareas(usr, V, mask_solved, mask_undefined);

	if (completer_weights != NULL) {
		oper_points * op_pnts = new oper_points(completer_weights, 
			completer_weights_cnt, 
			mask_solved,
			mask_undefined,
			NN);
		T = new oper_complex(1, T, 1, op_pnts);
	}

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

	if ( completer_solvable(points, surfit_completer->D1, surfit_completer->D2) )
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
	
};

void completer_with_grid_line(modifier1 * usr, grid_line * line) {

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

		if (!check_for_node(line, i)) 
			local_mask_solved->set_true(i);

	};
	
	use_completer(method_stepX, method_stepY,
		      method_X, 
		      local_mask_solved,
		      method_mask_undefined,
		      line,
		      method_grid->getCountX(),
		      method_grid->getCountY(),
		      method_phase_counter,
		      wtsk, sub_wtsks, usr);

	delete local_mask_solved;
	
};

void completer_with_faults(modifier1 * usr) {

	if (!fault_grd_line)
		return;
		
	writelog(SURFIT_MESSAGE,"reprojecting solution with faults...");
	
	completer_with_grid_line(usr, fault_grd_line);
	
};

void completer_with_defareas(modifier1 * usr) {

	if ( (!surfit_defarea) && (surfit_defareas->size() == 0) )
		return;
	
	writelog(SURFIT_MESSAGE,"reprojecting solution with defareas...");

	bitvec * local_mask_solved = new bitvec(method_mask_solved->size());
	local_mask_solved->init_true();
	
	defarea_update_mask_solved(surfit_defarea, local_mask_solved);
	unsigned int i;
	for (i = 0; i < surfit_defareas->size(); i++) {
		defarea_update_mask_solved( (*surfit_defareas)[i], local_mask_solved );
	}
	int I;
	for (I = 0; I < method_mask_solved->size(); I++) {
		if (method_mask_solved->get(I))
			local_mask_solved->set_true(I);
	}

	use_completer(method_stepX, method_stepY,
		      method_X, 
		      local_mask_solved,
		      method_mask_undefined,
		      NULL,
		      method_grid->getCountX(),
		      method_grid->getCountY(),
		      method_phase_counter,
		      wtsk, sub_wtsks, usr);

	delete local_mask_solved;
	
};

void completer_with_undef_areas(modifier1 * usr) {

	if (!area_grd_line)
		return;
		
	writelog(SURFIT_MESSAGE,"reprojecting solution with undef-valued areas...");
	
	completer_with_grid_line(usr, area_grd_line);
	
};

void use_flood_areas(REAL D1, REAL D2,
		     std::vector<short int> * flood_areas,
		     int flood_areas_cnt,
		     grid * grd, 
		     modifier1 * usr)
{
	int color;
	int f_size = flood_areas->size();

	int NN = grd->getCountX();
	int MM = grd->getCountY();

	bool all_ok = false;
	int pos = 0;
	int exists = 0;
	
	if (flood_areas_cnt <= 1)
		return;

	writelog(SURFIT_MESSAGE,"flood_areas_cnt = %d", flood_areas_cnt);

	writelog(SURFIT_MESSAGE,"processing each isolated area (%d)...", flood_areas_cnt);
	bitvec * local_mask_undefined = new bitvec(method_mask_undefined->size());
	bitvec * local_mask_solved = new bitvec(method_mask_solved->size());

	bool undef, solved;
	
	for (color = 1; color <= flood_areas_cnt; color++) {
	
		local_mask_undefined->copy(method_mask_undefined);
		local_mask_solved->copy(method_mask_solved);
	
		for (pos = 0; pos < f_size; pos++) {
			if ( (*flood_areas)[pos] != color ) {
				local_mask_undefined->set_true(pos);
				local_mask_solved->set_false(pos);
			}
		}

		use_completer(method_stepX, method_stepY, 
			      method_X, 
			      local_mask_solved, 
			      local_mask_undefined, 
			      fault_grd_line,
			      method_basis_cntX, method_basis_cntY,
			      method_phase_counter,
			      wtsk, sub_wtsks, usr);
		
		for (pos = 0; pos < f_size; pos++) {
			if ( (*flood_areas)[pos] == color ) {
				
				undef = local_mask_undefined->get(pos);
				if (undef)
					method_mask_undefined->set_true(pos);
				else 
					method_mask_undefined->set_false(pos);

				solved = local_mask_solved->get(pos);	
				if (solved)
					method_mask_solved->set_true(pos);
				else
					method_mask_solved->set_false(pos);
				
			}
		}

	};

	delete local_mask_undefined;
	delete local_mask_solved;

};

///////////////////////////////////////
//
//  C O M P L E T E R _ U S E R 
//
///////////////////////////////////////

completer_user::completer_user() : user("completer") {};
completer_user::~completer_user() {};

int completer_user::max_priority() {
	return completer_info();
};

void completer_user::init() {
	if (!surfit_completer)
		return;
	completer_weights = NULL;
	completer_weights_cnt = NULL;
};

void completer_user::prepare() {};
void completer_user::begin() {};
void completer_user::stage1(int priority) {};
void completer_user::stage2(int priority) {};
void completer_user::stage3(int priority) {};
void completer_user::stage4(int priority) {};
void completer_user::stage5(int priority) {};

void completer_user::finish() 
{
	if (!surfit_completer)
		return;

	writelog(SURFIT_MESSAGE,"completer : processing...");

	int matrix_size = method_basis_cntX*method_basis_cntY;

	int solved_size = method_mask_solved->true_size();
	int undef_size = method_mask_undefined->true_size();

	if ( solved_size + undef_size >= matrix_size ) {
		writelog(SURFIT_MESSAGE,"completer : nothing to do");
		return;
	}

	int NN = method_basis_cntX;
	int MM = method_basis_cntY;

	std::vector<short int> * flood_areas = new std::vector<short int>(matrix_size);
	int flood_areas_cnt = 0;

	if (method_phase_counter > 1) {
		
		completer_with_faults(this);
		completer_with_undef_areas(this);
		completer_with_defareas(this);
		
	}

	// floodfill stage
	fill_all_areas(flood_areas, method_grid, fault_grd_line, flood_areas_cnt, method_mask_undefined);
	
	use_flood_areas(surfit_completer->D1,
		surfit_completer->D2,
		flood_areas, flood_areas_cnt,
		method_grid,
		this);

	delete flood_areas;

	use_completer( method_stepX, method_stepY,
		       method_X,
		       method_mask_solved, method_mask_undefined,
		       fault_grd_line,
		       method_basis_cntX, method_basis_cntY,
		       method_phase_counter,
		       wtsk, sub_wtsks, this );
	
};

void completer_user::release() 
{
	if (!surfit_completer)
		return;

	if (completer_weights) 
		writelog(SURFIT_DEBUG,"completer_weights was not removed!");
	delete completer_weights;
	completer_weights = NULL;
	if (completer_weights) 
		writelog(SURFIT_DEBUG,"completer_weights_cnt was not removed!");
	delete completer_weights_cnt;
	completer_weights_cnt = NULL;
};

vec * completer_user::get_weights() const {
	if (!surfit_completer)
		return NULL;

	if (!completer_weights)
		completer_weights = new vec(method_basis_cntX*method_basis_cntY);
	return completer_weights;
};

intvec * completer_user::get_weights_cnt() const {
	if (!surfit_completer)
		return NULL;

	if (!completer_weights_cnt)
		completer_weights_cnt = new intvec(method_basis_cntX*method_basis_cntY);
	return completer_weights_cnt;
};

void completer_user::remove_weights() {
	if (!surfit_completer)
		return;

	delete completer_weights;
	completer_weights = NULL;
};

void completer_user::remove_weights_cnt() {
	if (!surfit_completer)
		return;

	delete completer_weights_cnt;
	completer_weights_cnt = NULL;	
};

}; // namespace surfit;





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
#include "trend_user.h"
#include "trends.h"
#include "variables_tcl.h"
#include "trend.h"
#include "grid.h"
#include "fileio.h"
#include "func_internal.h"
#include "operD1.h"
#include "operD2.h"
#include "oper_points.h"
#include "vec.h"
#include "bitvec.h"
#include "intvec.h"
#include "free_elements.h"

// solvers
#include "solvers.h"

#include "grid_user.h"
#include "flt_user.h"
#include "wtask_user.h"
#include "wfunc_user.h"
#include "warea_user.h"
#include "completer_user.h"

#include <algorithm>

namespace surfit {

///////////////////////////////////////////////////////
//
//  A U X _ F U N C   G L O B A L   V A R I A B L E S
//
///////////////////////////////////////////////////////
vec * trend_weights = NULL;
intvec * trend_weights_cnt = NULL;

trend                * surfit_trend  = NULL;
std::vector<trend *> * surfit_trends = NULL;

/*! \struct trend_garbage
    \brief struct for deletion of \ref trend pointers
*/
struct trend_garbage : public binman {
	//! inits \ref surfit_trend and \ref surfit_trends
	trend_garbage() {
		surfit_trend = NULL;
		surfit_trends = new std::vector<trend *>;
	};
	//! removes \ref surfit_trend and \ref surfit_trends
	~trend_garbage() {
		delete surfit_trend;
		if (surfit_trends) {
			free_elements(surfit_trends->begin(), surfit_trends->end());
			delete surfit_trends;
		}
	};
};

trend_garbage trend_garb;


////////////////////////////////////////////////////////
//
//  A U X _ F U N C   U S E F U L   F U N C T I O N S 
//
////////////////////////////////////////////////////////

bool trend_solvable(int points, REAL D1, REAL D2) {
	if (D1 != 0)
		return (points > 0);
	return (points > 2);
};


grid * adopt_func_grid(func * fnc, grid * grd,
		       int & from_x, int & to_x,
		       int & from_y, int & to_y) {

	REAL g_x0, g_xn, g_y0, g_yn; // Начало и конец геометрии
	REAL f_x0, f_xn, f_y0, f_yn; // Начало и конец функции
	REAL x0, xn, y0, yn;     // Реальные начало и конец

	grd->getCoordNode(0,0, g_x0, g_y0);
	grd->getCoordNode(grd->getCountX()-1, grd->getCountY()-1, g_xn, g_yn);

	fnc->getCoordNode(0,0, f_x0, f_y0);
	fnc->getCoordNode(fnc->getCountX()-1,fnc->getCountY()-1, f_xn, f_yn);
	
	
	x0 = MAX(g_x0, f_x0);
	xn = MIN(g_xn, f_xn);
	y0 = MAX(g_y0, f_y0);
	yn = MIN(g_yn, f_yn);

	if (x0 >= xn)
		return NULL;
	
	if (y0 >= yn)
		return NULL;

	REAL grd_x, grd_y;
	
	int i0 = grd->get_i(x0);
	grd->getCoordNode(i0, 0, grd_x, grd_y);
	if (grd_x < x0)
		i0++;

	int in = grd->get_i(xn);
	grd->getCoordNode(in, 0, grd_x, grd_y);
	if (grd_x > xn)
		in--;

	int j0 = grd->get_j(y0);
	grd->getCoordNode(0, j0, grd_x, grd_y);
	if (grd_y < y0)
		j0++;

	int jn = grd->get_j(yn);
	grd->getCoordNode(0, jn, grd_x, grd_y);
	if (grd_y > yn)
		jn--;

	from_x = i0;
	to_x = in;
	from_y = j0;
	to_y = jn;

	grd->getCoordNode(i0,j0,x0,y0);
	grd->getCoordNode(in,jn,xn,yn);
	
	grid * new_geom = new grid(x0, xn, grd->stepX, y0, yn, grd->stepY);
	return new_geom;

};

void apply_trend(trend * aux_fnc,
		 vec *& X, 
		 bitvec * mask_solved,
		 bitvec * mask_undefined,
		 trend_user * usr)
{
	
	if (aux_fnc->getName())
		writelog(SURFIT_MESSAGE,"trend (%s) : processing...",aux_fnc->getName());
	else 
		writelog(SURFIT_MESSAGE,"trend : processing...");
	
	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();

	int matrix_size = NN*MM;
	int aux_X_from, aux_X_to;
	int aux_Y_from, aux_Y_to;
		
	if ((aux_fnc->D1 == 0) && (aux_fnc->D2 == 0)) {
		writelog(SURFIT_WARNING,"D1 = 0 and D2 = 0. Nothing to do");
		return;
	}
		
	grid * aux_grid = adopt_func_grid(aux_fnc, method_grid, 
		aux_X_from, aux_X_to,
		aux_Y_from, aux_Y_to);
	
	func * tr = _func_project(aux_fnc, aux_grid);
	delete aux_grid;

	operD1_rect * oD1 = new operD1_rect(matrix_size, NN, 
		method_stepX, method_stepY,
		aux_X_from, aux_X_to,
		aux_Y_from, aux_Y_to,
		mask_solved, mask_undefined, 
		fault_grd_line);
		
	operD2_rect * oD2 = new operD2_rect(matrix_size, NN, 
		method_stepX, method_stepY,
		aux_X_from, aux_X_to,
		aux_Y_from, aux_Y_to,
		mask_solved, mask_undefined, 
		fault_grd_line);

	oper_complex *  T = new oper_complex(aux_fnc->D1, oD1, aux_fnc->D2, oD2);

	vec * V = NULL;
	
	V = new vec(matrix_size);

	int points = 0;
	points += calcVecV(matrix_size, 
			   X, 
			   T, 
			   V, 
			   NN, 
			   MM, 
			   mask_solved, 
			   mask_undefined,
			   aux_X_from, aux_X_to,
			   aux_Y_from, aux_Y_to,
			   tr);

	points += calcVecV_points(usr, V, wtsk, sub_wtsks, mask_solved, mask_undefined);
	points += calcVecV_wfuncs(usr, V, mask_solved, mask_undefined);
	points += calcVecV_wareas(usr, V, mask_solved, mask_undefined);

	if (trend_weights != NULL) {
		oper_points * op_pnts = new oper_points(trend_weights, 
							trend_weights_cnt, 
							mask_solved,
							mask_undefined,
							NN);
		T = new oper_complex(1, T, 1, op_pnts);
	}
	
				
	if (write_mat) {

		int cnt = MAX(NN,MM);
		
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
	
	if ( trend_solvable(points, aux_fnc->D1, aux_fnc->D2) )
		solve(T, V, solver_code, X);
	else {
		int i,j,pos;
		for (j = aux_Y_from; j <= aux_Y_to; j++) {
			for (i = aux_X_from; i <= aux_X_to; i++) {
				pos = i + j*NN;
				if (!mask_solved->get(pos))
					mask_undefined->set_true(pos);
			}
		}	
	}
	
	usr->remove_weights();
	usr->remove_weights_cnt();

	if (write_mat) {
		int cnt = MAX(NN,MM);
		char xname[10];
		sprintf(&xname[0],"x%d",cnt);
		matlabWriteVector(X->begin(), X->end(), SURFIT_MAT, xname);
	}

	delete T;
	delete V;
	
	delete tr;

	int i,j,pos;
	for (j = aux_Y_from; j <= aux_Y_to; j++) {
		for (i = aux_X_from; i <= aux_X_to; i++) {
			pos = i + j*NN;
			if (!mask_undefined->get(pos))
				mask_solved->set_true(pos);
		}
	}
};



/////////////////////////////////
//
//  A U X _ F U N C _ U S E R 
//
/////////////////////////////////

trend_user::trend_user() : user ("trend") {};

trend_user::~trend_user() {};

int trend_user::max_priority() {
	return trends_info();
};

void trend_user::init() {
	trend_weights = NULL;
	trend_weights_cnt = NULL;
};

void trend_user::prepare() {};
void trend_user::begin() {};

void trend_user::stage1(int priority) {};
void trend_user::stage2(int priority) {};

void trend_user::stage3(int priority) {

	if (surfit_trend) {
		if (surfit_trend->get_priority() == priority) {
			apply_trend(surfit_trend, 
				    method_X,
				    method_mask_solved,
				    method_mask_undefined,
				    this);
		}
	}
	
	if (surfit_trends->size() > 0) {
		unsigned int trends_cnt;
		for (trends_cnt = 0; trends_cnt < surfit_trends->size(); trends_cnt++) {
			trend * a_aux_fnc = *(surfit_trends->begin()+trends_cnt);
			if (a_aux_fnc) {
				if (a_aux_fnc->get_priority() == priority) {
					apply_trend(a_aux_fnc,
						    method_X,
						    method_mask_solved,
						    method_mask_undefined,
						    this);
				}
			}
		}
	}
};

void trend_user::stage4(int priority) {};
void trend_user::stage5(int priority) {};
void trend_user::finish() {};
void trend_user::release() {
	if (trend_weights) 
		writelog(SURFIT_DEBUG,"trend_weights was not removed!");
	delete trend_weights;
	trend_weights = NULL;
	if (trend_weights) 
		writelog(SURFIT_DEBUG,"trend_weights_cnt was not removed!");
	delete trend_weights_cnt;
	trend_weights_cnt = NULL;
};

vec * trend_user::get_weights() const {
	if (!trend_weights)
		trend_weights = new vec(method_basis_cntX*method_basis_cntY);
	return trend_weights;
};

intvec * trend_user::get_weights_cnt() const {
	if (!trend_weights_cnt)
		trend_weights_cnt = new intvec(method_basis_cntX*method_basis_cntY);
	return trend_weights_cnt;
};

void trend_user::remove_weights() {
	delete trend_weights;
	trend_weights = NULL;
};

void trend_user::remove_weights_cnt() {
	delete trend_weights_cnt;
	trend_weights_cnt = NULL;	
};

}; // namespace surfit;


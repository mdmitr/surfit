
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
#include "wfuncs.h"
#include "wfunc.h"
#include "fileio.h"
#include "grid.h"
#include "bitvec.h"
#include "vec.h"
#include "intvec.h"
#include "free_elements.h"

#include "grid_user.h"
#include "wfunc_user.h"

namespace surfit {

//////////////////////////////////////////////////////
//
//  W F U N C  G L O B A L  V A R I A B L E S
//
//////////////////////////////////////////////////////

wfunc * surfit_wfunc = NULL;
std::vector<wfunc *> * surfit_wfuncs = NULL;

/*! \struct wfunc_garbage
    \brief struct for deletion of \ref wfunc pointers
*/
struct wfunc_garbage : public binman {
	//! inits \ref surfit_wfunc and \ref surfit_wfuncs
	wfunc_garbage() {
		surfit_wfunc = NULL;
		surfit_wfuncs = new std::vector<wfunc *>;
	};
	//! inits \ref surfit_wfunc and \ref surfit_wfuncs
	~wfunc_garbage() {
		delete surfit_wfunc;
		
		if (surfit_wfuncs) {
			free_elements(surfit_wfuncs->begin(), surfit_wfuncs->end());
			delete surfit_wfuncs;
		}
	};
};

wfunc_garbage wfunc_garb;


//////////////////////////////////////////////////////
//
//  W F U N C  U S E F U L   F U N C T I O N S
//
//////////////////////////////////////////////////////

int calcVecV_wfunc(modifier1 * usr, vec * V, wfunc * wfnc, bitvec * mask_solved, bitvec * mask_undefined) {

	int points = 0;

	if (!wfnc)
		return points;

	if (wfnc->getName())
		writelog(SURFIT_MESSAGE,"modifying with wfunc : (%s), size=(%d x %d)", wfnc->getName(), wfnc->getCountX(), wfnc->getCountY());
	else 
		writelog(SURFIT_MESSAGE,"modifying with wfunc : noname, size=(%d x %d)", wfnc->getCountX(), wfnc->getCountY());

	vec * weights = usr->get_weights();
	intvec * weights_cnt = usr->get_weights_cnt();

	if (!weights) {
		writelog(SURFIT_WARNING,"no modifier1 specified!");
		return points;
	}
		
	int NN = method_grid->getCountX();
	int MM = method_grid->getCountY();

	int i, j, I, J;
	int i_from, i_to, j_from, j_to;
	REAL x_from, x_to, y_from, y_to;
	REAL x,y;
	REAL value;
	REAL func_value;
	int counter;
	int func_NN = wfnc->grd->getCountX();
	int func_MM = wfnc->grd->getCountY();
	int N;

	int geom_NN = method_grid->getCountX();
	int geom_MM = method_grid->getCountY();

	REAL f_x, f_y;
	
	j_from = 0;

	for (j = 0; j < geom_MM; j++) {
		y = method_grid->getCoordNodeY(j);
		y_from = y - method_grid->stepY/REAL(2);
		y_to =   y + method_grid->stepY/REAL(2);

		if (j_from >= func_MM) {
			break;
		}

		f_y = wfnc->getCoordNodeY(j_from);

		if (f_y > y_to)
			continue;

		while (f_y < y_from) {
			j_from++;
			f_y = wfnc->getCoordNodeY(j_from);
		}

		j_to = j_from;
		
		while (f_y < y_to) {
			j_to++;
			f_y = wfnc->getCoordNodeY(j_to);
		}

		if (j_from == j_to)
			j_to++;

		j_to = MIN(j_to, func_MM);
								
		i_from = 0;
		for (i = 0; i < geom_NN; i++) {

			N = i + j*method_grid->getCountX();
			
			// check for existance
			if (method_mask_solved->get(N))
				continue;
			if (method_mask_undefined->get(N))
				continue;
			
			x = method_grid->getCoordNodeX(i);
			x_from = x - method_grid->stepX/REAL(2);
			x_to =   x + method_grid->stepX/REAL(2);

			if (i_from >= func_NN) {
				break;
			}
			
			f_x = wfnc->getCoordNodeX(i_from);

			if (f_x > x_to)
				continue;

			while (f_x < x_from) {
				i_from++;
				f_x = wfnc->getCoordNodeX(i_from);
			}

			i_to = i_from;

			while (f_x < x_to) {
				i_to++;
				f_x = wfnc->getCoordNodeX(i_to);
			}
			
			if (i_to == i_from)
				i_to++;

			i_to = MIN(i_to, func_NN);

			counter = 0;
			value = 0;
			for (J = j_from; J < j_to; J++) {
				for (I = i_from; I < i_to; I++) {
					func_value = (*(wfnc->coeff))(I + J*func_NN);
					if (func_value != wfnc->undef_value) {
						value += func_value;
						counter++;
					}
				}
			}
			if (counter != 0) {
				value = value/REAL(counter);
				int pos = i + j*NN;
				if ( (!mask_solved->get(pos)) && (!mask_undefined->get(pos)) ) {
					(*V)(i + j*NN) += value*wfnc->weight;
					(*weights)(i + j*NN) += wfnc->weight;
					(*weights_cnt)(i + j*NN) += 1;
					points++;
				}
			}
			
			i_from = i_to;
		
		}
		
		j_from = j_to;
	
	}

	return points;
	
};

int calcVecV_wfuncs(modifier1 * usr, vec * V, bitvec * mask_solved, bitvec * mask_undefined) {
	int points = 0;
	if (surfit_wfunc) {
		points += calcVecV_wfunc(usr, V, surfit_wfunc, mask_solved, mask_undefined);
	}
	if (surfit_wfuncs) {
		std::vector<wfunc *>::iterator it;
		for (it = surfit_wfuncs->begin(); it != surfit_wfuncs->end(); it++) {
			points += calcVecV_wfunc(usr, V, *it, mask_solved, mask_undefined);
		}
	}
	return points;
};

//////////////////////////////////////////////////////
//
//  W F U N C _ U S E R 
//
//////////////////////////////////////////////////////
	
wfunc_user::wfunc_user() : user("wfunc") {};
wfunc_user::~wfunc_user() {};
	
int wfunc_user::max_priority() {
	return wfuncs_info();
};

void wfunc_user::init() {};
void wfunc_user::prepare() {};
void wfunc_user::begin() {};
void wfunc_user::stage1(int priority) {};
void wfunc_user::stage2(int priority) {};
void wfunc_user::stage3(int priority) {};
void wfunc_user::stage4(int priority) {};
void wfunc_user::stage5(int priority) {};
void wfunc_user::finish() {};
void wfunc_user::release() {};

}; // namespace surfit;


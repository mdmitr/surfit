
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
#include "funcs.h"
#include "func.h"
#include "grid.h"
#include "fileio.h"
#include "bitvec.h"
#include "vec.h"
#include "free_elements.h"

#include "func_user.h"
#include "grid_user.h"

namespace surfit {

///////////////////////////////////////////////////
//
//  F U N C  G L O B A L   V A R I A B L E S
//
///////////////////////////////////////////////////

func                    * surfit_func      = NULL;
std::vector<func *>     * surfit_funcs     = NULL;

/*! \struct func_garbage
    \brief struct for deletion of \ref func pointers
*/
struct func_garbage : public binman {
	//! inits \ref surfit_func and \ref surfit_funcs
	func_garbage() {
		surfit_func = NULL;
		surfit_funcs = new std::vector<func *>;
	};
	//! removes \ref surfit_func and \ref surfit_funcs
	~func_garbage() {
		delete surfit_func;
		if (surfit_funcs) {
			free_elements(surfit_funcs->begin(), surfit_funcs->end());
			delete surfit_funcs;
		}
	};
};

func_garbage func_garb;


///////////////////////////////////////////////////
//
//  F U N C  U S E F U L   F U N C T I O N S
//
///////////////////////////////////////////////////

void ordered_points(func * fnc,
		    grid * grd,
		    vec *& X, 
		    bitvec * mask_solved,
		    bitvec * mask_undefined) 
{
	if (!fnc)
		return;

	if (fnc->getName())
		writelog(SURFIT_MESSAGE,"func : (%s), size=(%d x %d)", fnc->getName(), fnc->getCountX(), fnc->getCountY());
	else 
		writelog(SURFIT_MESSAGE,"func : noname, size=(%d x %d)", fnc->getCountX(), fnc->getCountY());

	int NN = grd->getCountX();
	int MM = grd->getCountY();

	int i, j, I, J;
	int i_from, i_to, j_from, j_to;
	REAL x_from, x_to, y_from, y_to;
	REAL x,y;
	REAL value;
	REAL func_value;
	int counter;
	int func_NN = fnc->grd->getCountX();
	int func_MM = fnc->grd->getCountY();
	int N;

	int geom_NN = grd->getCountX();
	int geom_MM = grd->getCountY();

	REAL f_x, f_y;
	
	j_from = 0;

	for (j = 0; j < geom_MM; j++) {
		y = grd->getCoordNodeY(j);
		y_from = y - grd->stepY/REAL(2);
		y_to =   y + grd->stepY/REAL(2);

		if (j_from >= func_MM) {
			break;
		}

		f_y = fnc->getCoordNodeY(j_from);

		if (f_y > y_to)
			continue;

		while (f_y < y_from) {
			j_from++;
			f_y = fnc->getCoordNodeY(j_from);
		}

		j_to = j_from;
		
		while (f_y < y_to) {
			j_to++;
			f_y = fnc->getCoordNodeY(j_to);
		}

		if (j_from == j_to)
			j_to++;

		j_to = MIN(j_to, func_MM);
								
		i_from = 0;
		for (i = 0; i < geom_NN; i++) {

			N = i + j*grd->getCountX();
			
			// check for existance
			if (mask_solved->get(N))
				continue;
			if (mask_undefined->get(N))
				continue;
			
			x = grd->getCoordNodeX(i);
			x_from = x - grd->stepX/REAL(2);
			x_to =   x + grd->stepX/REAL(2);

			if (i_from >= func_NN) {
				break;
			}
			
			f_x = fnc->getCoordNodeX(i_from);

			if (f_x > x_to)
				continue;

			while (f_x < x_from) {
				i_from++;
				f_x = fnc->getCoordNodeX(i_from);
			}

			i_to = i_from;

			while (f_x < x_to) {
				i_to++;
				f_x = fnc->getCoordNodeX(i_to);
			}
			
			if (i_to == i_from)
				i_to++;

			i_to = MIN(i_to, func_NN);

			counter = 0;
			value = 0;
			for (J = j_from; J < j_to; J++) {
				for (I = i_from; I < i_to; I++) {
					func_value = (*(fnc->coeff))(I + J*func_NN);
					if (func_value != fnc->undef_value) {
						value += func_value;
						counter++;
					}
				}
			}
			if (counter != 0) {
				value = value/REAL(counter);
				(*X)(i + j*NN) = value;
				mask_solved->set_true(i + j*NN);
			}
			
			i_from = i_to;
			
		
		}
		
		j_from = j_to;
	
	}
};


/////////////////////////////////////////
//
//  F U N C _ U S E R 
//
/////////////////////////////////////////

func_user::func_user() : user("func") {};

func_user::~func_user() {};
	
int func_user::max_priority() {
	return funcs_info();
};

void func_user::init() {};
void func_user::prepare() {};
void func_user::begin() {};
void func_user::stage1(int priority) {};
void func_user::stage2(int priority) {};

void func_user::stage3(int priority) {
	if (surfit_func) {
		if (surfit_func->get_priority() == priority) {
			ordered_points(surfit_func,	
				       method_grid,
				       method_X, 
				       method_mask_solved, 
				       method_mask_undefined);
		}
	}
	
	if (surfit_funcs->size() > 0) {
		unsigned int func_cnt;
		for (func_cnt = 0; func_cnt < surfit_funcs->size(); func_cnt++) {
			func * a_fnc = *(surfit_funcs->begin()+func_cnt);
			if (a_fnc) {
				if (a_fnc->get_priority() == priority) {
					ordered_points(a_fnc, 
						       method_grid,
						       method_X, 
						       method_mask_solved, 
						       method_mask_undefined);
				}
			}
		}
	}
};

void func_user::stage4(int priority) {};
void func_user::stage5(int priority) {};
void func_user::finish() {};
void func_user::release() {};

}; // namespace surfit;



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
#include "defareas.h"
#include "defarea.h"
#include "grid.h"
#include "fileio.h"
#include "bitvec.h"
#include "boolvec.h"
#include "free_elements.h"
#include "grid_line.h"
#include "intvec.h"

#include "grid_user.h"
#include "defarea_user.h"

#include "grid_line_user.h"

namespace surfit {

//////////////////////////////////////////////////////
//
//  D E F A R E A  G L O B A L   V A R I A B L E S
//
///////////////////////////////////////////////////////

defarea                 * surfit_defarea   = NULL;
std::vector<defarea *>  * surfit_defareas  = NULL;

/*! \struct defarea_garbage
    \brief struct for deletion of \ref defarea pointers
*/
struct defarea_garbage : public binman {
	//! inits \ref surfit_defarea and \ref surfit_defareas
	defarea_garbage() {
		surfit_defarea   = NULL;
		surfit_defareas  = new std::vector<defarea *>;
	};
	//! removes \ref surfit_defarea and \ref surfit_defareas
	~defarea_garbage() {
		delete surfit_defarea;
		if (surfit_defareas) {
			free_elements(surfit_defareas->begin(), surfit_defareas->end());
			delete surfit_defareas;
		}
	};
};

defarea_garbage defarea_garb;


//////////////////////////////////////////////////////
//
//  D E F A R E A  U S E F U L   F U N C T I O N S 
//
///////////////////////////////////////////////////////

void defarea_update_mask_solved(defarea * def, bitvec * mask_solved) {
	int NN = method_prev_grid->getCountX();
	int MM = method_prev_grid->getCountY();
	int matrix_size = NN*MM;

	int newNN = NN;
	int newMM = MM;

	if (doubleX)
		newNN *= 2;
	if (doubleY)
		newMM *= 2;

	int new_matrix_size = newNN*newMM;

	REAL x,y;
	int n,m;

	int i;
	for (i = 0; i < new_matrix_size; i++) {
		n = i % newNN;
		m = (i - n)/newNN;
		method_grid->getCoordNode(n, m, x, y);
		n = method_prev_grid->get_i(x);
		m = method_prev_grid->get_j(y);
		method_prev_grid->getCoordNode(n, m, x, y);
		if ( !def->getValue(x, y) ) {
			mask_solved->set_false(i);	
		}
	};
};

void ordered_def_points(defarea * def,
			grid * grd,
			vec *& X, 
			bitvec * mask_solved,
			bitvec * mask_undefined) 
{
	if (!def)
		return;

	if (def->getName())
		writelog(SURFIT_MESSAGE,"defarea : (%s), size=(%d x %d)", def->getName(), def->getCountX(), def->getCountY());
	else 
		writelog(SURFIT_MESSAGE,"defarea : noname, size=(%d x %d)", def->getCountX(), def->getCountY());

	int NN = grd->getCountX();
	int MM = grd->getCountY();

	int i, j;
	REAL x,y;
	bool defarea_value;
	int N;

	int geom_NN = grd->getCountX();
	int geom_MM = grd->getCountY();

	for (j = 0; j < geom_MM; j++) {
		y = grd->getCoordNodeY(j);
		
		for (i = 0; i < geom_NN; i++) {
			
			N = i + j*grd->getCountX();
			
			// check for existance
			if (mask_solved->get(N))
				continue;
			if (mask_undefined->get(N))
				continue;
			
			x = grd->getCoordNodeX(i);
			defarea_value = def->getValue(x,y);
			if (!defarea_value) {
				mask_undefined->set_true(i + j*NN);
			}
			
		}

	}
};


///////////////////////////////////////////////
//
//  D E F A R E A _ U S E R
//
///////////////////////////////////////////////

defarea_user::defarea_user() : user("defarea") {};
defarea_user::~defarea_user() {};
	
int defarea_user::max_priority() {
	return defareas_info();
};

void defarea_user::init() {};
void defarea_user::prepare() {};
void defarea_user::begin() {};
void defarea_user::stage1(int priority) {};
void defarea_user::stage2(int priority) {};

void defarea_user::stage3(int priority) {
	if (surfit_defarea) {
		if (surfit_defarea->get_priority() == priority) {
			ordered_def_points(surfit_defarea,	
					   method_grid,
					   method_X, 
					   method_mask_solved, 
					   method_mask_undefined);
		}
	}
	
	if (surfit_defareas->size() > 0) {
		unsigned int defarea_cnt;
		for (defarea_cnt = 0; defarea_cnt < surfit_defareas->size(); defarea_cnt++) {
			defarea * a_def = *(surfit_defareas->begin()+defarea_cnt);
			if (a_def) {
				if (a_def->get_priority() == priority) {
					ordered_def_points(a_def, 
							   method_grid,
							   method_X, 
							   method_mask_solved, 
							   method_mask_undefined);
				}
			}
		}
	}
};

void defarea_user::stage4(int priority) {};
void defarea_user::stage5(int priority) {};
void defarea_user::finish() {};
void defarea_user::release() {};

}; // namespace surfit;


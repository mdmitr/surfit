
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
#include "ptasks.h"
#include "points.h"
#include "sort_alg.h"
#include "ptask.h"
#include "vec.h"
#include "lcm_simple.h"
#include "fileio.h"
#include "free_elements.h"
#include "bitvec.h"

#include "ptask_user.h"
#include "task_user.h"
#include "grid_user.h"

#include <algorithm>

namespace surfit {

/////////////////////////////////////////////////////
//
//  P T A S K   G L O B A L   V A R I A B L E S
//
/////////////////////////////////////////////////////

ptask      *  flow_ptask      = NULL;
std::vector<ptask *>    * flow_ptasks    = NULL;

sub_tasks * sub_ptsks = NULL;
std::vector<void *> * a_sub_ptsks = NULL;
std::vector<ptask *> * ptasks_garbage;

/*! \struct ptask_garbage
    \brief struct for deletion of pointers
*/
struct ptask_garbage : public binman {
	ptask_garbage() {
		flow_ptask     = NULL;
		flow_ptasks    = new std::vector<ptask *>;
	};

	//! garbage sweeper
	~ptask_garbage() {
		delete flow_ptask;
		if (flow_ptasks) {
			free_elements(flow_ptasks->begin(), flow_ptasks->end());
			delete flow_ptasks;
		}
	};
};

ptask_garbage ptask_garb;


/////////////////////////////////////////////////////
//
//  P T A S K   U S E F U L   F U N C T I O N S
//
/////////////////////////////////////////////////////

int calcVecV_ptask(lcm_simple * usr, vec * V, ptask * ptsk, sub_tasks * sub_ptasks, 
		   bitvec * mask_solved, bitvec * mask_undefined) {
	
	int points = 0;
	if (ptsk->getName())
		writelog(SURFIT_MESSAGE,"modifying with ptask : (%s), %d points", ptsk->getName(), ptsk->size());
	else
		writelog(SURFIT_MESSAGE,"modifying with ptask : noname, %d points", ptsk->size());

	REAL mult = REAL(1)/(usr->permeability/usr->viscosity*usr->multiplier);

	REAL total_q = 0;
	
	if (sub_ptasks) {
		unsigned int ptsks_cnt;
		for (ptsks_cnt = 0; ptsks_cnt < sub_ptasks->size(); ptsks_cnt++) {
			
			sub_points * sp = *(sub_ptasks->begin()+ptsks_cnt);
			
			if (!(  mask_solved->get(sp->cell_number) ||
				mask_undefined->get(sp->cell_number)) ) 
			{
				REAL deb_val = sp->sum_value(ptsk);
				(*V)(sp->cell_number) += mult*deb_val;
				total_q += deb_val;
				points++;
			}

		}
	}
	return points;
};

int calcVecV_ptask(lcm_simple * usr, vec * V, bitvec * mask_solved, bitvec * mask_undefined) {

	int points = 0;
	if (!usr)
		return points;

	if (flow_ptask) {
		points += calcVecV_ptask(usr, V, flow_ptask, sub_ptsks, mask_solved, mask_undefined);
	}
	
	if (a_sub_ptsks) {
		unsigned int as_cnt;
		for (as_cnt = 0; as_cnt < a_sub_ptsks->size(); as_cnt++) {
			sub_tasks * a_sub_ptasks = (sub_tasks *)*(a_sub_ptsks->begin()+as_cnt);
			ptask * a_ptsk = *(flow_ptasks->begin()+as_cnt);
			points += calcVecV_ptask(usr, V, a_ptsk, a_sub_ptasks, mask_solved, mask_undefined);
		}
	}
	return points;
};

/////////////////////////////////////////////////////
//
//  P T A S K _ U S E R 
//
/////////////////////////////////////////////////////

ptask_user::ptask_user() : user("ptask") {};
ptask_user::~ptask_user() {};
	
int ptask_user::max_priority() {
	return ptasks_info();
};

void ptask_user::init() {
	ptasks_garbage = new std::vector<ptask *>;
	sub_ptsks = NULL;
	delete a_sub_ptsks;
	a_sub_ptsks = new std::vector<void *>;
};

void ptask_user::prepare() {
	prepare_scattered_points( (task*)flow_ptask, sub_ptsks);
	if (flow_ptasks->size() > 0) {
		unsigned int tasks_counter;
		for (tasks_counter = 0; tasks_counter < flow_ptasks->size(); tasks_counter++) {
			ptask * a_ptask = *(flow_ptasks->begin()+tasks_counter); // additional task
			sub_tasks * a_sub_tsks = NULL;
			prepare_scattered_points( (task*)a_ptask, a_sub_tsks);
			a_sub_ptsks->push_back(a_sub_tsks);
		}
	}
};

void ptask_user::begin() {};
void ptask_user::stage1(int priority) {};
void ptask_user::stage2(int priority) {};

void ptask_user::stage3(int priority) {
	if (flow_ptask) {
		bind_points_to_grid(method_sub_grid, (task*)flow_ptask, sub_ptsks, method_grid);
	}
	
	unsigned int tasks_counter;
	for (tasks_counter = 0; tasks_counter < flow_ptasks->size(); tasks_counter++) {
		ptask * a_ptask = *(flow_ptasks->begin()+tasks_counter);
		sub_tasks * a_sub_ptasks = (sub_tasks *)(*a_sub_ptsks)[tasks_counter];
		bind_points_to_grid(method_sub_grid, a_ptask, a_sub_ptasks, method_grid);
		(*a_sub_ptsks)[tasks_counter] = a_sub_ptasks;
	}
};

void ptask_user::stage4(int priority) {};
void ptask_user::stage5(int priority) {};
void ptask_user::finish() {};

void ptask_user::release() {
	// sub_ptasks deletion
	if (sub_ptsks) {
		free_scattered_points( sub_ptsks );
		sub_ptsks = NULL;
	}
	unsigned int ptasks_counter;
	for (ptasks_counter = 0; ptasks_counter < a_sub_ptsks->size(); ptasks_counter++) {
		sub_tasks * a_sub_ptasks = (sub_tasks *) *(a_sub_ptsks->begin() + ptasks_counter);
		free_scattered_points( a_sub_ptasks );
	}
	delete a_sub_ptsks;
	a_sub_ptsks = NULL;

	// tasks_garbage
	std::vector<ptask *>::iterator it, it2;
	for (it = ptasks_garbage->begin(); it != ptasks_garbage->end(); it++) {
		
		it2 = std::find(flow_ptasks->begin(), flow_ptasks->end(), *it);
		if (it2 != flow_ptasks->end())
			flow_ptasks->erase(it2);
				
		delete *it;
	}
	delete ptasks_garbage;
	ptasks_garbage = NULL;
};

}; // namespace surfit;


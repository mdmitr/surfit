
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
#include <time.h>
#include <vector>
#include "main_method.h"
#include "fileio.h"
#include "grid_tcl.h"
#include "user.h"
#include "variables.h"
#include "variables_tcl.h"
#include "file_manager.h"

#include "grid_user.h"
#include "bitvec.h"

namespace surfit {

bool method_ok;

void universal_solver(std::vector<user *> * users_holder) {
	writelog(SURFIT_MESSAGE,"");
	writelog(SURFIT_MESSAGE,"");
		
	time_t ltime_begin;
	time( &ltime_begin );

	if (!surfit_grid)
		grid_auto();

	// default tolerance, must be defined automatically
	if (tol == 0) {
		tol = float(1e-5);
		writelog(SURFIT_MESSAGE,"tol automatically set to %g", tol);
	}

	unsigned int i;
	
	writelog(SURFIT_MESSAGE,"Sequence list of supported data for selected method:");
	for (i = 0; i < users_holder->size(); i++) {
		user * usr = (*users_holder)[i];
		writelog(SURFIT_MESSAGE,"%s", usr->getName());
	}

	writelog(SURFIT_MESSAGE,"");
	writelog(SURFIT_MESSAGE,"*****************************************");
	if (map_name)
		writelog(SURFIT_MESSAGE,"* Initial data information : (%s)", map_name);
	else
		writelog(SURFIT_MESSAGE,"* Initial data information : ");
	writelog(SURFIT_MESSAGE,"*****************************************");
	writelog(SURFIT_MESSAGE,"Tolerance : %G", tol);
	grid_info();

	int max_priority = 0;

	// PRIORITY
	for (i = 0; i < users_holder->size(); i++) {
		user * usr = *(users_holder->begin() + i);
		max_priority = MAX(max_priority, usr->max_priority());
	};

	writelog(SURFIT_MESSAGE,"");
	writelog(SURFIT_MESSAGE,"*****************************************");
	if (map_name)
		writelog(SURFIT_MESSAGE,"* \"Prepare\" phase : %s", map_name);
	else
		writelog(SURFIT_MESSAGE,"* \"Prepare\" phase");
	writelog(SURFIT_MESSAGE,"*****************************************");

	// INIT
	for (i = 0; i < users_holder->size(); i++) {
		user * usr = *(users_holder->begin() + i);
		usr->init();
	};

	// calculation starts here !
	method_ok = false;

	// PREPARE
	for (i = 0; i < users_holder->size(); i++) {
		user * usr = *(users_holder->begin() + i);
		usr->prepare();
	};

	while (!method_ok) {
			
		// BEGIN
		for (i = 0; i < users_holder->size(); i++) {
			user * usr = *(users_holder->begin() + i);
			usr->begin();
		};

		int current_priority;
		for (current_priority = 0; current_priority <= max_priority; current_priority++) 
		{
			writelog(SURFIT_MESSAGE,"");
			writelog(SURFIT_MESSAGE,"Applying data with \"%d\" priority", current_priority);
			writelog(SURFIT_MESSAGE,"");
			
			for (i = 0; i < users_holder->size(); i++) {
				user * usr = *(users_holder->begin() + i);
				usr->stage1(current_priority);
			};

			for (i = 0; i < users_holder->size(); i++) {
				user * usr = *(users_holder->begin() + i);
				usr->stage2(current_priority);
			};

			for (i = 0; i < users_holder->size(); i++) {
				user * usr = *(users_holder->begin() + i);
				usr->stage3(current_priority);
				bool res = method_mask_solved->get(13);
			};

			for (i = 0; i < users_holder->size(); i++) {
				user * usr = *(users_holder->begin() + i);
				usr->stage4(current_priority);
			};

			for (i = 0; i < users_holder->size(); i++) {
				user * usr = *(users_holder->begin() + i);
				usr->stage5(current_priority);
			};

		}

		int I;
		for (I = (int)users_holder->size()-1; I >= 0; I--) {
			user * usr = *(users_holder->begin() + I);
			usr->finish();
		};

	}

	for (i = 0; i < users_holder->size(); i++) {
		user * usr = *(users_holder->begin() + i);
		usr->release();
	};

	time_t ltime_end;
	time( &ltime_end );
	
	double sec = difftime(ltime_end,ltime_begin);
	int minutes = (int)(sec/REAL(60));
	sec -= minutes*60;
		
	writelog(SURFIT_MESSAGE,"Elapsed time %d minutes %G seconds",minutes,sec);
};

void solve() {

	universal_solver(surfit_users);
			
};

}; // namespace surfit;


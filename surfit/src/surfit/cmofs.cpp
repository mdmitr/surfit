
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

#include "surfit_ie.h"

#include "fileio.h"

#include "cmofs.h"
#include "variables.h"
#include "variables_tcl.h"
#include "functional.h"
#include "free_elements.h"
#include "vec.h"
#include "bitvec.h"

#include <time.h>

#include "grid_user.h"

namespace surfit {

void surfit() {

	writelog(LOG_MESSAGE,"");
	writelog(LOG_MESSAGE,"");
		
	time_t ltime_begin;
	time( &ltime_begin );

	if (map_name == NULL)
		map_name = strdup("noname");

	if (strlen(map_name) == 0) {
		free(map_name);
		map_name = strdup("noname");
	}

	grid_init();
	grid_prepare();

	if (surfit_grid == NULL) {
		writelog(LOG_ERROR,"grid not found : exiting cmofs");
		return;
	}
		
	int i;
	
	while( !method_ok ) {

		grid_begin();

		std::vector<functional *> * Functionals = new std::vector<functional *>(*functionals);
		int f_size = Functionals->size();

		for (i = 0; i < f_size; i++) {

			if (stop_execution == 1) 
				break;
			
			functional * fnc = (*Functionals)[i];
			std::vector<functional *>::iterator fnc_it = Functionals->begin()+i;
			bool res = fnc->minimize();
			if (res == false) {
				if (i+1 < f_size) {
					functional * next_fnc = (*Functionals)[i+1];
					next_fnc->cond_add(fnc);
					next_fnc->cond_move(fnc);
					i--;
					Functionals->erase(fnc_it);
					f_size = Functionals->size();
				}
			} else {
				fnc->mark_solved_and_undefined(method_mask_solved, method_mask_undefined, false);
				if (fnc->cond()) {
					int k;
					for (k = fnc->cond_size()-1; k >= 0; k--) {
						functional * fnc_cnd = fnc->cond_get(k);
						Functionals->insert(fnc_it+1, fnc_cnd);
						fnc->cond_erase(k);
						f_size = Functionals->size();
					}
				}
				fnc->drop_private_data();
			}
			
			
		};

		for (i = 0; i < (int)Functionals->size(); i++) {
			functional * fnc = (*Functionals)[i];
			if (fnc->cond())
				fnc->cond_erase_all();
			fnc->drop_private_data();
		}

		delete Functionals;
		
		if (stop_execution != 1)
			grid_finish();
		else
			break;

	};

	int f_size = functionals->size();

	for (i = 0; i < f_size; i++) {
		functional * f = (*functionals)[i];
		f->cleanup();
	}

	grid_release();

	time_t ltime_end;
	time( &ltime_end );
	
	double sec = difftime(ltime_end,ltime_begin);
	int minutes = (int)(sec/REAL(60));
	sec -= minutes*60;
		
	writelog(LOG_MESSAGE,"Elapsed time %d minutes %G seconds",minutes,sec);

};

}; // namespace surfit;


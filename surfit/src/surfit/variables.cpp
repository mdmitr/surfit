
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

#include "interp.h"
#include "fileio.h"

#include "variables.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "license.h"
#include "surfit_threads.h"

#include "rnd.h"
#include "data_manager.h"

#include "solvers.h"

#include "free_elements.h"
#include "surfit_data.h"
#include "functional.h"

#include <vector>
#include <float.h>
#include <tcl.h>

#ifdef WIN32
#include "windows.h"
#else
#include <unistd.h>
#endif

namespace surfit {

char bigbuffer[1024*30];

float tol = float(1e-5);
char * solver_name = NULL;
bool write_mat = false;
int stop_execution = 0;

int cpu = 1;

int reproject_faults = 1;
int reproject_undef_areas = 0;
int process_isolated_areas = 1;

int penalty_max_iter = 150;
REAL penalty_weight = 1;
REAL penalty_weight_mult = 2;

REAL sor_omega = REAL(0.6);
REAL ssor_omega = REAL(0.6);

REAL undef_value = FLT_MAX;

data_manager *  surfit_data_manager = NULL;
std::vector<functional *> * functionals = NULL;

char * map_name = NULL;

/*! \struct garbage
    \brief struct for init and deletion of different pointers (\ref user)
*/
struct garbage : public binman {
	//! init different pointers
	garbage() {
		surfit_init_all();		
	};
	
	//! removes different pointers (\ref user)
	virtual ~garbage() {
		delete surfit_data_manager;
		surfit_data_manager = NULL;
		if (functionals) {
			release_elements(functionals->begin(), functionals->end());
			delete functionals;
			functionals = NULL;
		}
	};
};

garbage garb;

static void
data_cleanup(ClientData clientData)
{
    clear_data();
#ifdef HAVE_GL_WORKS
//    cleanup();
#endif
};


void surfit_init_all() {

	functionals = new std::vector<functional *>;

	randomize();
	reproject_faults = 1;
	reproject_undef_areas = 0;
	process_isolated_areas = 1;
	tol = float(1e-5);
	undef_value = FLT_MAX;
	write_mat = false;

	sor_omega = REAL(1.6);
	ssor_omega = REAL(1.6);

	surfit_data_manager = new data_manager;
	surfit_data_manager->managers->push_back(new surfit_manager);

	Tcl_CreateThreadExitHandler(data_cleanup, NULL);

#ifdef WIN32
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	cpu = info.dwNumberOfProcessors;
#else
	cpu = sysconf(_SC_NPROCESSORS_ONLN);
	if (cpu < 1)
		cpu = 1;
#endif


};


void surfit_init_variables(Tcl_Interp * iinterp) {

	// 2d
	init_interp(iinterp);
	print_license();
	log_open();

	init_threads(cpu);
	//init_all();
};


void set_tol(float val) {
	tol = val;
};

float get_tol() {
	return tol;
};

void functionals_push_back(functional * f) {
	functionals->push_back(f);
};

}; // namespace surfit;



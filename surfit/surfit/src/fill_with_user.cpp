
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
#include "fill_with.h"
#include "bitvec.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "vec.h"

#include "fill_with_user.h"
#include "grid_user.h"

namespace surfit {

//////////////////////////////////////////////////////////
//
//  F I L L _ W I T H   G L O B A L   V A R I A B L E S
//
//////////////////////////////////////////////////////////

fill_with * surfit_fill_with = NULL;

//////////////////////////////////////////////////////////
//
//  F I L L _ W I T H   U S E F U L   F U N C T I O N S 
//
//////////////////////////////////////////////////////////

/*! \struct fill_with_garbage
    \brief struct for deletion of \ref fill_with pointers
*/
struct fill_with_garbage : public binman {
	//! inits \ref surfit_fill_with
	fill_with_garbage() {
		surfit_fill_with = NULL;
	};
	//! removes \ref surfit_fill_with
	~fill_with_garbage() {
		delete surfit_fill_with;
	};

};

fill_with_garbage fill_with_garb;


///////////////////////////////////////
//
//  F I L L _ W I T H _ U S E R
//
///////////////////////////////////////
fill_with_user::fill_with_user() : user("fill_with") {};
fill_with_user::~fill_with_user() {};
	
int fill_with_user::max_priority() {
	if (!surfit_fill_with)
		return 0;
	return surfit_fill_with->get_priority();
};

void fill_with_user::init() {};
void fill_with_user::prepare() {};
void fill_with_user::begin() {};
void fill_with_user::stage1(int priority) {};
void fill_with_user::stage2(int priority) {};

void fill_with_user::stage3(int priority) {
	if (!surfit_fill_with)
		return;

	if (surfit_fill_with->get_priority() != priority)
		return;

	if (surfit_fill_with->value != undef_value)
		writelog(SURFIT_MESSAGE,"fill_with : %g", surfit_fill_with->value);
	else 
		writelog(SURFIT_MESSAGE,"fill_with : undef_value");

	int size = method_mask_solved->size();
	int i;
	for (i = 0; i < size; i++) {
		if ( !method_mask_solved->get(i) && !method_mask_undefined->get(i) ) {
			if (surfit_fill_with->value != undef_value) {
				(*method_X)(i) = surfit_fill_with->value;
				method_mask_solved->set_true(i);
			} else {
				(*method_X)(i) = surfit_fill_with->value;
				method_mask_undefined->set_true(i);
			};
		}
	};
			
};

void fill_with_user::stage4(int priority) {};
void fill_with_user::stage5(int priority) {};
void fill_with_user::finish() {};
void fill_with_user::release() {};

}; // namespace surfit;



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

#ifndef __surfit_dynamic_user_included__
#define __surfit_dynamic_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class dynamic;

/*! \ingroup surfit_data_variables
    \var surfit_dynamic
    \brief dynamically-loaded data (\ref data)

\sa 
\li \ref tcl_dynamic "Tcl commands"

*/
extern SURFIT_EXPORT dynamic * surfit_dynamic;

/*! \ingroup surfit_variables_collections
    \var std::vector<dynamic *> * surfit_dynamics;
    collection of \ref dynamic objects
*/
extern SURFIT_EXPORT std::vector<dynamic *> * surfit_dynamics;

/*! \class dynamic_user
    \brief interface class for making equations from \ref dynamic
*/
class SURFIT_EXPORT dynamic_user : public user {
public:

	//! constructor
	dynamic_user();

	//! destructor
	~dynamic_user();
	
	int max_priority();
	void init();
	void prepare();
	void begin();
	void stage1(int priority);
	void stage2(int priority);
	void stage3(int priority);
	void stage4(int priority);
	void stage5(int priority);
	void finish();
	void release();

};

}; // namespace surfit;

#endif


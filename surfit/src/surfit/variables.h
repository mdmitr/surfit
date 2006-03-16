
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

#ifndef __surfit__variables__
#define __surfit__variables__

#include <vector>

namespace surfit {

	class data_manager;
	extern SURFIT_EXPORT data_manager * surfit_data_manager;

	class user;
	
	//
	// Collections
	//

	class functional;
	extern SURFIT_EXPORT std::vector<functional*> * functionals;

	SURFIT_EXPORT 
	void functionals_push_back(functional * f);

	extern char * solver_name;

};

#endif



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

#ifndef __surfit_f_triangulate_included__
#define __surfit_f_triangulate_included__

#include "f_method.h"
#include "vec.h"

namespace surfit {

class d_surf;
class f_surf;

//! implements gridding method called "triangulation"
class f_triangulate : public f_method
{
public:
	//! constructor
	f_triangulate();
	//! destructor
	~f_triangulate();

	virtual d_surf * get_method_surf();
	virtual const char * get_method_name();
};

}; // namespace surfit

#endif


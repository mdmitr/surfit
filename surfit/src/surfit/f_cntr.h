
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

#ifndef __surfit_f_cntr_included__
#define __surfit_f_cntr_included__

#include "functional.h"
#include "f_points.h"

namespace surfit {

class d_points;
class f_points;
class d_cntr;
class bitvec;
class vec;
class sizetvec;

/*! \class f_cntr
    \brief functional for approximating contour
*/
class SURFIT_EXPORT f_cntr : public f_points_user {
public:
	//! constructor
	f_cntr(const d_cntr * icontour);
	//! destructor
	~f_cntr();

	d_points * get_points();
	
protected:

	int this_get_data_count() const;
	const data * this_get_data(int pos) const;

	//! contour for approximation
	const d_cntr * contour;
};

}; // namespace surfit

#endif


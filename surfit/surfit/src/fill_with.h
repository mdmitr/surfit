
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

#ifndef __fill_with__included__
#define __fill_with__included__

#include "data.h"

namespace surfit {

/*! \class fill_with
    \brief sets values of all unsolved cells to "value" (see \ref surfit_fill_with). See \ref tcl_fill_with "Tcl commands" for \ref fill_with.
*/
class SURFIT_EXPORT fill_with : public data {
public:
	//! constructor
	fill_with(REAL ivalue);

	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const;

	//! fill value
	REAL value;

};

}; // namespace surfit;

#endif


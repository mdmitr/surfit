
/*------------------------------------------------------------------------------
 *	$Id: cntr_internal.h 823 2006-07-12 10:15:53Z mishadm $
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

#ifndef __surfit_cntr_trace_included__
#define __surfit_cntr_trace_included__

#include <vector>
#include "vec.h"
#include "bitvec.h"

namespace surfit {

//! class for isoline
struct fiso
{
	//! constructor 
	fiso(REAL ilevel, 
	     size_t ilevel_number, 
	     size_t ilevels, 
	     bitvec * ichecks,
	     size_t inn, size_t imm);

	//! destructor
	~fiso();
	
	//! returns isoline level
	REAL get_level() const;

	//! returns isoline number
	size_t get_level_number() const;

	//! adds point to isoline
	void add_point(REAL px, REAL py, size_t i, size_t j, bool visible);

	//! gets point from isoline by its number
	void get_point(size_t pos, REAL & px, REAL & py, bool & visible) const;

	//! returns number of points in isoline
	size_t size() const;

	//! return value for filling isoline
	REAL get_fill_level() const;
	
	//! sets fill value
	void set_fill_level(REAL ival, bool force = false);

	//! returns checksum
	int get_checksum() const;

	//! returns iterator for the x-coord of the first points
	vec::iterator x_begin() const;
	//! returns iterator 
	vec::iterator x_end() const;
	//! returns iterator for the y-coord of the first points
	vec::iterator y_begin() const;
	//! returns iterator 
	vec::iterator y_end() const;
	
	//! x-coords
	vec * x;
	//! y-coords
	vec * y;
	
private:

	//! visibility flags
	std::vector<bool> * flags;

	//! optimization vector
	bitvec * checks;

	//! level number
	size_t level_number;
	
	//! number of levels for isolines
	size_t levels;
	
	//! number of grid cells in OX direction
	size_t nn;
		
	//! number of grid cells in OY direction
	size_t mm;

	//! isoline level
	REAL level;
	
	//! isoline fill level
	REAL fill_level;
	
	//! checksum (for speed)
	int checksum;
};

//! calculates isolines for surface
std::vector<fiso *> * trace_isos(vec * levels,
				 vec * x_coords,
				 vec * y_coords,
				 extvec * data,
				 size_t nn, size_t mm,
				 REAL uval,
				 bool close_on_bound);

}; // namespace surfit

#endif


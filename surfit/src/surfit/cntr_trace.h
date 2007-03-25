
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

struct fiso
{
	fiso(REAL ilevel, 
	     size_t ilevel_number, 
	     size_t ilevels, 
	     bitvec * ichecks,
	     size_t inn, size_t imm);
	~fiso();
	
	REAL get_level() const;
	size_t get_level_number() const;
	void add_point(REAL px, REAL py, size_t i, size_t j, bool visible);
	void get_point(size_t pos, REAL & px, REAL & py, bool & visible) const;
	size_t size() const;
	REAL get_fill_level() const;
	void set_fill_level(REAL ival);
	int get_checksum() const;

	vec::iterator x_begin() const;
	vec::iterator x_end() const;
	vec::iterator y_begin() const;
	vec::iterator y_end() const;
	
	vec * x;
	vec * y;
private:
	std::vector<bool> * flags;
	bitvec * checks;
	size_t level_number;
	size_t levels;
	size_t nn, mm;
	REAL level;
	REAL fill_level;
	int checksum;
};

std::vector<fiso *> * trace_isos(vec * levels,
				 vec * x_coords,
				 vec * y_coords,
				 extvec * data,
				 size_t nn, size_t mm,
				 REAL uval,
				 bool close_on_bound);

}; // namespace surfit

#endif



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

#ifndef __color_scale_included__
#define __color_scale_included__

#include "real.h"

#include <vector>

namespace surfit {

#define DEFAULT_COLORS 89, 138, 237, 227, 46, 32

/*!
	\class color_scale
	\brief class of color scale for \ref func or \ref trend or \ref wfunc
*/
class SURFIT_EXPORT color_scale {
public:
	//! constructor 
	color_scale(REAL from, REAL to, REAL step,
		    int r_from, int g_from, int b_from,
		    int r_to, int g_to, int b_to);

	//! destructor
	~color_scale();

	//! sets color_scale (like constructor)
	void set(REAL from, REAL to, REAL step,
		 int r_from, int g_from, int b_from,
		 int r_to, int g_to, int b_to);
	//! adds new color_scale interval
	void add(REAL from, REAL to, REAL step,
		 int r_from, int g_from, int b_from,
		 int r_to, int g_to, int b_to);

	//! returns color for value
	void get_value(REAL value, int & r, int & g, int & b) const;

	//! returns value for specified position
	virtual REAL get_value(int pos) const;

	//! returns color_scale size (amount of colors)
	int size() const;

	//! returs color for specified position
	bool get_color(int pos, int & r, int & g, int &b) const;
	//! sets first color in color scale
	void set_color_from(int r, int g, int b);
	//! sets last color in color scale
	void set_color_to(int r, int g, int b);
	//! sets minimum value
	void set_min(REAL min_val);
	//! sets maximum value
	void set_max(REAL max_val);
	//! sets step for values
	void set_step(REAL step_val);

	//! returns parameters of color_scale
	bool get_params(REAL & from, REAL & to, REAL & step,
		        int & r_from, int & g_from, int & b_from,
			int & r_to, int & g_to, int & b_to);

	//! returns false if color_scale is not default
	bool is_default() { return default_cs; };
	//! sets color_scale to default
	void set_default(bool val) { default_cs = val; };
	
private:

	//! array of red-colors
	std::vector<int>  * r_values;
	//! array of green-colors
	std::vector<int>  * g_values;
	//! array of blue-colors
	std::vector<int>  * b_values;
	//! array of values
	std::vector<REAL> * values;
	//! flag for checking defaultness
	bool default_cs;

};

SURFIT_EXPORT
color_scale * get_surfit_color_scale();

SURFIT_EXPORT
void set_color_scale(REAL from, REAL to, REAL step,
                     int r1, int g1, int b1,
		     int r2, int g2, int b2);

SURFIT_EXPORT
void set_default_color_scale();

}; // namespace surfit;

#endif


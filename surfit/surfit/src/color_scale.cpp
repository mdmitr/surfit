
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
#include "color_scale.h"
#include "variables_internal.h"

#include <algorithm>

namespace surfit {

int check_color(int color) {
	color = MIN(255, color);
	color = MAX(0, color);
	return color;
}

color_scale::color_scale(REAL from, REAL to, REAL step,
                         int r_from, int g_from, int b_from,
                         int r_to, int g_to, int b_to) 
{
	r_values = NULL;
	g_values = NULL;
	b_values = NULL;
	values = NULL;
	set(from, to, step, 
		r_from, g_from, b_from,
		r_to, g_to, b_to);
	default_cs = false;	
};

color_scale::~color_scale() 
{
	delete r_values;
	delete g_values;
	delete b_values;
	delete values;
};

void color_scale::set(REAL from, REAL to, REAL step,
                      int r_from, int g_from, int b_from,
                      int r_to, int g_to, int b_to)
{
	delete r_values;
	delete g_values;
	delete b_values;
	delete values;
	r_values = NULL;
	g_values = NULL;
	b_values = NULL;
	values = NULL;

	int size = int((to-from)/step) + 1;
	if (size <= 0)
		return;

	r_values = new std::vector<int>(size+1);
	g_values = new std::vector<int>(size+1);
	b_values = new std::vector<int>(size+1);
	values   = new std::vector<REAL>(size);
	
	int i;
	REAL r_step = (r_to-r_from)/REAL(size);
	REAL g_step = (g_to-g_from)/REAL(size);
	REAL b_step = (b_to-b_from)/REAL(size);
	REAL r_val, g_val, b_val;

	for (i = 0; i < size; i++) {
		r_val = check_color(int(r_from + i*r_step));
		g_val = check_color(int(g_from + i*g_step));
		b_val = check_color(int(b_from + i*b_step));
		(*values)[i] = from + i*step;
		(*r_values)[i] = (int)r_val;
		(*g_values)[i] = (int)g_val;
		(*b_values)[i] = (int)b_val;
	};
	r_val = check_color(int(r_from + i*r_step));
	g_val = check_color(int(g_from + i*g_step));
	b_val = check_color(int(b_from + i*b_step));
	(*r_values)[i] = (int)r_val;
	(*g_values)[i] = (int)g_val;
	(*b_values)[i] = (int)b_val;
	default_cs = false;
}

void color_scale::add(REAL from, REAL to, REAL step,
                      int r_from, int g_from, int b_from,
                      int r_to, int g_to, int b_to)
{
	
	int size = int((to-from)/step) + 1;
	if (size <= 0)
		return;

	int old_size = r_values->size();
	r_values->resize(old_size + size + 1);
	g_values->resize(old_size + size + 1);
	b_values->resize(old_size + size + 1);
	values->resize(old_size + size );
	
	int i;
	REAL r_step = (r_to-r_from)/REAL(size);
	REAL g_step = (g_to-g_from)/REAL(size);
	REAL b_step = (b_to-b_from)/REAL(size);
	int r_val, g_val, b_val;

	for (i = old_size; i < old_size+size; i++) {
		r_val = check_color(int(r_from + (i-old_size)*r_step));
		g_val = check_color(int(g_from + (i-old_size)*g_step));
		b_val = check_color(int(b_from + (i-old_size)*b_step));
		(*values)[i-1] = from + (i-old_size)*step;
		(*r_values)[i] = r_val;
		(*g_values)[i] = g_val;
		(*b_values)[i] = b_val;
	};
	r_val = check_color(int(r_from + (i-old_size)*r_step));
	g_val = check_color(int(g_from + (i-old_size)*g_step));
	b_val = check_color(int(b_from + (i-old_size)*b_step));
	(*r_values)[old_size+size] = r_val;
	(*g_values)[old_size+size] = g_val;
	(*b_values)[old_size+size] = b_val;
	default_cs = false;
}

void color_scale::get_value(REAL value, int & r, int & g, int & b) const
{
	if (!values)
		return;
	int size = values->size();
	if (size == 0)
		return;
	
	std::vector<REAL>::const_iterator it = std::lower_bound(values->begin(), values->end(), value);
	
	if (it == values->end()) {
		r = (*r_values)[size-1];
		g = (*g_values)[size-1];
		b = (*b_values)[size-1];
	} else {
		int pos = it-values->begin();
		r = (*r_values)[pos];
		g = (*g_values)[pos];
		b = (*b_values)[pos];
	}

	return;
	
};

int color_scale::size() const {
	if (!r_values)
		return 0;

	return r_values->size();
};

bool color_scale::get_color(int pos, int & r, int & g, int &b) const {
	if (!r_values)
		return false;

	if ((pos < 0) || (pos > (int)r_values->size()))
		return false;

	r = (*r_values)[pos];
	g = (*g_values)[pos];
	b = (*b_values)[pos];
	return true;
};

bool color_scale::get_params(REAL & from, REAL & to, REAL & step,
                             int & r_from, int & g_from, int & b_from,
                             int & r_to, int & g_to, int & b_to) 
{
	if (!values)
		return false;

	if (values->size() == 0)
		return false;

	from = (*values)[0];
	to = (*values)[values->size()-1];
	step = (to-from)/(values->size()-1);

	int size = r_values->size();
	r_from = (*r_values)[0];
	g_from = (*g_values)[0];
	b_from = (*b_values)[0];

	r_to = (*r_values)[size-1];
	g_to = (*g_values)[size-1];
	b_to = (*b_values)[size-1];

	return true;
};

void color_scale::set_color_from(int r, int g, int b) {
	REAL from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	r_from = r;
	g_from = g;
	b_from = b;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

void color_scale::set_color_to(int r, int g, int b) {
	REAL from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	r_to = r;
	g_to = g;
	b_to = b;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

void color_scale::set_min(REAL min_val) {
	REAL from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	from = min_val;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

REAL color_scale::get_value(int pos) const {
	return (*values)[pos];
};

void color_scale::set_max(REAL max_val) {
	REAL from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	to = max_val;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

void color_scale::set_step(REAL step_val) {
	REAL from, to, step;
	int r_from, g_from, b_from;
	int r_to, g_to, b_to;

	get_params(from, to, step,
		   r_from, g_from, b_from,
		   r_to, g_to, b_to);

	step = step_val;

	set(from, to, step,
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);

};

color_scale * get_surfit_color_scale() {
	return surfit_color_scale;
};

void set_color_scale(REAL from, REAL to, REAL step,
                     int r1, int g1, int b1,
		     int r2, int g2, int b2) {
	if (surfit_color_scale)
		surfit_color_scale->set(from, to, step, r1, g1, b1, r2, g2, b2);
	else {
		surfit_color_scale = new color_scale(from, to, step, r1, g1, b1, r2, g2, b2);
	}
};

void set_default_color_scale() {
	if (surfit_color_scale)
		surfit_color_scale->set_default(true);
};

}; // namespace surfit;


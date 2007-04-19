
/*------------------------------------------------------------------------------
 *	$Id: cntr_tcl.cpp 823 2006-07-12 10:15:53Z mishadm $
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

#include "surfit_ie.h"
#include "cntr_trace.h"
#include "grid_user.h"
#include "bitvec.h"

#include <float.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>

namespace surfit {

struct trace_info
{
	vec * levels;
	vec * x_coords;
	vec * y_coords;
	extvec * data;
	bitvec * checks;
	size_t nn, mm;
	REAL uval;
	bool close_on_bound;
};

inline 
size_t level_index(REAL level, trace_info & info)
{
	vec::iterator it = std::find(info.levels->begin(), info.levels->end(), level);
	if (it != info.levels->end())
		return it - info.levels->begin();
	assert(0);
	return UINT_MAX;
};

fiso::fiso(REAL ilevel, size_t ilevel_number, size_t ilevels, bitvec * ichecks, size_t inn, size_t imm)
{	
	x = create_vec(0,0,0,MAX(inn,imm));
	x->reserve(MAX(inn,imm));
	y = create_vec(0,0,0,MAX(inn,imm));
	y->reserve(MAX(inn,imm));
	flags = new std::vector<bool>();
	level = ilevel;
	levels = ilevels;
	level_number = ilevel_number;
	nn = inn;
	mm = imm;
	checks = ichecks;
	fill_level = FLT_MAX;
	checksum = 0;
};

fiso::~fiso()
{
	x->release();
	y->release();
	delete flags;
};

REAL fiso::get_level() const 
{ 
	return level; 
};

size_t fiso::get_level_number() const
{
	return level_number;
};

void fiso::add_point(REAL px, REAL py, size_t i, size_t j, bool visible)
{
	x->push_back(px);
	y->push_back(py);
	flags->push_back(visible);
	if (level_number != UINT_MAX)
	{
		size_t pos;
		pos = three2one(i, j, level_number, nn, mm, levels);
		checks->set_true(pos);
	}
	checksum += i+j;
};

void fiso::get_point(size_t pos, REAL & px, REAL & py, bool & visible) const
{
	px = (*x)(pos);
	py = (*y)(pos);
	visible = (*flags)[pos];
};

size_t fiso::size() const 
{ 
	return x->size(); 
};

REAL fiso::get_fill_level() const 
{ 
	return fill_level; 
};

void fiso::set_fill_level(REAL ival) 
{ 
	if ( level < FLT_MAX/2. )
		fill_level = ival; 
};

int fiso::get_checksum() const 
{ 
	return checksum; 
};

vec::iterator fiso::x_begin() const
{
	return x->begin();
};

vec::iterator fiso::x_end() const
{
	return x->end();
};

vec::iterator fiso::y_begin() const
{
	return y->begin();
};

vec::iterator fiso::y_end() const
{
	return y->end();
};

#define SIDE_BOTTOM 0
#define SIDE_LEFT 1
#define SIDE_TOP 2
#define SIDE_RIGHT 3

#define EPS 1e-6

short opp_side[4]={SIDE_TOP, SIDE_RIGHT, SIDE_BOTTOM, SIDE_LEFT};

// modifies value a little
REAL bug_value(REAL val)
{
	if (val < 1)
		return val + EPS;
	REAL rank = log10(val);
	return val + EPS*pow(10.,rank);
};

// returns val1 >= val2
inline
bool cmp_vals(REAL val1, REAL val2, REAL uval)
{
	if (val1 == uval)
		return true;
	if (val2 == uval)
		return false;
	return (val1 >= val2);
};

// returns true in case of level lies between val1 and val2
inline
bool check_level_intersection(REAL val1, REAL val2, REAL level, REAL uval)
{
        if (val1 == uval)
		return (val2 < level);
	if (val2 == uval)
		return (val1 < level);
        return ( ((val1 > level) && (val2 < level)) || ((val2 > level) && (val1 < level)));
};

inline
void calc_point(REAL level, short side, size_t i, size_t j,
		REAL vals[4],
		trace_info & info, REAL & x, REAL & y, bool & visible)
{
	REAL x0, x1;
	REAL y0, y1;
	visible = true;
	REAL w;
	switch(side) {
		case SIDE_BOTTOM:
			{
				assert(vals[0] != vals[1]);
				x0 = (*(info.x_coords))(i);
				x1 = (*(info.x_coords))(i+1);
				if ((vals[0] == info.uval) || (vals[1] == info.uval))
				{
					w = 0.5;
					visible = false;
				}
				else
					w = (level-vals[0])/(vals[1]-vals[0]);
				x = x0 + (x1-x0)*w;
				y = (*(info.y_coords))(j);
			}
			break;
		case SIDE_LEFT:
			{
				x = (*(info.x_coords))(i);
				if ((vals[0] == info.uval) || (vals[2] == info.uval))
				{
					w = 0.5;
					visible = false;
				}
				else
					w = (level-vals[0])/(vals[2]-vals[0]);
				y0 = (*(info.y_coords))(j);
				y1 = (*(info.y_coords))(j+1);
				y = y0 + (y1-y0)*w;
			}
			break;
		case SIDE_TOP:
			{
				x0 = (*(info.x_coords))(i);
				x1 = (*(info.x_coords))(i+1);
				if ((vals[2] == info.uval) || (vals[3] == info.uval))
				{
					w = 0.5;
					visible = false;
				}
				else
					w = (level-vals[2])/(vals[3]-vals[2]);
				x = x0 + (x1-x0)*w;
				y = (*(info.y_coords))(j+1);
			}
			break;
		case SIDE_RIGHT:
			{
				x = (*(info.x_coords))(i+1);
				if ((vals[3] == info.uval) || (vals[1] == info.uval))
				{
					w = 0.5;
					visible = false;
				}
				else
					w = (level-vals[1])/(vals[3]-vals[1]);
				y0 = (*(info.y_coords))(j);
				y1 = (*(info.y_coords))(j+1);
				y = y0 + (y1-y0)*w;
			}
			break;
	}
};

inline 
bool is_edge_rib(short s, size_t i, size_t j, size_t nn, size_t mm)
{
	return (( (i == 0) && (s == SIDE_LEFT) )	|| 
		( (i == nn-2) && (s == SIDE_RIGHT) )	||
		( (j == 0) && (s == SIDE_BOTTOM) )	|| 
		( (j == mm-2) && (s == SIDE_TOP) ) );
};

inline
void update_vals(REAL vals[4], size_t i, size_t j, trace_info & info)
{
	size_t pos = two2one(i, j, info.nn, info.mm);
	vals[0] = (*(info.data))(pos);
	pos++;
	vals[1] = (*(info.data))(pos);
	pos += info.nn-1;
	vals[2] = (*(info.data))(pos);
	pos++;
	vals[3] = (*(info.data))(pos);
};

inline 
void add_bottom_edge(fiso * iso, size_t i_from, size_t i_to, trace_info & info)
{
	REAL x0, x1, y;
	x0 = (*(info.x_coords))(i_from);
	x1 = (*(info.x_coords))(i_to);
	y = (*(info.y_coords))(0);
	iso->add_point(x0, y, i_from, 0, false);
	iso->add_point(x1, y, i_to, 0, false);
};

inline 
void add_top_edge(fiso * iso, size_t i_from, size_t i_to, trace_info & info)
{
	REAL x0, x1, y;
	x0 = (*(info.x_coords))(i_from);
	x1 = (*(info.x_coords))(i_to);
	y = (*(info.y_coords))( info.y_coords->size()-1 );
	iso->add_point(x0, y, i_from, info.y_coords->size()-1, false );
	iso->add_point(x1, y, i_to, info.y_coords->size()-1, false );
};

inline 
void add_left_edge(fiso * iso, size_t j_from, size_t j_to, trace_info & info)
{
	REAL x, y0, y1;
	y0 = (*(info.y_coords))(j_from);
	y1 = (*(info.y_coords))(j_to);
	x = (*(info.x_coords))(0);
	iso->add_point(x, y0, 0, j_from, false);
	iso->add_point(x, y1, 0, j_to, false);
};

inline 
void add_right_edge(fiso * iso, size_t j_from, size_t j_to, trace_info & info)
{
	REAL x, y0, y1;
	y0 = (*(info.y_coords))(j_from);
	y1 = (*(info.y_coords))(j_to);
	x = (*(info.x_coords))( info.x_coords->size()-1 );
	iso->add_point(x, y0, info.x_coords->size()-1, j_from, false);
	iso->add_point(x, y1, info.x_coords->size()-1, j_to, false);
};

struct next_rib_info
{
	size_t first_i;
	size_t first_j;
	size_t first_side;
};

inline
void finalize_iso(fiso * iso, REAL level, size_t & i, size_t & j, short & res, trace_info & info, 
		  next_rib_info & rib_info, short end_side)
{
	size_t k = level_index(level, info);
	if (k == UINT_MAX)
		return;
	
	// mark cell 
	size_t pos;
	pos = three2one(i, j, k, info.nn, info.mm, info.levels->size());
	info.checks->set_true(pos);

	short begin_side = rib_info.first_side;
	size_t nn = info.nn;
	size_t mm = info.mm;
	size_t fi = rib_info.first_i;
	size_t fj = rib_info.first_j;

	if (begin_side == SIDE_BOTTOM)
	{
		if (end_side ==  SIDE_LEFT)
		{
			add_left_edge(iso, j, mm-1,info);
			add_top_edge(iso, 0, nn-1, info);
			add_right_edge(iso, mm-1, 0, info);
			add_bottom_edge(iso, nn-1, fi+1, info);
		}
		if (end_side == SIDE_TOP)
		{
			add_top_edge(iso, i, nn-1, info);
			add_right_edge(iso, mm-1, 0, info);
			add_bottom_edge(iso, nn-1, fi+1, info);
		}
		if (end_side == SIDE_RIGHT)
		{
			add_right_edge(iso, j, 0, info);
			add_bottom_edge(iso, nn-1, fi+1, info);
		}
		if (end_side == SIDE_BOTTOM)
		{
			add_bottom_edge(iso, i, fi+1, info);
		}
	}
	if (begin_side == SIDE_LEFT)
	{
		if (end_side == SIDE_RIGHT)
		{
			add_right_edge(iso, j, mm-1, info);
			add_top_edge(iso, nn-1, 0, info);
			add_left_edge(iso, mm-1, fj+1, info);
		}
		if (end_side == SIDE_TOP)
		{
			add_top_edge(iso, i, 0, info);
			add_left_edge(iso, mm-1, fj+1, info);
		}
		if (end_side == SIDE_LEFT)
		{
			add_left_edge(iso, j, fj+1, info);
		}
	}
	if (begin_side == SIDE_TOP)
	{
		if (end_side == SIDE_RIGHT)
		{
			add_right_edge(iso, j, 0, info);
			add_top_edge(iso, nn-1, fi+1, info);
		}
		if (end_side == SIDE_TOP)
		{
			add_top_edge(iso, i, fi+1, info);
		}
	}
	if (begin_side == SIDE_RIGHT)
	{
		if (end_side == SIDE_RIGHT)
		{
			add_right_edge(iso, j, fj+1, info);
		}
	}

	// add first point
	i = rib_info.first_i;
	j = rib_info.first_j;
	REAL x, y;
	bool vis;
	iso->get_point(0, x, y, vis);
	iso->add_point(x, y, i, j, false);
	
	res = rib_info.first_side;
	
};

inline 
short get_next_rib(REAL level, 
		   short side, 
		   size_t & i, size_t & j, 
		   REAL vals[4], 
		   trace_info & info, 
		   bool closed, 
		   bool & need_add, 
		   fiso * iso, 
		   next_rib_info & rib_info)
{
	need_add = true;
	short res = side;
	short sx = 0, sy = 0;
	switch (side)
	{
	case SIDE_BOTTOM:
		{
			if (check_level_intersection( vals[0], vals[3], level, info.uval ))
			{
				if (check_level_intersection(vals[0], vals[2], level, info.uval))
				{
					res = SIDE_RIGHT;
					sx = -1;
				}
				else
				{
					res = SIDE_BOTTOM;
					sy = 1;
				}
			} 
			else 
			{
				res = SIDE_LEFT;
				sx = 1;
			}
		};
		break;
	case SIDE_LEFT:
		{
			if (check_level_intersection( vals[0], vals[3], level, info.uval ))
			{
				if (check_level_intersection(vals[0], vals[1], level, info.uval))
				{
					res = SIDE_TOP;
					sy = -1;
				}
				else
				{
					res = SIDE_LEFT;
					sx = 1;
				}
			}
			else 
			{
				res = SIDE_BOTTOM;
				sy = 1;
			}
		};
		break;
	case SIDE_TOP:
		{
			if (check_level_intersection( vals[0], vals[3], level, info.uval ))
			{
				if (check_level_intersection( vals[1], vals[3], level, info.uval ))
				{
					res = SIDE_LEFT;
					sx = 1;
				}
				else
				{
					res = SIDE_TOP;
					sy = -1;
				}
			}
			else
			{
				res = SIDE_RIGHT;
				sx = -1;
			}

		};
		break;
	case SIDE_RIGHT:
		{
			if (check_level_intersection( vals[0], vals[3], level, info.uval ))
			{
				if (check_level_intersection( vals[2], vals[3], level, info.uval ))
				{
					res = SIDE_BOTTOM;
					sy = 1;
				}
				else
				{
					res = SIDE_RIGHT;
					sx = -1;
				}
			}
			else
			{
				res = SIDE_TOP;
				sy = -1;
			}
		};
		break;
	};

	// check for bound
	short oside = opp_side[res];
	if ( is_edge_rib(oside, i, j, info.nn, info.mm) )
	{
		if (closed)
		{
			need_add = false;
			return SHRT_MAX;
		}
		else 
		{
			if (info.close_on_bound)
				finalize_iso(iso, level, i, j, res, info, rib_info, oside);
			else {
				REAL x, y;
				bool visible;
				calc_point(level, oside, i, j, vals, info, x, y, visible);
				iso->add_point(x,y,i,j,visible);
			}
			need_add = false;
			return res;
		}
	}
	else
	{
		i += sx;
		j += sy;
		update_vals(vals, i, j, info);
	}

	return res;
};

REAL get_fill_level(REAL level, short side, size_t i, size_t j, trace_info & info)
{
	size_t k = level_index(level, info);
	
	bool inc = 0;
	if (side == SIDE_LEFT)
		j++;
	if (side == SIDE_BOTTOM)
		i++;
	if ((side == SIDE_RIGHT) || (side == SIDE_TOP))
	{
		i++;
		j++;
	}

	size_t pos;
	pos = two2one(i, j, info.nn, info.mm);
	REAL check_val = (*(info.data))(pos);
	int l_cnt = info.levels->size();
	REAL added_level = (*(info.levels))(l_cnt-1);

	if ( cmp_vals(check_val, level, info.uval) )
	{
		if (k == l_cnt - 1) {
			return added_level;
		} else {
			if (((*(info.levels))(k+1) == added_level) && (check_val > added_level))
				return FLT_MAX;
			return ((*(info.levels))(k) + (*(info.levels))(k+1) ) / 2.;
		}
	}
	else
	{
		if (k == 0) {
			return (*(info.levels))(k) / 2.;
		} else {
			return ((*(info.levels))(k) + (*(info.levels))(k-1) ) / 2.;
		}
	}
	
	return FLT_MAX;

};

fiso * trace_isoline(REAL level, short side, size_t i, size_t j, 
		     REAL vals[4],  trace_info & info, bool closed)
{

	bool need_add;
	REAL x,y;
	bool visible;
	short curr_side = side;
	next_rib_info rib_info;
	rib_info.first_i = i;
	rib_info.first_j = j;
	rib_info.first_side = side;
	size_t level_number = level_index(level, info);

	fiso * iso = new fiso(level, level_number, info.levels->size(), info.checks, info.nn, info.mm);

	// find first point
	calc_point(level, side, i, j, vals, info, x, y, visible);
	iso->add_point(x,y, i, j, visible);

	if (info.close_on_bound)
	{
		REAL fill_level = get_fill_level(level, side, i, j, info);
		iso->set_fill_level(fill_level);
	}

	// find second point
	curr_side = get_next_rib(level, side, i, j, vals, info, closed, need_add, iso, rib_info);
	calc_point(level, curr_side, i, j, vals, info, x, y, visible);
	iso->add_point(x,y,i,j,visible);

	// find the rest
	while ( !( rib_info.first_i == i && rib_info.first_j == j && curr_side == side) )
	{
		short prev_side = curr_side;
		size_t prev_i = i, prev_j = j;
		curr_side = get_next_rib(level, curr_side, i, j, vals, info, closed, need_add, iso, rib_info);
		if (!need_add)
			break;

		if (curr_side == SHRT_MAX) {
			delete iso;
			return NULL;
		}

		calc_point(level, curr_side, i, j, vals, info, x, y, visible);
 		iso->add_point(x,y,i,j,visible);
		if (closed == false) {
			// BOTTOM
			if ( ((curr_side == SIDE_LEFT) || (curr_side == SIDE_RIGHT)) && (j == 0))
			{
				if (prev_side == SIDE_TOP)
				{
					size_t pos = three2one(prev_i, prev_j, level_number, info.nn, info.mm, info.levels->size());
					info.checks->set_false(pos);
					continue;
				}
			}
			// LEFT
			if ( ((curr_side == SIDE_TOP) || (curr_side == SIDE_BOTTOM)) && (i == 0))
			{
				if (prev_side == SIDE_RIGHT)
				{
					size_t pos = three2one(prev_i, prev_j, level_number, info.nn, info.mm, info.levels->size());
					info.checks->set_false(pos);
					continue;
				}
			}
			// TOP
			if ( ((curr_side == SIDE_LEFT) || (curr_side == SIDE_RIGHT)) && (j == info.mm-1))
			{
				if (prev_side == SIDE_BOTTOM)
				{
					size_t pos = three2one(prev_i, prev_j, level_number, info.nn, info.mm, info.levels->size());
					info.checks->set_false(pos);
					continue;
				}
			}
			// RIGHT
			if ( ((curr_side == SIDE_TOP) || (curr_side == SIDE_BOTTOM)) && (i == info.nn-1))
			{
				if (prev_side == SIDE_LEFT)
				{
					size_t pos = three2one(prev_i, prev_j, level_number, info.nn, info.mm, info.levels->size());
					info.checks->set_false(pos);
					continue;
				}
			}
		}
	}

	update_vals(vals, rib_info.first_i, rib_info.first_j, info);

	return iso;
};

fiso * trace_bound_rect(trace_info & info)
{
	REAL val = (*(info.data))(0);
        fiso * iso = NULL;
	REAL level;
	size_t level_number;
	vec::iterator it;

	if (val == info.uval)
		goto ret_bound_iso_null;

	it = std::lower_bound(info.levels->begin(), info.levels->end(), val);
	if (it == info.levels->end())
		goto ret_bound_iso_null;
	
	level = *it;
	level_number = it - info.levels->begin();
        iso = new fiso(level, UINT_MAX, info.levels->size(), info.checks, info.nn, info.mm);
	iso->set_fill_level(val);

	add_bottom_edge(iso, 0, info.nn-1, info);
	add_right_edge(iso, 0, info.mm-1, info);
	add_top_edge(iso, info.nn-1, 0, info);
	add_left_edge(iso, info.mm-1, 0, info);
	
ret_bound_iso_null:
	return iso;
};

bool add_isoline(fiso * iso, std::vector<fiso *> * isos)
{
	if (isos->size() > 0)
	{
		fiso * prev_iso = (*isos)[ isos->size() - 1 ];
		if (prev_iso->get_level() == iso->get_level())
		if (prev_iso->size() == iso->size())
		{
			if (prev_iso->get_checksum() == iso->get_checksum()) // isolines are the same
			{
				delete prev_iso;
				(*isos)[ isos->size() - 1 ] = iso;
				return true;
			}
		}
	}
	if (iso->size() > 0)
	{
		isos->push_back(iso);
		return true;
	}
	else
	{
		delete iso;
		return false;
	}
};

std::vector<fiso *> * trace_isos(vec * levels,
				 vec * x_coords,
				 vec * y_coords,
				 extvec * data,
				 size_t nn, size_t mm,
				 REAL uval,
				 bool close_on_bound)
{
	size_t pos;
	size_t i,j; // for navigating inside matrix
	size_t l; // for levels
	REAL level; // current level;
	bool swap_order;

	REAL added_level = (*levels)(levels->size()-1) + FLT_MAX/2.;
	levels->push_back(added_level);
	size_t l_cnt = levels->size();

        bitvec * checks = create_bitvec( l_cnt*nn*mm );
	checks->init_false();
	std::vector<fiso *> * isos = new std::vector<fiso *>();
	vec * bugged_levels = create_vec(*levels);

	trace_info info;
	info.levels = levels;
	info.x_coords = x_coords;
	info.y_coords = y_coords;
	info.data = data;
	info.nn = nn;
	info.mm = mm;
	info.uval = FLT_MAX;
	info.checks = checks;
	info.close_on_bound = close_on_bound;

	for (pos = 0; pos < bugged_levels->size(); pos++)
	{
		REAL lev = (*bugged_levels)(pos);
		REAL bugged_level = bug_value(lev);
		(*bugged_levels)(pos) = bugged_level;
	}

	vec::iterator it;
	for (pos = 0; pos < nn*mm; pos++)
	{
		REAL val = (*data)(pos);
		if (val == uval)
		{
			if (uval != FLT_MAX)
				(*data)(pos) = FLT_MAX;
			continue;
		}
		it = std::lower_bound(levels->begin(), levels->end(), val);
		if (it != levels->end())
		{
			if (*it == val)
			{
				int dpos = it-levels->begin();
				REAL bugged_value = (*bugged_levels)(it-levels->begin());
				(*data)(pos) = bugged_value;
			}
		}
	}

	bugged_levels->release();
	bugged_levels = NULL;

	uval = FLT_MAX;
		
	//
	//        val2   val3
	//          o-----o
	//	    |\   /|
	//          | \ / |
	//          |  o val4
	//          | / \ |
	//          |/   \|
	//          o-----o
	//         val0   val1
	//
	REAL vals[4];

	if (close_on_bound == true) {
		fiso * iso = trace_bound_rect(info);
		if (iso) {
			add_isoline(iso, isos);
		}
	}
	
	// trace isolines starting from bounds
        
	// bottom
	j = 0;
	for (i = 0; i < nn-1; i++) 
	{
		update_vals(vals, i, j, info);
		
		if ((vals[0] == uval) && (vals[1] == uval))
			continue;

		swap_order = cmp_vals(vals[0], vals[1], uval);
		if (swap_order) {
			for (l = l_cnt-1; l >= 0; l--) {
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) {
					if (l == 0)
						break;
					continue;
				}
				level = (*levels)(l);
				if (check_level_intersection(vals[0], vals[1], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_BOTTOM, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
				if (l == 0)
					break;
			}
		} else {
			for (l = 0; l < l_cnt; l++) {
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) 
					continue;
				level = (*levels)(l);
				if (check_level_intersection(vals[0], vals[1], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_BOTTOM, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
			}
		}
	}

	// left
	///*
	i = 0;
	for (j = 0; j < mm-1; j++)
	{
		update_vals(vals, i, j, info);

		if ((vals[0] == uval) && (vals[2] == uval))
			continue;

		swap_order = cmp_vals(vals[0], vals[2], uval);
		if (swap_order) {
			for (l = l_cnt-1; l >= 0; l--) {
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) {
					if (l == 0)
						break;
					continue;
				}
				level = (*levels)(l);
				if (check_level_intersection(vals[0], vals[2], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_LEFT, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
				if (l == 0)
					break;
			}
		} else {
			for (l = 0; l < l_cnt; l++) {
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) 
					continue;
				level = (*levels)(l);
				if (check_level_intersection(vals[0], vals[2], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_LEFT, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
			}
		}
	}
	//*/
	
	// top
	///*
	j = mm-2;
	for (i = 0; i < nn-1; i++) 
	{
		update_vals(vals, i, j, info);
		
		if ((vals[2] == uval) && (vals[3] == uval))
			continue;

		swap_order = cmp_vals(vals[2], vals[3], uval);
		if (swap_order) {
			for (l = l_cnt-1; l >= 0; l--) {
				level = (*levels)(l);
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) {
					if (l == 0)
						break;
					continue;
				}
				if (check_level_intersection(vals[2], vals[3], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_TOP, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
				if (l == 0)
					break;
			}
		} else {
			for (l = 0; l < l_cnt; l++) {
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) 
					continue;
				level = (*levels)(l);
				if (check_level_intersection(vals[2], vals[3], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_TOP, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
			}
		}
	}
	//*/

	// right
	///*
	i = nn-2;
	for (j = 0; j < mm-1; j++)
	{
		update_vals(vals, i, j, info);

		if ((vals[1] == uval) && (vals[3] == uval))
			continue;

		swap_order = cmp_vals(vals[1], vals[3], uval);
		if (swap_order) {
			for (l = l_cnt-1; l >= 0; l--) {
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) {
					if (l == 0)
						break;
					continue;
				}
				level = (*levels)(l);
				if (check_level_intersection(vals[1], vals[3], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_RIGHT, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
				if (l == 0)
					break;
			}
		} else {
			for (l = 0; l < l_cnt; l++) {
				pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
				if ( info.checks->get(pos) == true ) 
					continue;
				level = (*levels)(l);
				if (check_level_intersection(vals[1], vals[3], level, uval))
				{
					fiso * iso = trace_isoline(level, SIDE_RIGHT, i, j, vals, info, false);
					add_isoline(iso, isos);
				}
			}
		}
	}
	//*/
	
	///*
	for (j = 1; j <= mm-2; j++)
	{
		for (i = 1; i <= nn-2; i++)
		{
			update_vals(vals, i, j, info);

			bool check_right = (i != nn-2);
						
			if (check_right)
			{
				if ((vals[1] != uval) || (vals[3] != uval))
				{
					swap_order = cmp_vals(vals[1], vals[3], uval);
					if (swap_order) {
						for (l = l_cnt-1; l >= 0; l--) {
							pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
							if ( info.checks->get(pos) == true ) {
								if (l == 0)
									break;
								continue;
							}
							level = (*levels)(l);
							if (check_level_intersection(vals[1], vals[3], level, uval))
							{
								fiso * iso = trace_isoline(level, SIDE_RIGHT, i, j, vals, info, true);
								add_isoline(iso, isos);
							}
							if (l == 0)
								break;
						}
					} else {
						for (l = 0; l < l_cnt; l++) {
							pos = three2one(i, j, l, info.nn, info.mm, l_cnt);
							if ( info.checks->get(pos) == true ) 
								continue;
							level = (*levels)(l);
							if (check_level_intersection(vals[1], vals[3], level, uval))
							{
								fiso * iso = trace_isoline(level, SIDE_RIGHT, i, j, vals, info, true);
								add_isoline(iso, isos);
							}
						}
					}
				}
			}
			
		}
	}
	//*/
	checks->release();
	return isos;
}

}; // namespace surfit



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

#include "globe_ie.h"

#include "datafile.h"
#include "fileio.h"
#include "findfile.h"
#include "interp.h"

#include "dem.h"
#include "dem_internal.h"
#include "dem_tcl.h"
#include "points.h"
#include "pnts_internal.h"
#include "surf_internal.h"
#include "mask_internal.h"
#include "mask.h"
#include "grid.h"
#include "grid_internal.h"
#include "grid_line.h"
#include "variables_internal.h"
#include "variables_tcl.h"
#include "free_elements.h"
#include "surf.h"
#include "boolvec.h"
#include "strvec.h"
#include "intvec.h"
#include "vec.h"

#include "grid_user.h"

#include <float.h>
#include <algorithm>

namespace surfit {

struct vec_oper
{
	virtual REAL do_oper(d_dem * dem) = 0;
};

struct match_dem_vec
{
	match_dem_vec(const char * ipos, vec_oper * ioper) : oper(ioper), pos(ipos), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_vec();
			res->push_back( oper->do_oper(dem) );
		}
	}
	const char * pos;
	vec * res;
	vec_oper * oper;
};

struct bool_oper
{
	virtual bool do_oper(d_dem * dem) = 0;
};

struct match_dem_bool
{
	match_dem_bool(const char * ipos, bool_oper * ioper) : oper(ioper), pos(ipos), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(dem) );
		}
	}
	const char * pos;
	boolvec * res;
	bool_oper * oper;
};

boolvec * dem_load(const char * filename, const char * demname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname != NULL) {
		d_dem * d = _dem_load(fname, demname);
		if (d) {
			globe_dems->push_back(d);
			res->push_back(true);
		} else
			res->push_back(false);
		fname = find_next();
	}

	return res;
};

struct match_dem_save
{
	match_dem_save(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _dem_save(dem, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * dem_save(const char * filename, const char * pos) 
{
	match_dem_save qq(filename, pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

boolvec * dem_load_dtm(const char * hdr_filename, const char * name, const char * bin_filename) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(hdr_filename);

	while (fname != NULL) {
		d_dem * d = _dem_load_dtm(fname, bin_filename);
		if (d) {
			if (name)
				d->setName(name);
			globe_dems->push_back(d);
			res->push_back(true);
		} else
			res->push_back(false);
		fname = find_next();
	};

	find_close();
	return res;
};

boolvec * dem_load_hgt_zip(const char * hgt_zip_filename, const char * dem_name) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(hgt_zip_filename);

	while (fname != NULL) {
		
		d_dem * d = _dem_load_hgt_zip(fname);
		if (d) {
			if (dem_name)
				d->setName(dem_name);
			globe_dems->push_back(d);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();

		if (stop_execution)
			break;
		
	}

	find_close();
	return res;
};

boolvec *  dem_load_hgt(const char * hgt_filename, const char * dem_name) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(hgt_filename);

	while (fname != NULL) {
		d_dem * d = _dem_load_hgt(fname);
		if (d) {
			if (dem_name)
				d->setName(dem_name);
			globe_dems->push_back(d);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();

		if (stop_execution)
			break;
	}
	
	find_close();
	return res;
};

boolvec * dem_load_globe(const char * filename, const char * dem_name) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname != NULL) {
		d_dem * d = _dem_load_globe(fname);
		if (d) {
			if (dem_name)
				d->setName(dem_name);
			globe_dems->push_back(d);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();

		if (stop_execution)
			break;
	}

	find_close();
	return res;
};

struct match_dem_save_dtm
{
	match_dem_save_dtm(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _dem_save_dtm(dem, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * dem_save_dtm(const char * filename, const char * pos) 
{
	match_dem_save_dtm qq(filename, pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_resid2
{
	match_dem_resid2(const char * ifilename, d_dem * idem, const char * ipnts_pos) 
		: filename(ifilename), dem(idem), pnts_pos(ipnts_pos), res(NULL) {};
	void operator()(d_points * pnts) 
	{
		if ( StringMatch(pnts_pos, pnts->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();

			res->push_back( _dem_resid(dem, pnts, filename) );
		}
	}
	const char * filename;
	d_dem * dem;
	const char * pnts_pos;
	boolvec * res;
};

struct match_dem_resid
{
	match_dem_resid(const char * ifilename, const char * idem_pos, const char * ipnts_pos) 
		: filename(ifilename), dem_pos(idem_pos), pnts_pos(ipnts_pos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(dem_pos, dem->getName()) )
		{
			match_dem_resid2 qq(filename, dem, pnts_pos);
			qq = std::for_each(surfit_pnts->begin(), surfit_pnts->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * filename;
	const char * dem_pos;
	const char * pnts_pos;
	boolvec * res;
};

boolvec * dem_resid(const char * filename, const char * dem_pos, const char * pnts_pos) 
{
	match_dem_resid qq(filename, dem_pos, pnts_pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct vec_oper_minz : vec_oper
{
	virtual REAL do_oper(d_dem * dem) 
	{
		REAL minZ, maxZ;
		dem->getMinMaxZ(minZ, maxZ);
		return minZ;
	}
};

vec * dem_minz(const char * pos) 
{
	vec_oper_minz oper;
	match_dem_vec qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct vec_oper_maxz : vec_oper
{
	virtual REAL do_oper(d_dem * dem) 
	{
		REAL minZ, maxZ;
		dem->getMinMaxZ(minZ, maxZ);
		return maxZ;
	}
};

vec * dem_maxz(const char * pos) 
{
	vec_oper_maxz oper;
	match_dem_vec qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_save_grd
{
	match_dem_save_grd(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _dem_save_grd(dem, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * dem_save_grd(const char * filename, const char * pos) 
{
	match_dem_save_grd qq(filename, pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

boolvec * dem_load_grd(const char * filename, const char * demname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname != NULL) {
		d_dem * d = _dem_load_grd(fname, demname);
		if (d) {
			if (demname)
				d->setName(demname);
			globe_dems->push_back(d);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();

		if (stop_execution)
			break;
	}
	
	find_close();
	return res;
};

struct match_dem_save_xyz
{
	match_dem_save_xyz(const char * ifilename, const char * ipos) : filename(ifilename), pos(ipos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _dem_save_xyz(dem, filename) );
		}
	}
	const char * filename;
	const char * pos;
	boolvec * res;
};

boolvec * dem_save_xyz(const char * filename, const char * pos) 
{
	match_dem_save_xyz qq(filename, pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_getCountX
{
	match_dem_getCountX(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( dem->getCountX() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * dem_getCountX(const char * pos) 
{
	match_dem_getCountX qq(pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_getCountY
{
	match_dem_getCountY(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( dem->getCountY() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * dem_getCountY(const char * pos) 
{
	match_dem_getCountY qq(pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct vec_oper_stepx : vec_oper
{
	virtual REAL do_oper(d_dem * dem) 
	{
		return dem->getStepX();
	}
};

vec * dem_getStepX(const char * pos) 
{
	vec_oper_stepx oper;
	match_dem_vec qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct vec_oper_stepy : vec_oper
{
	virtual REAL do_oper(d_dem * dem) 
	{
		return dem->getStepY();
	}
};

vec * dem_getStepY(const char * pos) 
{
	vec_oper_stepy oper;
	match_dem_vec qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct vec_oper_getValue : public vec_oper
{
	vec_oper_getValue(REAL ix, REAL iy) : x(ix), y(iy) {};
	virtual REAL do_oper(d_dem * dem) 
	{
		return dem->getValue(x,y);
	}
	REAL x,y;
};

vec * dem_getValue(REAL x, REAL y, const char * pos) 
{
	vec_oper_getValue oper(x,y);
	match_dem_vec qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_dem 
{
	virtual bool do_oper(d_dem * dem1, d_dem * dem2) = 0;
};

struct match_oper_dem2
{
	match_oper_dem2(d_dem * idem1, const char * ipos2, bool_oper_dem * ioper) : oper(ioper), dem1(idem1), pos2(ipos2), res(NULL) {};
	void operator()(d_dem * dem2)
	{
		if ( StringMatch(pos2, dem2->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(dem1, dem2) );
		}
	}
	d_dem * dem1;
	const char * pos2;
	boolvec * res;
	bool_oper_dem * oper;
};

struct match_oper_dem
{
	match_oper_dem(const char * ipos1, const char * ipos2, bool_oper_dem * ioper) : oper(ioper), pos1(ipos1), pos2(ipos2), res(NULL) {};
	void operator()(d_dem * dem1)
	{
		if ( StringMatch(pos1, dem1->getName()) )
		{
			match_oper_dem2 qq(dem1, pos2, oper);
			qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
			if (res == NULL)
				res = create_boolvec();
			res->push_back(qq.res);
		}
	}
	const char * pos1;
	const char * pos2;
	boolvec * res;
	bool_oper_dem * oper;
};

struct bool_oper_dem_plus : public bool_oper_dem
{
	virtual bool do_oper(d_dem * dem1, d_dem * dem2)
	{	
		writelog(LOG_MESSAGE,"calculating dem_plus \"%s\" \"%s\"", dem1->getName(), dem2->getName());
		if (!dem1->compare_grid(dem2))	{
			writelog(LOG_WARNING,"dem_plus : different grids");
			return false;
		}
		dem1->plus(dem2);
		return true;
	}
};

boolvec * dem_plus(const char * pos1, const char * pos2) 
{
	bool_oper_dem_plus oper;
	match_oper_dem qq(pos1, pos2, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_dem_minus : public bool_oper_dem
{
	virtual bool do_oper(d_dem * dem1, d_dem * dem2)
	{	
		writelog(LOG_MESSAGE,"calculating dem_minus \"%s\" \"%s\"", dem1->getName(), dem2->getName());
		if (!dem1->compare_grid(dem2))	{
			writelog(LOG_WARNING,"dem_minus : different grids");
			return false;
		}
		dem1->minus(dem2);
		return true;
	}
};

boolvec * dem_minus(const char * pos1, const char * pos2) 
{
	bool_oper_dem_minus oper;
	match_oper_dem qq(pos1, pos2, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_dem_mult : public bool_oper_dem
{
	virtual bool do_oper(d_dem * dem1, d_dem * dem2)
	{	
		writelog(LOG_MESSAGE,"calculating dem_mult \"%s\" \"%s\"", dem1->getName(), dem2->getName());
		if (!dem1->compare_grid(dem2))	{
			writelog(LOG_WARNING,"dem_mult : different grids");
			return false;
		}
		dem1->mult(dem2);
		return true;
	}
};

boolvec * dem_mult(const char * pos1, const char * pos2) 
{
	bool_oper_dem_mult oper;
	match_oper_dem qq(pos1, pos2, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_dem_div : public bool_oper_dem
{
	virtual bool do_oper(d_dem * dem1, d_dem * dem2)
	{	
		writelog(LOG_MESSAGE,"calculating dem_div \"%s\" \"%s\"", dem1->getName(), dem2->getName());
		if (!dem1->compare_grid(dem2))	{
			writelog(LOG_WARNING,"dem_div : different grids");
			return false;
		}
		dem1->div(dem2);
		return true;
	}
};

boolvec * dem_div(const char * pos1, const char * pos2) 
{
	bool_oper_dem_div oper;
	match_oper_dem qq(pos1, pos2, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_dem_set : public bool_oper_dem
{
	virtual bool do_oper(d_dem * dem1, d_dem * dem2)
	{	
		writelog(LOG_MESSAGE,"calculating dem_set \"%s\" \"%s\"", dem1->getName(), dem2->getName());
		if (!dem1->compare_grid(dem2))	{
			writelog(LOG_WARNING,"dem_set : different grids");
			return false;
		}
		dem1->set(dem2);
		return true;
	}
};

boolvec * dem_set(const char * pos1, const char * pos2) 
{
	bool_oper_dem_set oper;
	match_oper_dem qq(pos1, pos2, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_plus_real : bool_oper
{
	bool_oper_plus_real(REAL ival) : val(ival) {};
	virtual bool do_oper(d_dem * dem) 
	{
		writelog(LOG_MESSAGE,"calculating dem_plus_real for dem \"%s\" and val=%g",dem->getName(),val);
		dem->plus( (short int) val );
		return true;
	}
	REAL val;
};

boolvec * dem_plus_real(REAL val, const char * pos) 
{
	bool_oper_plus_real oper(val);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
}

struct bool_oper_minus_real : bool_oper
{
	bool_oper_minus_real(REAL ival) : val(ival) {};
	virtual bool do_oper(d_dem * dem) 
	{
		writelog(LOG_MESSAGE,"calculating dem_minus_real for dem \"%s\" and val=%g",dem->getName(),val);
		dem->minus( (short int) val );
		return true;
	}
	REAL val;
};

boolvec * dem_minus_real(REAL val, const char * pos) 
{
	bool_oper_minus_real oper(val);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
}

struct bool_oper_mult_real : bool_oper
{
	bool_oper_mult_real(REAL ival) : val(ival) {};
	virtual bool do_oper(d_dem * dem) 
	{
		writelog(LOG_MESSAGE,"calculating dem_mult_real for dem \"%s\" and val=%g",dem->getName(),val);
		dem->mult( (short int) val );
		return true;
	}
	REAL val;
};

boolvec * dem_mult_real(REAL val, const char * pos) 
{
	bool_oper_mult_real oper(val);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
}

struct bool_oper_div_real : bool_oper
{
	bool_oper_div_real(REAL ival) : val(ival) {};
	virtual bool do_oper(d_dem * dem) 
	{
		writelog(LOG_MESSAGE,"calculating dem_div_real for dem \"%s\" and val=%g",dem->getName(),val);
		dem->div( (short int) val );
		return true;
	}
	REAL val;
};

boolvec * dem_div_real(REAL val, const char * pos) 
{
	bool_oper_div_real oper(val);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
}

struct bool_oper_set_real : bool_oper
{
	bool_oper_set_real(REAL ival) : val(ival) {};
	virtual bool do_oper(d_dem * dem) 
	{
		writelog(LOG_MESSAGE,"calculating dem_set_real for dem \"%s\" and val=%g",dem->getName(),val);
		dem->set( (short int) val );
		return true;
	}
	REAL val;
};

boolvec * dem_set_real(REAL val, const char * pos) 
{
	bool_oper_set_real oper(val);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
}

struct bool_oper_dem_undef : public bool_oper
{
	bool_oper_dem_undef(REAL ival) : val(ival) {};
	virtual bool do_oper(d_dem * dem)
	{
		dem->undef_value = (short int)val;
		return true;
	}
	REAL val;
};

boolvec * dem_undef(REAL new_undef_value, const char * pos) 
{
	bool_oper_dem_undef oper(new_undef_value);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct vec_oper_D1 : vec_oper
{
	virtual REAL do_oper(d_dem * dem) 
	{
		writelog(LOG_MESSAGE,"calculating dem_D1 for dem \"%s\"", dem->getName());
		return _dem_D1(dem);
	}
};

vec * dem_D1(const char * pos) 
{
	vec_oper_D1 oper;
	match_dem_vec qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct vec_oper_D2 : vec_oper
{
	virtual REAL do_oper(d_dem * dem) 
	{
		writelog(LOG_MESSAGE,"calculating dem_D2 for dem \"%s\"", dem->getName());
		return _dem_D2(dem);
	}
};

vec * dem_D2(const char * pos) 
{
	vec_oper_D2 oper;
	match_dem_vec qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_project : public bool_oper
{
	bool_oper_project(const char * inewname) : newname(inewname) {};
	virtual bool do_oper(d_dem * dem)
	{
		if (!_grid_check())
			return false;

		if (!(dem->grd->operator == (surfit_grid))) {
			d_dem * res_dem2 = _dem_project(dem, surfit_grid);
			if (newname)
				res_dem2->setName(newname);
			if (res_dem2) {
				globe_dems->push_back(res_dem2);
				return true;
			}
			return false;
		}
		return true;
	}
	const char * newname;
};

boolvec * dem_project(const char * newname, const char * pos) 
{
	bool_oper_project oper(newname);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_gradient : public bool_oper
{
	bool_oper_gradient(const char * inewname) : newname(inewname) {};
	virtual bool do_oper(d_dem * dem)
	{
		d_dem * res = _dem_gradient(dem);
		if (res) {
			if (newname)
				res->setName(newname);
			globe_dems->push_back(res);
			return true;
		}
		return false;
	}
	const char * newname;
};

boolvec * dem_gradient(const char * newname, const char * pos) 
{
	bool_oper_gradient oper(newname);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_to_pnts : public bool_oper
{
	virtual bool do_oper(d_dem * dem)
	{
		writelog(LOG_MESSAGE,"converting dem \"%s\" to points", dem->getName());

		d_points * pnts = _dem_to_points(dem);
		if (!pnts)
			return false;

		pnts->setName(dem->getName());
		_surfit_pnts_add(pnts);
		return true;
	}
};

boolvec * dem_to_pnts(const char * pos) 
{
	bool_oper_to_pnts oper;
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_to_surf : public bool_oper
{
	virtual bool do_oper(d_dem * dem)
	{
		writelog(LOG_MESSAGE,"converting dem \"%s\" to surface", dem->getName());

		d_surf * srf = _dem_to_surf(dem);
		if (!srf)
			return false;

		srf->setName(dem->getName());

		_add_surfit_surfs(srf);
		return true;
	}
};

boolvec * dem_to_surf(const char * pos)
{
	bool_oper_to_surf oper;
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_to_mask : public bool_oper
{
	bool_oper_to_mask(REAL ifrom, REAL ito) : true_from(ifrom), true_to(ito) {};
	virtual bool do_oper(d_dem * dem)
	{
		writelog(LOG_MESSAGE,"converting dem \"%s\" to mask", dem->getName());

		d_mask * msk = _dem_to_mask(dem, (short int)true_from, (short int)true_to);
		if (!msk)
			return false;

		msk->setName(dem->getName());

		_surfit_mask_add(msk);
		return true;
	}
	REAL true_from, true_to;
};

boolvec * dem_to_mask(short true_from, short true_to, const char * pos)
{
	bool_oper_to_mask oper(true_from, true_to);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct bool_oper_setName : bool_oper
{
	bool_oper_setName(const char * inewname) : newname(inewname) {};
	virtual bool do_oper(d_dem * dem)
	{
		dem->setName(newname);
		return true;
	}
	const char * newname;
};

boolvec * dem_setName(const char * new_name, const char * pos) 
{
	bool_oper_setName oper(new_name);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_getName
{
	match_dem_getName(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_strvec();
			res->push_back( dem->getName() ) ;
		}
	}
	const char * pos;
	strvec * res;
};

strvec * dem_getName(const char * pos) 
{
	match_dem_getName qq(pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

const char * dem_getNameAt(int pos)
{
	if ((size_t)pos > globe_dems->size())
		return NULL;
	return (*globe_dems)[pos]->getName();
};

struct match_dem_getId
{
	match_dem_getId(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( dem->getId() ) ;
		}
	}
	const char * pos;
	intvec * res;
};

intvec * dem_getId(const char * pos) 
{
	match_dem_getId qq(pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

bool dem_delall() {

	if (globe_dems == NULL)
		return false;

	if (globe_dems->size() == 0) {
		return false;
	}
	
	release_elements(globe_dems->begin(), globe_dems->end());
	globe_dems->resize(0);

	return true;
};

void dem_del(const char * pos) 
{
	if (globe_dems->size() == 0)
		return;
	size_t i;
	for (i = globe_dems->size()-1; i >= 0; i--)
	{
		d_dem * dem = (*globe_dems)[i];
		if ( StringMatch(pos, dem->getName()) == true )
		{
			writelog(LOG_MESSAGE,"removing DEM \"%s\" from memory", dem->getName());
			dem->release();
			globe_dems->erase(globe_dems->begin()+i);
		}
		if (i == 0)
			break;
	}
};

int dem_size() {
	return globe_dems->size();
};

void dems_info() {
	if (globe_dems->size() > 0) {
		size_t dem_cnt;
		for (dem_cnt = 0; dem_cnt < globe_dems->size(); dem_cnt++) {
			d_dem * a_srf = *(globe_dems->begin()+dem_cnt);
			if (a_srf) {
				_dem_info(a_srf);
			}
		}
	}
};

//
//
// wavelets section
//
//

struct match_dem_decomp
{
	match_dem_decomp(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _dem_decomp(dem) );
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * dem_decomp(const char * pos) 
{
	match_dem_decomp q(pos);
	q = std::for_each(globe_dems->begin(), globe_dems->end(), q);
	return q.res;
};

struct bool_oper_auto_decomp : public bool_oper
{
	bool_oper_auto_decomp(REAL ieps) : eps(ieps) {};
	virtual bool do_oper(d_dem * dem)
	{
		return _dem_auto_decomp(dem, eps);
	}
	REAL eps;
};

boolvec * dem_auto_decomp(REAL eps, const char * pos) 
{
	bool_oper_auto_decomp oper(eps);
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_recons
{
	match_dem_recons(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem) 
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( _dem_recons(dem) );
		}
	}
	const char * pos;
	boolvec * res;
};

boolvec * dem_recons(const char * pos) 
{
	match_dem_recons q(pos);
	q = std::for_each(globe_dems->begin(), globe_dems->end(), q);
	return q.res;
};

struct bool_oper_full_recons : public bool_oper
{
	virtual bool do_oper(d_dem * dem)
	{
		return _dem_full_recons(dem);
	}
};

boolvec * dem_full_recons(const char * pos) 
{
	bool_oper_full_recons oper;
	match_dem_bool qq(pos, &oper);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

struct match_dem_get_details_level
{
	match_dem_get_details_level(const char * ipos) : pos(ipos), res(NULL) {};
	void operator()(d_dem * dem)
	{
		if ( StringMatch(pos, dem->getName()) )
		{
			if (res == NULL)
				res = create_intvec();
			res->push_back( dem->coeffs_store->size() );
		}
	}
	const char * pos;
	intvec * res;
};

intvec * dem_get_details_level(const char * pos) 
{
	match_dem_get_details_level qq(pos);
	qq = std::for_each(globe_dems->begin(), globe_dems->end(), qq);
	return qq.res;
};

}; // namespace surfit;


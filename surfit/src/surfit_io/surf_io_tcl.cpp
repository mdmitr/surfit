
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

#include "surfit_io_ie.h"

#include "boolvec.h"
#include "findfile.h"

#include "surf.h"
#include "surf_io.h"
#include "surf_io_tcl.h"

#include <algorithm>

namespace surfit {

boolvec * surf_load_grd(const char * filename, const char * surfname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_surf * srf = _surf_load_grd(fname, surfname);
		if (srf) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();

	};
	find_close();
	return res;
};

boolvec * surf_load_gmt(const char * filename, const char * surfname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_surf * srf = _surf_load_gmt(fname, surfname);
		if (srf) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		}
		else
			res->push_back(false);

		fname = find_next();

	};
	find_close();
	return res;
};

boolvec * surf_load_grass(const char * filename, const char * surfname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_surf * srf = _surf_load_grass(fname, surfname);
		if (srf) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();

	};
	find_close();
	return res;
};

boolvec * surf_load_arcgis(const char * filename, const char * surfname) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_surf * srf = _surf_load_arcgis(fname, surfname);
		if (srf) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();
	};

	find_close();
	return res;
};

boolvec * surf_load_xyz(const char * filename, const char * surfname, bool force) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_surf * srf = _surf_load_xyz(fname, surfname, force);
		if (srf) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();
	};

	find_close();
	return res;
};

boolvec * surf_load_jpg(const char * filename, const char * surfname,
		   REAL minz, REAL maxz, REAL startX, REAL startY, REAL stepX, REAL stepY) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_surf * srf = _surf_load_jpg(fname, surfname,
			minz, maxz, startX, startY, stepX, stepY);
		if (srf) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();
	};

	find_close();
	return res;
};

boolvec * surf_load_bmp(const char * filename, const char * surfname,
		   REAL minz, REAL maxz, REAL startX, REAL startY, REAL stepX, REAL stepY) 
{
	boolvec * res = create_boolvec();
	const char * fname = find_first(filename);

	while (fname) {
		d_surf * srf = _surf_load_bmp(fname, surfname,
			minz, maxz, startX, startY, stepX, stepY);
		if (srf) {
			surfit_surfs->push_back(srf);
			res->push_back(true);
		} else
			res->push_back(false);

		fname = find_next();
	};

	find_close();
	return res;
};

struct save_oper
{
	virtual bool do_oper(const char * filename, d_surf * surf) = 0;
};

struct match_surf_save
{
	match_surf_save(const char * ifilename, const char * ipos, save_oper * ioper) 
		: filename(ifilename), pos(ipos), oper(ioper), res(NULL) {};
	void operator()(d_surf * surf)
	{
		if ( StringMatch(pos, surf->getName()) )
		{
			if (res == NULL)
				res = create_boolvec();
			res->push_back( oper->do_oper(filename, surf) );
		}
	}
	const char * filename;
	const char * pos;
	save_oper * oper;
	boolvec * res;
};

struct save_oper_grd : public save_oper
{
	save_oper_grd(int iformat) : format(iformat) {};
	virtual bool do_oper(const char * filename, d_surf * srf)
	{
		if (!srf)
			return false;
		bool res = false;
		switch (format) {
		case 0:
			res = _surf_save_grd(srf, filename);
			break;
		case 1:
			res = _surf_save_grd_bin(srf, filename);
			break;
		case 2:
			res = _surf_save_grd_bin7(srf, filename);
			break;
		};
		return res;
	};
	int format;
};

boolvec * surf_save_grd(const char * filename, const char * pos, int format) 
{
	save_oper_grd oper(format);
	match_surf_save qq(filename, pos, &oper);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct save_oper_gmt : public save_oper
{
	virtual bool do_oper(const char * filename, d_surf * srf)
	{
		if (!srf)
			return false;
		return _surf_save_gmt(srf, filename);
	};
};

boolvec * surf_save_gmt(const char * filename, const char * pos) 
{
	save_oper_gmt oper;
	match_surf_save qq(filename, pos, &oper);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct save_oper_grass : public save_oper
{
	virtual bool do_oper(const char * filename, d_surf * srf)
	{
		if (!srf)
			return false;
		return _surf_save_grass(srf, filename);
	};
};

boolvec * surf_save_grass(const char * filename, const char * pos) 
{
	save_oper_grass oper;
	match_surf_save qq(filename, pos, &oper);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct save_oper_arcgis : public save_oper
{
	virtual bool do_oper(const char * filename, d_surf * srf)
	{
		if (!srf)
			return false;
		return _surf_save_arcgis(srf, filename);
	};
};

boolvec * surf_save_arcgis(const char * filename, const char * pos) 
{
	save_oper_arcgis oper;
	match_surf_save qq(filename, pos, &oper);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct save_oper_xyz : public save_oper
{
	virtual bool do_oper(const char * filename, d_surf * srf)
	{
		if (!srf)
			return false;
		return _surf_save_xyz(srf, filename);
	};
};

boolvec * surf_save_xyz(const char * filename, const char * pos) 
{
	save_oper_xyz oper;
	match_surf_save qq(filename, pos, &oper);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct save_oper_jpg : public save_oper
{
	save_oper_jpg(int iquality) : quality(iquality) {};
	virtual bool do_oper(const char * filename, d_surf * srf)
	{
		if (!srf)
			return false;
		return _surf_save_jpg(srf, filename, quality);
	};
	int quality;
};

boolvec * surf_save_jpg(const char * filename, const char * pos, int quality) 
{
	save_oper_jpg oper(quality);
	match_surf_save qq(filename, pos, &oper);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

struct save_oper_bmp : public save_oper
{
	virtual bool do_oper(const char * filename, d_surf * srf)
	{
		if (!srf)
			return false;
		return _surf_save_bmp(srf, filename);
	};
};

boolvec * surf_save_bmp(const char * filename, const char * pos) 
{
	save_oper_bmp oper;
	match_surf_save qq(filename, pos, &oper);
	qq = std::for_each(surfit_surfs->begin(), surfit_surfs->end(), qq);
	return qq.res;
};

}; // namespace surfit;



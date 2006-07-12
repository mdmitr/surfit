
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

#include "surf.h"
#include "surf_io.h"

namespace surfit {

bool surf_load_grd(const char * filename, const char * surfname) {
	d_surf * srf = _surf_load_grd(filename, surfname);
	if (srf) {
		surfit_surfs->push_back(srf);
		return true;
	}
	return false;
};

bool surf_load_gmt(const char * filename, const char * surfname) {
	d_surf * srf = _surf_load_gmt(filename, surfname);
	if (srf) {
		surfit_surfs->push_back(srf);
		return true;
	}
	return false;
};

bool surf_load_grass(const char * filename, const char * surfname) {
	d_surf * srf = _surf_load_grass(filename, surfname);
	if (srf) {
		surfit_surfs->push_back(srf);
		return true;
	}
	return false;
};

bool surf_load_arcgis(const char * filename, const char * surfname) {
	d_surf * srf = _surf_load_arcgis(filename, surfname);
	if (srf) {
		surfit_surfs->push_back(srf);
		return true;
	}
	return false;
};

bool surf_load_jpg(const char * filename, const char * surfname,
		   REAL minz, REAL maxz, REAL startX, REAL startY, REAL stepX, REAL stepY) {
	d_surf * srf = _surf_load_jpg(filename, surfname,
				      minz, maxz, startX, startY, stepX, stepY);
	if (srf) {
		surfit_surfs->push_back(srf);
		return true;
	}
	return false;
};

bool surf_load_bmp(const char * filename, const char * surfname,
		   REAL minz, REAL maxz, REAL startX, REAL startY, REAL stepX, REAL stepY) {
	d_surf * srf = _surf_load_bmp(filename, surfname,
				      minz, maxz, startX, startY, stepX, stepY);
	if (srf) {
		surfit_surfs->push_back(srf);
		return true;
	}
	return false;
};

bool surf_save_grd(const char * filename, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_save_grd(srf, filename);
};

bool surf_save_gmt(const char * filename, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_save_gmt(srf, filename);
};

bool surf_save_grass(const char * filename, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_save_grass(srf, filename);
};

bool surf_save_arcgis(const char * filename, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_save_arcgis(srf, filename);
};

bool surf_save_xyz(const char * filename, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_save_xyz(srf, filename);
};

bool surf_save_jpg(const char * filename, const char * pos, int quality) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_save_jpg(srf, filename, quality);
};

bool surf_save_bmp(const char * filename, const char * pos) {
	d_surf * srf = get_element<d_surf>(pos, surfit_surfs->begin(), surfit_surfs->end());
	if (!srf)
		return false;
	return _surf_save_bmp(srf, filename);
};

}; // namespace surfit;



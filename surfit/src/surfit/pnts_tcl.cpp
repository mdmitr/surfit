
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

#include "surfit_ie.h"

#include "datafile.h"
#include "fileio.h"
#include "vec.h"
#include "rnd.h"
#include "geom_alg.h"

#include <math.h>

#include "points.h"
#include "pnts_internal.h"
#include "pnts_tcl.h"
#include "surf.h"
#include "surf_internal.h"
#include "mask.h"
#include "mask_internal.h"
#include "variables_internal.h"
#include "curv_internal.h"
#include "curv.h"
#include "area.h"
#include "free_elements.h"

namespace surfit {

bool pnts_load(const char * filename, const char * pntsname) {
	d_points * pnts = _pnts_load(filename, pntsname);
	if (pnts) {
		surfit_pnts->push_back(pnts);
		return true;
	}
	return false;
};

bool pnts_add_noise(REAL std, const char * pos) {
	
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	if (pnts->size() == 0)
		return false;

	REAL * ptr;
	for (ptr = pnts->Z->begin(); ptr != pnts->Z->end(); ptr++) {
		*ptr += norm_rand(std);
	}

	return true;
};

REAL pnts_mean(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return FLT_MAX;

	return pnts->mean();
}

REAL pnts_std(REAL mean, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	return pnts->std(mean);
}


bool pnts_save(const char * filename, const char * pos) {
	
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	writelog(LOG_MESSAGE,"Saving points to file %s", filename);

	return _pnts_save(pnts, filename);
};

int pnts_getCount(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return -1;
	return pnts->size();
};

bool pnts_read(const char * filename, const char * pntsname, int col1, int col2, int col3, int col4, const char * delimiter, int skip_lines, int grow_by) {
	d_points * pnts = _pnts_read(filename, pntsname, col1, col2, col3, col4, delimiter, skip_lines, grow_by);
	if (pnts) {
		surfit_pnts->push_back(pnts);
		return true;
	}
	return false;
};

bool pnts_write(const char * filename, const char * delimiter, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	char buf[80];
	strcpy( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "%lf" );
	strcat( buf, delimiter );
	strcat( buf, "\n" );
	return _pnts_write(pnts, filename, buf);
};

bool pnts_filter_by_surf(REAL eps, const char * pnts_pos, const char * surf_pos) {

	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (pnts == NULL)
		return false;

	int old_size = pnts->size();
	if (old_size == 0)
		return false;

	REAL * old_X_ptr = pnts->X->begin();
	REAL * old_Y_ptr = pnts->Y->begin();
	REAL * old_Z_ptr = pnts->Z->begin();

	REAL * new_X_ptr = pnts->X->begin();
	REAL * new_Y_ptr = pnts->Y->begin();
	REAL * new_Z_ptr = pnts->Z->begin();

	REAL z_value;

	for (;old_X_ptr != pnts->X->end(); old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
		z_value = srf->getValue(*old_X_ptr, *old_Y_ptr);
		if ( fabs(z_value - *old_Z_ptr) < eps ) {
			*new_X_ptr = *old_X_ptr;
			*new_Y_ptr = *old_Y_ptr;
			*new_Z_ptr = *old_Z_ptr;
			new_X_ptr++;
			new_Y_ptr++;
			new_Z_ptr++;
		}
	}

	int new_size = new_X_ptr - pnts->X->begin();

	pnts->X->resize(new_size);
	pnts->Y->resize(new_size);
	pnts->Z->resize(new_size);
	
	return true;

};

bool pnts_filter_in_area(const char * pnts_pos, const char * area_pos) {

	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_area * crv = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (crv == NULL)
		return false;
	
	writelog(LOG_MESSAGE,"removing points inside area");

	int old_size = pnts->size();

	REAL * old_X_ptr = pnts->X->begin();
	REAL * old_Y_ptr = pnts->Y->begin();
	REAL * old_Z_ptr = pnts->Z->begin();

	REAL * new_X_ptr = pnts->X->begin();
	REAL * new_Y_ptr = pnts->Y->begin();
	REAL * new_Z_ptr = pnts->Z->begin();

	for (;old_X_ptr != pnts->X->end(); old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
		
		bool in_reg = crv->in_region(*old_X_ptr, *old_Y_ptr);
		if ( in_reg ) {
			*new_X_ptr = *old_X_ptr;
			*new_Y_ptr = *old_Y_ptr;
			*new_Z_ptr = *old_Z_ptr;
			new_X_ptr++;
			new_Y_ptr++;
			new_Z_ptr++;
		}
	}

	int new_size = new_X_ptr - pnts->X->begin();

	pnts->X->resize(new_size);
	pnts->Y->resize(new_size);
	pnts->Z->resize(new_size);
	
	return true;

};

bool pnts_filter_out_area(const char * pnts_pos, const char * area_pos) {

	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_area * crv = get_element<d_area>(area_pos, surfit_areas->begin(), surfit_areas->end());
	if (crv == NULL)
		return false;

	writelog(LOG_MESSAGE,"removing points outside area");

	int old_size = pnts->size();

	REAL * old_X_ptr = pnts->X->begin();
	REAL * old_Y_ptr = pnts->Y->begin();
	REAL * old_Z_ptr = pnts->Z->begin();

	REAL * new_X_ptr = pnts->X->begin();
	REAL * new_Y_ptr = pnts->Y->begin();
	REAL * new_Z_ptr = pnts->Z->begin();

	for (;old_X_ptr != pnts->X->end(); old_X_ptr++, old_Y_ptr++, old_Z_ptr++) {
		
		bool in_reg = crv->in_region(*old_X_ptr, *old_Y_ptr);
		if ( !in_reg ) {
			*new_X_ptr = *old_X_ptr;
			*new_Y_ptr = *old_Y_ptr;
			*new_Z_ptr = *old_Z_ptr;
			new_X_ptr++;
			new_Y_ptr++;
			new_Z_ptr++;
		}
	}

	int new_size = new_X_ptr - pnts->X->begin();

	pnts->X->resize(new_size);
	pnts->Y->resize(new_size);
	pnts->Z->resize(new_size);

	return true;

};

bool pnts_filter_by_mask(const char * pnts_pos, const char * def_pos) {
	
	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_mask * msk = get_element<d_mask>(def_pos, surfit_masks->begin(), surfit_masks->end());
	if (pnts == NULL)
		return false;

	int cnt = pnts->size();
	if (cnt == 0)
		return false;
		
	int i,j;
	REAL x,y;
	bool val;
	j = 0;
	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();

	for (i = 0; i < cnt; i++) {
		x = *(x_ptr + i);
		y = *(y_ptr + i);
		val = msk->getValue(x,y);
		if (val) {
			*(x_ptr + j) = x;
			*(y_ptr + j) = y;
			*(z_ptr + j) = *(z_ptr + i);
			j++;
		}
	}

	pnts->X->resize(j);
	pnts->Y->resize(j);
	pnts->Z->resize(j);
	
	return true;
};

bool pnts_plus(const char * pos1, const char * pos2) {
	d_points * pnts1 = get_element<d_points>(pos1, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts1 == NULL)
		return false;

	d_points * pnts2 = get_element<d_points>(pos2, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts2 == NULL)
		return false;

	return pnts1->plus(pnts2);
};

bool pnts_minus(const char * pos1, const char * pos2) {
	d_points * pnts1 = get_element<d_points>(pos1, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts1 == NULL)
		return false;

	d_points * pnts2 = get_element<d_points>(pos2, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts2 == NULL)
		return false;
	return pnts1->minus(pnts2);
};

bool pnts_mult(const char * pos1, const char * pos2) {
	d_points * pnts1 = get_element<d_points>(pos1, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts1 == NULL)
		return false;

	d_points * pnts2 = get_element<d_points>(pos2, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts2 == NULL)
		return false;
	return pnts1->mult(pnts2);
};

bool pnts_div(const char * pos1, const char * pos2) {
	d_points * pnts1 = get_element<d_points>(pos1, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts1 == NULL)
		return false;

	d_points * pnts2 = get_element<d_points>(pos2, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts2 == NULL)
		return false;
	return pnts1->div(pnts2);
};

bool pnts_set(const char * pos1, const char * pos2) {
	d_points * pnts1 = get_element<d_points>(pos1, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts1 == NULL)
		return false;

	d_points * pnts2 = get_element<d_points>(pos2, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts2 == NULL)
		return false;
	return pnts1->set(pnts2);
};

bool pnts_plus_real(REAL val, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	pnts->plus(val);
	return true;
};

bool pnts_minus_real(REAL val, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	pnts->minus(val);
	return true;
};

bool pnts_mult_real(REAL val, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	pnts->mult(val);
	return true;
};

bool pnts_div_real(REAL val, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	pnts->div(val);
	return true;
};

bool pnts_set_real(REAL val, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	pnts->set(val);
	return true;
};

bool pnts_plus_surf(const char * pos, const char * surf_pos) {

	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	if (pnts->size() == 0)
		return false;

	int i;
	REAL x,y,z, Z;
	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();
	for (i = 0; i < pnts->size(); i++) {
		x = *(x_ptr + i);
		y = *(y_ptr + i);
		z = *(z_ptr + i);
		Z = srf->getValue(x,y);
		if (Z != srf->undef_value) {
			*(z_ptr + i) = z + Z;
		}
	}

	return true;
};

bool pnts_minus_surf(const char * pos, const char * surf_pos) {

	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	if (pnts->size() == 0)
		return false;

	int i;
	REAL x,y,z, Z;
	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();
	for (i = 0; i < pnts->size(); i++) {
		x = *(x_ptr + i);
		y = *(y_ptr + i);
		z = *(z_ptr + i);
		Z = srf->getValue(x,y);
		if (Z != srf->undef_value) {
			*(z_ptr + i) = z - Z;
		}
	}

	return true;
};

bool pnts_mult_surf(const char * pos, const char * surf_pos) {
	
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	if (pnts->size() == 0)
		return false;

	int i;
	REAL x,y,z, Z;
	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();
	for (i = 0; i < pnts->size(); i++) {
		x = *(x_ptr + i);
		y = *(y_ptr + i);
		z = *(z_ptr + i);
		Z = srf->getValue(x,y);
		if (Z != srf->undef_value) {
			*(z_ptr + i) = z * Z;
		}
	}

	return true;
};

bool pnts_div_surf(const char * pos, const char * surf_pos) {

	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	if (pnts->size() == 0)
		return false;

	int i;
	REAL x,y,z, Z;
	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();
	for (i = 0; i < pnts->size(); i++) {
		x = *(x_ptr + i);
		y = *(y_ptr + i);
		z = *(z_ptr + i);
		Z = srf->getValue(x,y);
		if (Z != srf->undef_value) {
			*(z_ptr + i) = z / Z;
			if (Z == 0)
				*(z_ptr + i) = 0;

		}
	}

	return true;
};

bool pnts_set_surf(const char * pos, const char * surf_pos) {

	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	if (pnts->size() == 0)
		return false;

	int i;
	REAL x,y,z, Z;
	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();
	for (i = 0; i < pnts->size(); i++) {
		x = *(x_ptr + i);
		y = *(y_ptr + i);
		z = *(z_ptr + i);
		Z = srf->getValue(x,y);
		if (Z != srf->undef_value) {
			*(z_ptr + i) = Z;
		}
	}

	return true;
};

bool pnts_update_by_surf(const char * pnts_pos, const char * surf_pos) {

	d_points * pnts = get_element<d_points>(pnts_pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;

	d_surf * srf = get_element<d_surf>(surf_pos, surfit_surfs->begin(), surfit_surfs->end());
	if (srf == NULL)
		return false;

	if (pnts->size() == 0)
		return false;

	int i;
	REAL x,y,z;
	REAL * x_ptr = pnts->X->begin();
	REAL * y_ptr = pnts->Y->begin();
	REAL * z_ptr = pnts->Z->begin();
	for (i = 0; i < pnts->size(); i++) {
		x = *(x_ptr + i);
		y = *(y_ptr + i);
		z = srf->getValue(x,y);
		*(z_ptr + i) = z;
	}
	return true;
};

REAL pnts_minx(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	return pnts->minx();
};

REAL pnts_maxx(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	return pnts->maxx();
};

REAL pnts_miny(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	return pnts->miny();
};

REAL pnts_maxy(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	return pnts->maxy();
};

REAL pnts_minz(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	return pnts->minz();
};

REAL pnts_maxz(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	return pnts->maxz();
};

bool pnts_setName(const char * new_name, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	pnts->setName(new_name);
	return true;
};

const char * pnts_getName(const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return "";
	return pnts->getName();
};

bool pnts_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	_points_transform(pnts->X, pnts->Y,
			   shiftX, scaleX, shiftY, scaleY);
	return true;
};

bool pnts_inverse_transform(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	if (pnts->size() == 0)
		return false;
	_inverse_points_transform(pnts, shiftX, scaleX, shiftY, scaleY);
	return true;
};

bool pnts_rotate(REAL centerX, REAL centerY, REAL angle, const char * pos) {
	d_points * pnts = get_element<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == NULL)
		return false;
	if (pnts->size() == 0)
		return false;
	return rotate(centerX, centerY, angle, 
		      pnts->X->begin(), pnts->X->end(),
		      pnts->Y->begin(), pnts->Y->end());
};

bool pnts_delall() {
	if (surfit_pnts->size() == 0) {
		return false;
	}

	release_elements(surfit_pnts->begin(), surfit_pnts->end());
	surfit_pnts->resize(0);
	return true;
};

bool pnts_del(const char * pos) {
	std::vector<d_points *>::iterator pnts = get_iterator<d_points>(pos, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts == surfit_pnts->end())
		return false;
	
	if (*pnts)
		(*pnts)->release();
	surfit_pnts->erase(pnts);
	return true;
};

bool pnts_concat(const char * pos1, const char * pos2) {

	d_points * pnts1 = get_element<d_points>(pos1, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts1 == NULL)
		return false;

	d_points * pnts2 = get_element<d_points>(pos2, surfit_pnts->begin(), surfit_pnts->end());
	if (pnts2 == NULL)
		return false;

	if (pnts2->size() == 0)
		return false;

	int old_cnt = pnts1->size();
	int cnt = old_cnt + pnts2->size();

	if (pnts1->X == NULL)
		pnts1->X = create_vec();
	if (pnts1->Y == NULL)
		pnts1->Y = create_vec();
	if (pnts1->Z == NULL)
		pnts1->Z = create_vec();

	pnts1->X->resize(cnt);
	pnts1->Y->resize(cnt);
	pnts1->Z->resize(cnt);

	REAL * ptr = NULL;

	ptr = pnts1->X->begin() + old_cnt;
	memcpy(ptr, pnts2->X->begin(), pnts2->size()*sizeof(REAL));
	
	ptr = pnts1->Y->begin() + old_cnt;
	memcpy(ptr, pnts2->Y->begin(), pnts2->size()*sizeof(REAL));
	
	ptr = pnts1->Z->begin() + old_cnt;
	memcpy(ptr, pnts2->Z->begin(), pnts2->size()*sizeof(REAL));
	
	return true;
};

int pnts_size() {
	return surfit_pnts->size();
};

void pnts_info() {
	unsigned int pnts_counter;
	for (pnts_counter = 0; pnts_counter < surfit_pnts->size(); pnts_counter++) {
		d_points * pnts = *(surfit_pnts->begin()+pnts_counter);
		_pnts_info(pnts);
		
	}
};

}; // namespace surfit;


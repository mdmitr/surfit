
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

#include "sstuff.h"
#include "real.h"
#include "bitvec.h"
#include "vec.h"
#include "free_elements.h"

#include "surf.h"
#include "surf_internal.h"
#include "grid.h"
#include "grid_internal.h"
#include "grid_line.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "points.h"
#include "curv.h"
#include "curv_internal.h"
#include "mask.h"
#include "grid_line_internal.h"
#include "datafile.h"
#include "area.h"
#include "cntr.h"
#include "cntr_trace.h"
#include "geom_alg.h"
#include "colorscale.h"

#include "sort_alg.h"
#include "stepFunc.h"

#include "grid_line_user.h"
#include "grid_user.h"
#include "triangle.h"

#include "threads.h"

#include "creeps/CreEPS.h"

#include <math.h>
#include <float.h>
#include <errno.h>

namespace surfit {

int calc_ptr(int i, int j, int N);

d_points * _surf_to_pnts(const d_surf * srf) {
	
	if (!srf->coeff) {
		writelog(LOG_ERROR,"convert_surf_to_pnts : wrong surf - no coeffs");
		return NULL;
	}

	size_t size = srf->getCountX()*srf->getCountY();
	vec * Z = create_vec();
	Z->reserve(size);
	vec * X = create_vec();
	X->reserve(size);
	vec * Y = create_vec();
	Y->reserve(size);
	
	size_t i,j;
	REAL x, y, z;
	for (j = 0; j < srf->getCountY(); j++) {
		for (i = 0; i < srf->getCountX(); i++) {
			z = srf->getValueIJ(i,j);
			if (z == srf->undef_value)
				continue;
			srf->getCoordNode(i,j,x,y);
			X->push_back(x);
			Y->push_back(y);
			Z->push_back(z);
		}
	}

	return create_points(X, Y, Z,
			     srf->getName());
};

//
//
// wavelets section
//
//

bool _surf_decomp(d_surf * srf) {
	if (!srf)
		return false;
	
	return srf->decompose();
};

bool _surf_auto_decomp(d_surf * srf, REAL eps) {
	if (!srf)
		return false;

	return srf->auto_decompose(eps);
};

bool _surf_add_noise(d_surf * srf, REAL std) {
	if (!srf)
		return false;

	return srf->add_noise(std);
};

bool _surf_recons(d_surf * srf) {
	if (!srf)
		return false;

	return srf->reconstruct();
};

bool _surf_full_recons(d_surf * srf) {
	if (!srf)
		return false;

	return srf->full_reconstruct();
};

#ifdef HAVE_THREADS
struct surf_project_job : public job 
{
	surf_project_job()
	{
		J_from = 0;
		J_to = 0;
		srf = NULL;
		grd = NULL;
	};
	void set(size_t iJ_from, size_t iJ_to, 
		 const d_surf * isrf, const d_grid * igrd,
		 extvec * icoeff)
	{
		J_from = iJ_from;
		J_to = iJ_to;
		srf = isrf;
		grd = igrd;
		coeff = icoeff;
	};
	virtual void do_job() 
	{
		d_grid * g = srf->grd;
		REAL value, x, y, x0, y0;
		size_t I0, I1, J0, J1;
		REAL z0, z1, z2, z3;
		REAL delta_x, delta_y;

		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
		size_t size_x = grd->getCountX();
		size_t surf_sizeX = srf->getCountX();
		size_t surf_sizeY = srf->getCountY();

		size_t i,j;
		for (j = J_from; j < J_to; j++) {
			for (i = 0; i < (size_t)size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
								
				I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
				J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), surf_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), surf_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), surf_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), surf_sizeY-1);

				srf->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(srf->coeff))(I0 + surf_sizeX*J0);
				z1 = (*(srf->coeff))(I1 + surf_sizeX*J0);
				z2 = (*(srf->coeff))(I1 + surf_sizeX*J1);
				z3 = (*(srf->coeff))(I0 + surf_sizeX*J1);
				
				if (
					(z0 == srf->undef_value) ||
					(z1 == srf->undef_value) ||
					(z2 == srf->undef_value) ||
					(z3 == srf->undef_value) 
					) 
				{
					
					REAL sum = REAL(0);
					int cnt = 0;
					
					if (z0 != srf->undef_value) {
						sum += z0;
						cnt++;
					}
					if (z1 != srf->undef_value) {
						sum += z1;
						cnt++;
					}
					if (z2 != srf->undef_value) {
						sum += z2;
						cnt++;
					}
					if (z3 != srf->undef_value) {
						sum += z3;
						cnt++;
					}
					
					if (cnt == 0) {
						(*coeff)(i + j*size_x) = srf->undef_value;
						continue;
					}

					REAL mean_z = sum/REAL(cnt);
					if (z0 == srf->undef_value)
						z0 = mean_z;
					if (z1 == srf->undef_value)
						z1 = mean_z;
					if (z2 == srf->undef_value)
						z2 = mean_z;
					if (z3 == srf->undef_value)
						z3 = mean_z;
					
				}
				
				delta_x = x - x0;
				delta_y = y - y0;
				
				// первый шаг линейной интерпол€ции
				REAL z11 = (z2-z1)*delta_y/hY+z1;
				REAL z22 = (z3-z0)*delta_y/hY+z0;
				
				// второй шаг линейной интерпол€ции
				REAL res = (z11-z22)*delta_x/hX+z22;
								
				(*coeff)(i + j*size_x) = res;
				
								
			}
		}
	};

	size_t J_from, J_to;
	const d_surf * srf;
	const d_grid * grd;
	extvec * coeff;
};

surf_project_job surf_project_jobs[MAX_CPU];
#endif

d_surf * _surf_project(const d_surf * srf, d_grid * grd) 
{
	size_t size_x = grd->getCountX();
	size_t size_y = grd->getCountY();

	extvec * coeff = create_extvec(size_x*size_y,0,0);  // do not fill this vector
	
	size_t surf_size = srf->coeff->size();
	size_t surf_sizeX = srf->getCountX();
	size_t surf_sizeY = srf->getCountY();

	if (srf->getName())
		writelog(LOG_MESSAGE,"Projecting surf \"%s\" (%d x %d) => (%d x %d)",srf->getName(), surf_sizeX, surf_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting surf (%d x %d) => (%d x %d)", surf_sizeX, surf_sizeY, size_x, size_y);

	{

		REAL x, y;
		size_t I0, J0, I1, J1;
		REAL value;
		size_t i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
#ifdef HAVE_THREADS
		if (sstuff_get_threads() == 1) {
#endif
		d_grid * g = srf->grd;
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
								
				I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
				J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), surf_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), surf_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), surf_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), surf_sizeY-1);

				srf->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(srf->coeff))(I0 + surf_sizeX*J0);
				z1 = (*(srf->coeff))(I1 + surf_sizeX*J0);
				z2 = (*(srf->coeff))(I1 + surf_sizeX*J1);
				z3 = (*(srf->coeff))(I0 + surf_sizeX*J1);
				
				if (
					(z0 == srf->undef_value) ||
					(z1 == srf->undef_value) ||
					(z2 == srf->undef_value) ||
					(z3 == srf->undef_value) 
					) 
				{
					
					REAL sum = REAL(0);
					int cnt = 0;
					
					if (z0 != srf->undef_value) {
						sum += z0;
						cnt++;
					}
					if (z1 != srf->undef_value) {
						sum += z1;
						cnt++;
					}
					if (z2 != srf->undef_value) {
						sum += z2;
						cnt++;
					}
					if (z3 != srf->undef_value) {
						sum += z3;
						cnt++;
					}
					
					if (cnt == 0) {
						(*coeff)(i + j*size_x) = srf->undef_value;
						continue;
					}

					REAL mean_z = sum/REAL(cnt);
					if (z0 == srf->undef_value)
						z0 = mean_z;
					if (z1 == srf->undef_value)
						z1 = mean_z;
					if (z2 == srf->undef_value)
						z2 = mean_z;
					if (z3 == srf->undef_value)
						z3 = mean_z;
					
				}
				
				delta_x = x - x0;
				delta_y = y - y0;
				
				// первый шаг линейной интерпол€ции
				REAL z11 = (z2-z1)*delta_y/hY+z1;
				REAL z22 = (z3-z0)*delta_y/hY+z0;
				
				// второй шаг линейной интерпол€ции
				REAL res = (z11-z22)*delta_x/hX+z22;
								
				(*coeff)(i + j*size_x) = res;
				
								
			}
		}
#ifdef HAVE_THREADS
		} else {
			size_t step = size_y / (sstuff_get_threads());
			size_t ost = size_y % (sstuff_get_threads());
			size_t J_from = 0;
			size_t J_to = 0;
			size_t work;
			for (work = 0; work < sstuff_get_threads(); work++) {
				J_to = J_from + step;
				if (work == 0)
					J_to += ost;
				
				surf_project_job & f = surf_project_jobs[work];
				f.set(J_from, J_to, srf, grd, coeff);
				set_job(&f, work);
				J_from = J_to;
			}

			do_jobs();
		}
#endif
	}
	
	d_grid * new_grd = create_grid(grd);
	d_surf * res = create_surf(coeff, new_grd, srf->getName());
	res->undef_value = srf->undef_value;
	return res;
};

d_surf * _surf_project(d_surf * srf, d_grid * grd, grid_line * fault_grd_line) {

	if (!fault_grd_line)
		return _surf_project(srf, grd);

	size_t size_x = grd->getCountX();
	size_t size_y = grd->getCountY();

	extvec * coeff = create_extvec(size_x*size_y,0,0);  // do not fill this vector
	
	size_t surf_size = srf->coeff->size();
	size_t surf_sizeX = srf->getCountX();
	size_t surf_sizeY = srf->getCountY();

	if (srf->getName())
		writelog(LOG_MESSAGE,"Projecting surf \"%s\" (%d x %d) => (%d x %d)",srf->getName(), surf_sizeX, surf_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting surf (%d x %d) => (%d x %d)", surf_sizeX, surf_sizeY, size_x, size_y);

	{

		REAL x, y;
		size_t I0, J0, I1, J1;
		REAL value;
		size_t i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);

				x -= grd->stepX/REAL(2);
				y -= grd->stepY/REAL(2);
				
				d_grid * g = srf->grd;
				I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
				J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), surf_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), surf_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), surf_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), surf_sizeY-1);

				srf->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(srf->coeff))(I0 + surf_sizeX*J0);
				z1 = (*(srf->coeff))(I1 + surf_sizeX*J0);
				z2 = (*(srf->coeff))(I1 + surf_sizeX*J1);
				z3 = (*(srf->coeff))(I0 + surf_sizeX*J1);
				
				if (
					(z0 == srf->undef_value) &&
					(z1 == srf->undef_value) &&
					(z2 == srf->undef_value) &&
					(z3 == srf->undef_value) 
				   )
				{
					(*coeff)(i + j*size_x) = srf->undef_value;
				} else {
					
					if (
						(z0 == srf->undef_value) ||
						(z1 == srf->undef_value) ||
						(z2 == srf->undef_value) ||
						(z3 == srf->undef_value) 
						) 
					{
						
						REAL sum = REAL(0);
						int cnt = 0;
								
						if (z0 != srf->undef_value) {
							sum += z0;
							cnt++;
						}
						if (z1 != srf->undef_value) {
							sum += z1;
							cnt++;
						}
						if (z2 != srf->undef_value) {
							sum += z2;
							cnt++;
						}
						if (z3 != srf->undef_value) {
							sum += z3;
							cnt++;
						}

						REAL mean_z = sum/REAL(cnt);
						if (z0 == srf->undef_value)
							z0 = mean_z;
						if (z1 == srf->undef_value)
							z1 = mean_z;
						if (z2 == srf->undef_value)
							z2 = mean_z;
						if (z3 == srf->undef_value)
							z3 = mean_z;

					}
					
					delta_x = x - x0;
					delta_y = y - y0;

					if ( fault_grd_line->check_for_pair(I1 + J0*surf_sizeX, 
									    I1 + J1*surf_sizeX) )
					{
						if (delta_y < srf->grd->stepY/REAL(2))
							z2 = z1;
						else
							z1 = z2;
					}

					if ( fault_grd_line->check_for_pair(I0 + J0*surf_sizeX, 
									    I0 + J1*surf_sizeX) )
					{
						if (delta_y < srf->grd->stepY/REAL(2))
							z3 = z0;
						else
							z0 = z3;
					}

					// first step of linear interpolation
					REAL z11 = (z2-z1)*delta_y/hY+z1,
						 z22 = (z3-z0)*delta_y/hY+z0;

					if ( fault_grd_line->check_for_pair(I0 + J0*surf_sizeX,
									    I1 + J0*surf_sizeX)
						 ||
						 fault_grd_line->check_for_pair(I0 + J1*surf_sizeX,
										I1 + J1*surf_sizeX)
					   ) 
					{
						if (delta_x < srf->grd->stepX/REAL(2))
							(*coeff)(i + j*size_x) = z22;
						else
							(*coeff)(i + j*size_x) = z11;
					} else {
						
						// second step of linear interpolation
						REAL Res = (z11-z22)*delta_x/hX+z22;
						(*coeff)(i + j*size_x) = Res;
					}
				}
			}
		}
	}
	
	d_grid * new_grd = create_grid(grd);
	d_surf * res = create_surf(coeff, new_grd, srf->getName());
	res->undef_value = srf->undef_value;
	return res;
};

void _surf_info(const d_surf * srf) {
	if (!srf)
		return;
	writelog(LOG_MESSAGE,"surf (%s) : size=(%d x %d)", srf->getName(), srf->getCountX(), srf->getCountY());
};

bool _surf_resid(const d_surf * srf, const d_points * pnts, const char * filename) {
	if (!srf)
		return false;
	if (!pnts)
		return false;

	if (pnts->size() == 0)
		return false;

	writelog(LOG_MESSAGE, "Calcualting residuals. surface \"%s\", points \"%s\"",
		srf->getName(),pnts->getName());

	FILE * f = fopen(filename, "w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	int pnts_size = pnts->size();
	int cnt;
	REAL res;
	REAL x,y,z;

	REAL maxres = -FLT_MAX;

	vec::iterator x_ptr = pnts->X->begin();
	vec::iterator y_ptr = pnts->Y->begin();
	vec::iterator z_ptr = pnts->Z->begin();

	for (cnt = 0; cnt < pnts_size; cnt++) {
		x = *(x_ptr + cnt);
		y = *(y_ptr + cnt);
		z = *(z_ptr + cnt);
		res = srf->getValue(x,y) - z;
		maxres = (REAL)MAX(fabs(res),maxres);
		fprintf(f,"%lf \t %lf \t %lf %lf\n",x,y,z,res);
	}
	
	fclose(f);
	writelog(LOG_MESSAGE,"max residual : %lf", maxres);

	return true;

};

REAL _surf_D1(const d_surf * srf) {

	size_t i,j;
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	extvec::const_iterator ptr = srf->coeff->const_begin();

	REAL v1, v2;

	REAL dx = 0;
	size_t dx_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			if ((v1 != srf->undef_value) && (v2 != srf->undef_value)) {
				dx += (v2-v1)*(v2-v1);
				dx_cnt++;
			}
		}
	}

	dx /= REAL(dx_cnt);

	REAL dy = 0;
	int dy_cnt = 0;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-2; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + i + (j+1)*NN);
			if ((v1 != srf->undef_value) && (v2 != srf->undef_value)) {
				dy += (v2-v1)*(v2-v1);
				dy_cnt++;
			}
		}
	}

	dy /= REAL(dy_cnt);

	REAL h_x_2 = (srf->grd->stepX)*(srf->grd->stepX);
	REAL h_y_2 = (srf->grd->stepY)*(srf->grd->stepY);

	REAL res = dx/h_x_2 + dy/h_y_2;

	return res;

};

REAL _surf_D2(const d_surf * srf) {

	size_t i,j;
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	extvec::const_iterator ptr = srf->coeff->const_begin();

	REAL v1, v2, v3, v4;

	REAL dx2 = 0;
	size_t dx2_cnt = 0;
	for (i = 0; i < NN-3; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + (i+2) + j*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value)) {
				dx2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dx2_cnt++;
			}
		}
	}

	REAL dxdy = 0;
	size_t dxdy_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-2; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + i + (j+1)*NN);
			v4 = *(ptr + (i+1) + (j+1)*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value) && 
				(v4 != srf->undef_value) ) {
				dxdy += (v4-v3-v2+v1)*(v4-v3-v2+v1);
				dxdy_cnt++;
			}
		}
	}

	REAL dy2 = 0;
	size_t dy2_cnt = 0;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-3; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + i + (j+1)*NN);
			v3 = *(ptr + i + (j+2)*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value)) {
				dy2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dy2_cnt++;
			}
		}
	}

	REAL h_x_2 = (srf->grd->stepX)*(srf->grd->stepX);
	REAL h_y_2 = (srf->grd->stepY)*(srf->grd->stepY);
	writelog(LOG_DEBUG,"h_x_2 = %lf    h_y_2 = %lf",h_x_2, h_y_2);
	writelog(LOG_DEBUG,"dx2_cnt = %d dy2_cnt = %d dxdy_cnt = %d",dx2_cnt, dy2_cnt, dxdy_cnt);
	writelog(LOG_DEBUG,"dx2  = %lf",dx2);
	writelog(LOG_DEBUG,"dy2  = %lf",dy2);
	writelog(LOG_DEBUG,"dxdy = %lf",dxdy);

	dx2 /= REAL(dx2_cnt);
	dxdy /= REAL(dxdy_cnt);
	dy2 /= REAL(dy2_cnt);

	REAL res = dx2/(h_x_2*h_x_2) + 2*dxdy/(h_x_2*h_y_2) + dy2/(h_y_2*h_y_2);

	return res;
};

void _add_surfit_surfs(d_surf * srf) {
	if (!srf)
		return;
	surfit_surfs->push_back(srf);
};

d_surf * _surf_gradient(const d_surf * srf) {

	writelog(LOG_MESSAGE,"calculating gradient of surface \"%s\"", srf->getName());
	
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	bool first_x, second_x;
	bool first_y, second_y;

	extvec * coeff = create_extvec(NN*MM);

	size_t i, j, pos, pos1;
	REAL val;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			
			first_x = true;
			second_x = true;
			first_y = true;
			second_y = true;

			if (i == 0)
				second_x = false;
			if (i == NN-1)
				first_x = false;
			if (j == 0)
				second_y = false;
			if (j == MM-1)
				first_y = false;

			pos = i + j*NN;
			REAL pos_val = (*(srf->coeff))(pos);
			if (pos_val == srf->undef_value) {
				(*(coeff))(pos) = srf->undef_value;
				continue;
			}
			REAL pos1_val;

			val = REAL(0);

			if (first_x) {
				pos1 = (i+1) + j*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_x) {
				pos1 = (i-1) + j*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			if (first_y) {
				pos1 = (i) + (j+1)*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_y) {
				pos1 = i + (j-1)*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			(*(coeff))(pos) = val;
			
		}
	}

	d_grid * grd = create_grid(srf->grd);
	d_surf * res = create_surf(coeff, grd, srf->getName());
	return res;

};

REAL _surf_mean_area(const d_surf * srf, const d_area * area) {
	
	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return srf->undef_value;
	
	size_t i, N = 0;
	REAL sum = 0;
	REAL value;
	for (i = 0; i < mask->size(); i++) {

		if (mask->get(i) == false)
			continue;
		
		value = (*(srf->coeff))(i); 
		
		if (value == srf->undef_value)
			continue;

		sum += value;
		N++;
	}

	if (mask)
		mask->release();
	if (N == 0)
		return srf->undef_value;

	return sum/REAL(N);
	
};

REAL _surf_mean_mask(const d_surf * srf, const d_mask * mask) {
	
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();
	size_t size = NN*MM;

	size_t i, j, N = 0;
	REAL sum = 0;
	REAL value;
	REAL x, y;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			
			srf->getCoordNode(i, j, x, y);
			
			if (mask->getValue(x,y) == false)
				continue;
			
			value = (*(srf->coeff))(i + j*NN); 
			
			if (value == srf->undef_value)
				continue;
			
			sum += value;
			N++;
		}
	}

	if (N == 0)
		return srf->undef_value;

	return sum/REAL(N);
	
};


REAL _surf_wmean_area(const d_surf * srf, const d_surf * wsrf, const d_area * area) {
	
	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	
	size_t i;
	
	if (mask == NULL) 
		return srf->undef_value;
	
	size_t aux_X_from, aux_X_to;
	size_t aux_Y_from, aux_Y_to;
	_grid_intersect1(srf->grd, wsrf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_grid * aux_grid = _create_sub_grid(srf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_surf * w_srf = _surf_project(wsrf, aux_grid);
	size_t nn = aux_grid->getCountX();
	size_t mm = aux_grid->getCountY();
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();
	
	if (aux_grid)
		aux_grid->release();

	REAL denom = 0;
	size_t ii, jj;
	REAL sum = 0;
	REAL value;
	for (i = 0; i < mask->size(); i++) {

		if (mask->get(i) == false)
			continue;
		
		value = (*(srf->coeff))(i);
		if (value == srf->undef_value)
			continue;

		REAL weight = 0;

		one2two(i, ii, jj, NN, MM);

		if ((ii >= aux_X_from) && (ii <= aux_X_to) && (jj >= aux_Y_from) && (jj <= aux_Y_to)) {
			size_t I = ii-aux_X_from;
			size_t J = jj-aux_Y_from;
			weight = (*(w_srf->coeff))(I + J*nn);
			if (weight == w_srf->undef_value)
				weight = 0;
		}

		if (weight <= 0)
			continue;

		sum += value*weight;
		denom += weight;
	}

	if (w_srf)
		w_srf->release();
	if (mask)
		mask->release();

	if (denom == 0)
		return srf->undef_value;
	return sum/denom;
	
};

REAL _surf_wmean_mask(const d_surf * srf, const d_surf * wsrf, const d_mask * mask) {
	
	size_t i;
	
	if (mask == NULL) 
		return srf->undef_value;
	
	size_t aux_X_from, aux_X_to;
	size_t aux_Y_from, aux_Y_to;
	_grid_intersect1(srf->grd, wsrf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_grid * aux_grid = _create_sub_grid(srf->grd, aux_X_from, aux_X_to, aux_Y_from, aux_Y_to);
	d_surf * w_srf = _surf_project(wsrf, aux_grid);
	size_t nn = aux_grid->getCountX();
	size_t mm = aux_grid->getCountY();
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();
	
	if (aux_grid)
		aux_grid->release();

	REAL denom = 0;
	size_t ii, jj;
	REAL sum = 0;
	REAL value;
	REAL x, y;
	for (i = 0; i < NN*MM; i++) {

		one2two(i, ii, jj, NN, MM);
		srf->getCoordNode(ii, jj, x, y);

		if (mask->getValue(x,y) == false)
			continue;
		
		value = (*(srf->coeff))(i);
		if (value == srf->undef_value)
			continue;

		REAL weight = w_srf->getValue(x,y);
		if (weight == w_srf->undef_value)
			weight = 0;
		if (weight <= 0)
			continue;

		sum += value*weight;
		denom += weight;
	}

	if (w_srf)
		w_srf->release();

	return sum/denom;
	
};

REAL _surf_sum_area(const d_surf * srf, const d_area * area) {

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return 0;

	size_t i;

	REAL sum = 0;
	REAL value;
	for (i = 0; i < (size_t)mask->size(); i++) {
		
		if (mask->get(i) == false)
			continue;

		value = (*(srf->coeff))(i);
		if (value == srf->undef_value)
			continue;

		sum += value;
	}

	if (mask)
		mask->release();
	return sum;	

};

int _surf_cells_in_area(const d_surf * srf, const d_area * area) {

	bitvec * mask = nodes_in_area_mask(area, srf->grd);
	if (mask == NULL)
		return 0;
	int res = mask->true_size();
	if (mask)
		mask->release();
	return res;
	
};

d_surf * _surf_load_df(datafile * df, const char * surfname) 
{
	
	if (surfname)
		writelog(LOG_MESSAGE,"loading first surface from file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"loading surface \"%s\" from file %s",surfname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "surf_load : wrong datafile format";

	bool err = false;
	d_surf * srf = NULL;
	extvec * icoeff = NULL;
	d_grid * grd = NULL;
	char * name = NULL;
	REAL undef_value = FLT_MAX;

	extvec * coeff = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("surf","func")) {
			
			df->skipTagName();
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						name = (char*)malloc(strlen(df->getWord())+1);
						strcpy(name,df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}

				if ( df->isWord(REAL_NAME) ) {
					// read char name
					if (!df->readWord()) goto exit;
					
					if ( df->isWord("undef_value") ) {
						if ( !df->readReal(undef_value) ) goto exit;
						goto cont;
					}

					if (!df->skipReal(false)) goto exit;
					goto cont;
				}
				
				if ( df->isWord("array") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord(REAL_NAME) ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("coeff") ) {
							df->readRealArray(coeff);
							goto cont;
						}
					}
					if ( !df->skipArray(false) ) goto exit;
				}
				
				if ( df->isWord("tag") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord("grid") ) {
						if ( !_grid_load_df_tag_readed(df, grd) ) goto exit;
						goto cont;
					}
					if (!df->skipToEndTag()) goto exit;
					goto cont;
				}
								
				if ( !df->skip(false) ) goto exit;
				goto cont;
cont:
				if ( !df->readWord() ) goto exit;
				continue;
			}
		} else {
			goto exit;
		}
		
		if ( !coeff ) {
			writelog(LOG_ERROR,"surf_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(LOG_ERROR,"surf_load : empty geometry");
			err = true;
		}
		
		if (err) {
			if (coeff)
				coeff->release();
			if (grd)
				grd->release();
			free(name);
			return NULL;
		}
		
		srf = create_surf(coeff, grd, name);
		srf->undef_value = undef_value;
		free(name);
		
		if (!surfname) {
			return srf;
		} else {
			if (srf->getName()) {
				if ( StringMatch(surfname,srf->getName()) ) {
					log_printf(" : \"%s\"\n", srf->getName());
					return srf;
				}
			}
			if (srf)
				srf->release();
			srf = NULL;
		}
		
	}
	
	log_printf(" : \"%s\"\n", srf->getName());
	return srf;

exit:

	log_printf("\n");
	if (!surfname)
		writelog(LOG_WARNING, "surf_load : this file have no surf");
	else 
		writelog(LOG_WARNING, "surf_load : this file have no surf named %s", surfname);
	return NULL;

};

d_surf * _surf_load(const char * filename, const char * surfname) {

	datafile * df = new datafile(filename, DF_MODE_READ); // read

	d_surf * res = _surf_load_df(df, surfname);

	if (!res)
		goto exit;

	delete df;
	return res;

exit:

	if (res)
		res->release();
	delete df;
	return NULL;
};
	
bool _surf_save(const d_surf * srf, const char * filename) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	res = _surf_save_df(srf, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _surf_save_df(const d_surf * srf, datafile * df) {

	if (!srf->getName()) 
		writelog(LOG_MESSAGE,"saving surf with no name to file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"saving surf \"%s\" to file %s",srf->getName(),df->get_filename());
		
	bool res = true;
	bool op;
	
	op = srf->writeTags(df);           res = ( op && res );
	
	return res;
};

d_surf * triangulate_points(const d_points * pnts, const d_grid * grid)
{
	size_t points_cnt = pnts->size();

	if (points_cnt < 3)
		return NULL;

	struct triangulateio in, mid;
	in.numberofpoints = points_cnt;
	in.numberofpointattributes = 0;
	in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
	in.pointattributelist = NULL;
	in.pointmarkerlist = NULL;
	in.numberofsegments = 0;
	in.numberofholes = 0;
	in.numberofregions = 0;
	in.regionlist = NULL;

	size_t cnt = 0;
	size_t i;
	for (i = 0; i < points_cnt; i++) {
		in.pointlist[cnt] = (*(pnts->X))(i); 
		cnt++;
		in.pointlist[cnt] = (*(pnts->Y))(i); 
		cnt++;
	}
	
	/* Make necessary initializations so that Triangle can return a */
	/*   triangulation in `mid' and a voronoi diagram in `vorout'.  */
	
	mid.pointlist = (REAL *) NULL;            /* Not needed if -N switch used. */
	/* Not needed if -N switch used or number of point attributes is zero: */
	mid.pointattributelist = (REAL *) NULL;
	mid.pointmarkerlist = (int *) NULL; /* Not needed if -N or -B switch used. */
	mid.trianglelist = (int *) NULL;          /* Not needed if -E switch used. */
	/* Not needed if -E switch used or number of triangle attributes is zero: */
	mid.triangleattributelist = (REAL *) NULL;
	mid.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
	/* Needed only if segments are output (-p or -c) and -P not used: */
	mid.segmentlist = (int *) NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	mid.segmentmarkerlist = (int *) NULL;
	mid.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
	mid.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */
	
	
	/* Triangulate the points.  Switches are chosen to read and write a  */
	/*   PSLG (p), preserve the convex hull (c), number everything from  */
	/*   zero (z), assign a regional attribute to each element (A), and  */
	/*   produce an edge list (e), a Voronoi diagram (v), and a triangle */
	/*   neighbor list (n).                                              */
	
	triangulate((char*)"pczAenQ", &in, &mid, (struct triangulateio *) NULL);

	// get surface bound

	vec * x = create_vec(mid.numberofsegments+1);
	vec * y = create_vec(mid.numberofsegments+1);

	for (i = 0; i < (size_t)mid.numberofsegments; i++)
	{
		if (i == 0) {
			int seg = *(mid.segmentlist + 2*i);
			(*x)(i) = (*(pnts->X))(seg);
			(*y)(i) = (*(pnts->Y))(seg);
		} 
		int seg = *(mid.segmentlist + 2*i+1);
		(*x)(i) = (*(pnts->X))(seg);
		(*y)(i) = (*(pnts->Y))(seg);
	}
	(*x)(i) = (*x)(0);
	(*y)(i) = (*y)(0);

	d_grid * grd = create_grid(grid);
	d_curv * crv = create_curv(x, y);
	d_area * area = create_area(crv, true);
	bitvec * mask = nodes_in_area_mask(area, grd);
	
	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();
	size_t size = NN*MM;
	extvec * coeff = create_extvec(size, undef_value);

	for (i = 0; i < size; i++) {
		if (mask->get(i) == false) {
			(*coeff)(i) = undef_value;
			continue;
		}
	}

	// fill from triangles
	REAL xx[4];
	REAL yy[4];
	REAL zz[3];
	for (i = 0; i < (size_t)mid.numberoftriangles; i++)
	{
		int p0 = mid.trianglelist[3*i];
		int p1 = mid.trianglelist[3*i+1];
		int p2 = mid.trianglelist[3*i+2];
		xx[0] = (*(pnts->X))(p0);
		xx[1] = (*(pnts->X))(p1);
		xx[2] = (*(pnts->X))(p2);
		xx[3] = xx[0];

		yy[0] = (*(pnts->Y))(p0);
		yy[1] = (*(pnts->Y))(p1);
		yy[2] = (*(pnts->Y))(p2);
		yy[3] = yy[0];

		zz[0] = (*(pnts->Z))(p0);
		zz[1] = (*(pnts->Z))(p1);
		zz[2] = (*(pnts->Z))(p2);

		size_t i_from = INT_MAX, i_to = 0;
		size_t j_from = INT_MAX, j_to = 0;

		size_t I, J;

		grd->getCoordPoint(xx[0], yy[0], I, J);
		i_from = MIN(I, i_from);
		i_to = MAX(I, i_to);
		j_from = MIN(J, j_from);
		j_to = MAX(J, j_to);

		grd->getCoordPoint(xx[1], yy[1], I, J);
		i_from = MIN(I, i_from);
		i_to = MAX(I, i_to);
		j_from = MIN(J, j_from);
		j_to = MAX(J, j_to);

		grd->getCoordPoint(xx[2], yy[2], I, J);
		i_from = MIN(I, i_from);
		i_to = MAX(I, i_to);
		j_from = MIN(J, j_from);
		j_to = MAX(J, j_to);

		REAL x, y;

		for (J = j_from; J < j_to; J++) {
			for (I = i_from; I < i_to; I++) {
				grd->getCoordNode(I, J, x, y);
				if ( in_region(xx, yy, 3, x, y) ) {
					size_t pos = two2one(I, J, NN, MM);
					REAL z = undef_value;
					// определители
					REAL d1, d2, d3;
					d1 = (yy[1]-yy[0])*(zz[2]-zz[0])-(yy[2]-yy[0])*(zz[1]-zz[0]);
					d2 = -(xx[1]-xx[0])*(zz[2]-zz[0])+(xx[2]-xx[0])*(zz[1]-zz[0]);
					d3 = (xx[1]-xx[0])*(yy[2]-yy[0])-(yy[1]-yy[0])*(xx[2]-xx[0]);
	
					if (d3 == 0) {
						(*coeff)(pos) = z;
					}
	
					z = zz[0] - ((x-xx[0])*d1 + (y-yy[0])*d2)/d3;
					(*coeff)(pos) = z;
				}
			}
		}
	}

	d_surf * srf = create_surf(coeff, grd);
	srf->undef_value = undef_value;

	mask->release();
	area->release();

	free(in.pointlist);
	free(in.pointattributelist);
	free(in.pointmarkerlist);
	free(in.regionlist);
	free(mid.pointlist);
	free(mid.pointattributelist);
	free(mid.pointmarkerlist);
	free(mid.trianglelist);
	free(mid.triangleattributelist);
	free(mid.neighborlist);
	free(mid.segmentlist);
	free(mid.segmentmarkerlist);
	free(mid.edgelist);
	free(mid.edgemarkerlist);

	return srf;

};

std::vector<d_cntr *> * _surf_trace_cntrs(const d_surf * surf, REAL from, REAL to, REAL step, bool closed)
{
	std::vector<d_cntr *> * res = new std::vector<d_cntr *>();
	
	if (from == FLT_MAX)
		surf->getMinMaxZ(from, to);	
	if (to == FLT_MAX)
		to = from;

	if (step == FLT_MAX)
	{
		step = stepFunc(from, to, 16);
		from = floor( from/step ) * step;
		to = floor( to/step ) * step;
	}

	vec * levels = create_vec();
	REAL level;
	for (level = from; level <= to; level += step)
		levels->push_back(level);

	size_t levels_count = levels->size();
	size_t NN = surf->getCountX(), MM = surf->getCountY();
	size_t q,p;
	REAL x,y;

	vec * x_coords = create_vec(NN,0,0);
	for (q = 0; q < NN; q++) {
		surf->getCoordNode(q,0,x,y);
		(*x_coords)(q) = x;
	}

	vec * y_coords = create_vec(MM,0,0);
	for (q = 0; q < MM; q++) {
		surf->getCoordNode(0,q,x,y);
		(*y_coords)(q) = y;
	}

	extvec * data = create_extvec(*(surf->coeff)); // don't fill;

	writelog(LOG_MESSAGE,"tracing %d contours from surface \"%s\"", levels_count, surf->getName());
	std::vector<fiso *> * isos = trace_isos(levels, x_coords, y_coords, data, NN, MM, surf->undef_value, closed);

	levels->release();
	x_coords->release();
	y_coords->release();
	data->release();

	std::vector<int> cnts(levels_count);
	char buf[512];

	for (q = 0; q < isos->size(); q++)
	{
		fiso * iso = (*isos)[q];
		size_t level_num = iso->get_level_number();
		if (level_num == levels_count)
			level_num = UINT_MAX;
		bool prev_visible = false;
		d_cntr * cntr = NULL;
		vec * x = NULL;
		vec * y = NULL;
		vec * z = NULL;
		REAL iso_level = iso->get_level();
		REAL fill_level = iso->get_fill_level();
		for (p = 0; p < iso->size(); p++) {

			double px, py;
			bool visible;
			iso->get_point(p, px, py, visible);
			if (visible != prev_visible) {
				if (prev_visible == false) {
					if (cntr) {
						if (cntr->size() > 0)
							res->push_back(cntr);
						else {
							if (x)
								x->release();
							if (y)
								y->release();
							if (z)
								z->release();
						}
					}
					if (level_num != UINT_MAX) {
						cnts[level_num]++;
						if (cnts[level_num] == 1)
							sprintf(buf,"%s_%g",surf->getName(), iso->get_level());
						else
							sprintf(buf,"%s_%g_%d",surf->getName(), iso->get_level(), cnts[level_num]);
					} else
						sprintf(buf, "%s_undef", surf->getName());
					x = create_vec();
					y = create_vec();
					z = create_vec();
					cntr = create_cntr(x, y, z, buf);
				}
			}
			if (visible) {
				x->push_back(px);
				y->push_back(py);
				z->push_back(iso_level);
			}
			prev_visible = visible;
		}
		if (cntr) {
			if (cntr->size() > 0)
				res->push_back(cntr);
			else {
				if (x)
					x->release();
				if (y)
					y->release();
				if (z)
					z->release();
			}
		}

	}

	delete isos;


	return res;
};

class projection
{
public:
	projection(double ix0, double iy0, double ix1, double iy1,
		   double ix_0, double iy_0, double ix_1, double iy_1)
	{
		x0 = ix0;
		y0 = iy0;
		x1 = ix1;
		y1 = iy1;
		x_0 = ix_0;
		y_0 = iy_0;
		x_1 = ix_1;
		y_1 = iy_1;
		lx = x1 - x0;
		ly = y1 - y0;
		l_x = x_1 - x_0;
		l_y = y_1 - y_0;
	}

	float get_x(double x) {
		double px = (x-x0)/lx;
		x = x_0 + double(px*l_x);
		return (float)x;
	}

	float get_y(double y) {
		double py = (y-y0)/ly;
		y = y_0 + double(py*l_y);
		return (float)y;
	}

private:
	double x0, y0, x1, y1;
	double lx, ly;
	double x_0, y_0, x_1, y_1;
	double l_x, l_y;
};

float calc_label_width(const char * label, float digit_w, float period_w)
{
	float res = 0;
	size_t i;
	for (i = 0; i < strlen(label); i++) {
		char c = *(label+i);
		if ((c == '.') || (c == ',')) {
			res += period_w;
			continue;
		}
		res += digit_w;
	}
	return res;
};

bool _surf_plot(const d_surf * srf, const char * filename, size_t number_of_levels, bool draw_isos, bool draw_colorscale ) 
{
	if (srf == NULL)
		return false;

	size_t font_size = 8;
	REAL digit_w = REAL(500)/REAL(1000)*font_size/2.834645669291;
	REAL digit_h = font_size/2.834645669291/1.5;
	REAL period_w = REAL(250)/REAL(1000)*font_size/2.834645669291;
	
	REAL from, to, step;

	srf->getMinMaxZ(from, to);	
	
	step = stepFunc(from, to, number_of_levels);
	from = ceil( from/step ) * step;
	to = floor( to/step ) * step;
	
	vec * levels = create_vec();
	REAL level;
	for (level = from; level <= to; level += step)
		levels->push_back(level);

	size_t levels_count = levels->size();
	size_t NN = srf->getCountX(), MM = srf->getCountY();
	size_t q;
	REAL x,y;

	// find appropriate bottom line
	bool founded = false;
	size_t min_j;
	for (min_j = 0; min_j < MM; min_j++) 
	{
		size_t i;
		for (i = 0; i < NN; i++)
		{
			if ( (*(srf->coeff))(i +min_j*NN) != srf->undef_value ) {
				founded = true;
				break;
			}
		}
		if (founded)
			break;
	}

	if (min_j == MM)
		return false;

	vec * x_coords = create_vec(NN,0,0);
	for (q = 0; q < NN; q++) {
		srf->getCoordNode(q,0,x,y);
		(*x_coords)(q) = x;
	}

	vec * y_coords = create_vec(MM-min_j,0,0);
	for (q = min_j; q < MM; q++) {
		srf->getCoordNode(0,q,x,y);
		(*y_coords)(q-min_j) = y;
	}

	extvec * data = NULL;
	if (min_j == 0)
		data = create_extvec(*(srf->coeff)); // copy vector
	else
	{
		size_t size = NN*(MM-min_j);
		data = create_extvec(NN*(MM-min_j),0,false);
		size_t q;
		for (q = 0; q < size; q++) {
			size_t pos = q + NN*min_j;
			REAL val = (*(srf->coeff))(pos);
			(*data)(q) = val;
		}
	}

	writelog(LOG_MESSAGE,"tracing %d contours from surface \"%s\"", levels_count, srf->getName());
	std::vector<fiso *> * isos = trace_isos(levels, x_coords, y_coords, data, NN, MM-min_j, srf->undef_value, true);

	levels->release();
	x_coords->release();
	y_coords->release();
	data->release();
	
	color_scale cs(from, to, step, DEFAULT_COLORS);

	writelog(LOG_MESSAGE,"Plotting surface \"%s\" to file \"%s\"", srf->getName(), filename);
	float minx, maxx, miny, maxy;
	minx = (float)srf->getMinX();
	maxx = (float)srf->getMaxX();
	miny = (float)srf->getMinY();
	maxy = (float)srf->getMaxY();

	float max_len = MAX(maxx-minx, maxy-miny);

	char buf[256];
	size_t i, j;
	REAL added_level = to + FLT_MAX/REAL(2);

	float max_label_width = 0;
	if (draw_colorscale) {
		if (isos)
		for (i = 0; i < isos->size(); i++) {
			fiso * iso = (*isos)[i];
			REAL val = iso->get_level();
			if ((val == added_level) || (val == FLT_MAX))
				continue;
			sprintf(buf,"%g",val);
			max_label_width = MAX(max_label_width, calc_label_width(buf, (float)digit_w, (float)period_w));
		}
	}

	float width = 200;
	if (draw_colorscale)
		width -= max_label_width+20;

	projection prj(minx, miny, minx+max_len, miny+max_len, 0, 0, width, width);

	float MAXX = prj.get_x(maxx);
	float MAXY = prj.get_y(maxy);

	//CreEPS ps(filename, 210, 297); // A4
	CreEPS ps(filename, 200, 200); 
	if (ps.file_status() == false)
	{
		if (isos) {
			free_elements(isos->begin(), isos->end());
			delete isos;
		}
		return false;
	}
	ps.setAttributes( CAtFont((float)font_size) );
	ps.setAttributes( CAtLineThickness(0.1f) );

	std::vector<fiso *> white_bounds;

	int r,g,b;

	if (isos)
	for (i = 0; i < isos->size(); i++) {
		fiso * iso = (*isos)[i];

 		for (j = 0; j < iso->size(); j++)
		{
			double x,y;
			bool vis;
			iso->get_point(j, x, y, vis);
			float X = prj.get_x(x);
			float Y = prj.get_y(y);
			if (j == 0) {
				ps.startPath(X, Y);
			} else {
				ps.addLine(X, Y);
			}
		}

		if ((iso->get_fill_level() == srf->undef_value) && (iso->get_level() == added_level))
		{
			ps.endPath( CreEPS::FILL, CAtColor(1, 1, 1));
			white_bounds.push_back(iso);
		} else {
			cs.get_value(iso->get_fill_level(),r,g,b);
			ps.endPath( CreEPS::FILL, CAtColor(r/255.f, g/255.f, b/255.f) );
		}
	}

	if (isos)
	for (i = 0; i < isos->size(); i++) {

		fiso * iso = (*isos)[i];

		if (draw_isos == false)
			continue;

		if ((iso->get_fill_level() == srf->undef_value) && (iso->get_level() == added_level))
			continue;

		// convert isoline to centimeters
		std::vector<float> XX, YY;
		std::vector<bool> VIS;
		for (j = 0; j < iso->size(); j++)
		{
			double x,y;
			bool vis;
			iso->get_point(j, x, y, vis);
			float X = prj.get_x(x);
			float Y = prj.get_y(y);
			XX.push_back(X);
			YY.push_back(Y);
			VIS.push_back(vis);
		}

		// plot isoline
		for (j = 0; j < XX.size(); j++) {
			float X = XX[j];
			float Y = YY[j];
			bool V = VIS[j];
			bool prev_V = true;
			if (j == 0)
				ps.startPath(X, Y);
			else {
				if ((V == false) && (prev_V == false))
					ps.addMove(X, Y);
				else 
					ps.addLine(X, Y);
			}
			prev_V = V;
		}

		if ((iso->get_fill_level() == srf->undef_value) && (iso->get_level() == added_level))
		{
			ps.setAttributes( CAtLineThickness(0.2f) );
			ps.endPath( CreEPS::STROKE, CAtColor( 1, 1, 1) );
			ps.setAttributes( CAtLineThickness(0.1f) );
		} else {
			cs.get_value(iso->get_fill_level(),r,g,b);
			ps.endPath( CreEPS::STROKE, CAtColor( 0, 0, 0) );
		}

				
	}

	ps.setAttributes( CAtLineThickness(0.1f) );
	for (i = 0; i < white_bounds.size(); i++) {
		fiso * iso = (white_bounds)[i];
 		for (j = 0; j < iso->size(); j++)
		{
			double x,y;
			bool vis;
			iso->get_point(j, x, y, vis);
			float X = prj.get_x(x);
			float Y = prj.get_y(y);
			if (j == 0) {
				ps.startPath(X, Y);
			} else {
				ps.addLine(X, Y);
			}
		}
		ps.endPath( CreEPS::STROKE, CAtColor(0, 0, 0));
	}
	
	if (isos) {
		free_elements(isos->begin(), isos->end());
		delete isos;
	}

	if (draw_colorscale) {
		int q;
		float y_pos = 5;
		float rect_w = 10;
		float rect_h = 10;
		int cs_size = cs.size();

		rect_h = MIN(10, (width-10)/float(cs_size));

		for (q = 0; q < cs_size; q++) {
			cs.get_color(q, r, g, b);
			ps.rectFill(MAXX+5, y_pos, rect_w, rect_h, CAtColor(r/255.f, g/255.f, b/255.f));
			y_pos += rect_h;
		}
		const std::vector<double> * vals = cs.get_values();
		y_pos = 5;
		ps.setAttributes(CAtLineThickness(0.3f));
		ps.setAttributes(CAtColor(0,0,0));
		for (q = 0; q < cs.size(); q++) {
			cs.get_color(q, r, g, b);
			ps.rectStroke(MAXX+5, y_pos, rect_w, rect_h);
			y_pos += rect_h;
			if (q != cs_size-1) {
				ps.line(MAXX+5+rect_w, y_pos, MAXX+5+rect_w+3, y_pos);
				sprintf(buf, "%g", (*vals)[q]);
				ps.print(MAXX+10+rect_w, y_pos-float(digit_h)/2.f, buf);
			}
		}
	}

	return true;
};


}; // namespace surfit;



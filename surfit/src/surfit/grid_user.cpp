
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

#include "fileio.h"

#include "grid.h"
#include "bitvec.h"
#include "vec.h"
#include "surf.h"
#include "surf_internal.h"
#include "surf_tcl.h"
#include "variables_tcl.h"
#include "grid_tcl.h"
#include "variables.h"

#include "grid_user.h"
#include "functional.h"

// temp
#include "curv.h"
#include "grid_line.h"
#include "grid_line_user.h"
#include <float.h>

namespace surfit {

////////////////////////////////////////////////
//
//  G R I D   G L O B A L   V A R I A B L E S
//
////////////////////////////////////////////////

d_grid         *  surfit_grid         = NULL;

/*! \struct grid_garbage
    \brief struct for deletion of \ref grid pointers
*/
struct grid_garbage : public binman {
	//! inits \ref surfit_grid
	grid_garbage() {
		surfit_grid = NULL;
	};
	//! removes \ref surfit_grid
	~grid_garbage() {
		if (surfit_grid)
			surfit_grid->release();
	};
};

grid_garbage gird_garb;

d_grid * method_grid = NULL;
d_grid * method_sub_grid = NULL;
d_grid * method_prev_grid = NULL;
extvec * method_X = NULL;
bool method_ok = false;
bitvec * method_mask_solved = NULL;
bitvec * method_mask_undefined = NULL;
size_t basis_cnt = 8;
size_t method_basis_cntX = 8;
size_t method_basis_cntY = 8;
size_t method_phase_counter = 0;
REAL method_scaleX = FLT_MAX;
REAL method_shiftX = FLT_MAX;
REAL method_scaleY = FLT_MAX;
REAL method_shiftY = FLT_MAX;
REAL method_stepX = FLT_MAX;
REAL method_stepY = FLT_MAX;
bool doubleX = false;
bool doubleY = false;

/////////////////////////////////////////////////
//
//   G R I D   U S E F U L   F U N C T I O N S
//
/////////////////////////////////////////////////

size_t one2one(size_t pos, const d_grid * from, const d_grid * to) {
	size_t n, m;
	one2two(pos, n, m, from->getCountX(), from->getCountY());
	REAL x, y;
	from->getCoordNode(n, m, x, y);
	n = to->get_i(x);
	m = to->get_j(y);
	pos = two2one(n, m, to->getCountX(), to->getCountY());
	to->getCoordNode(n,m, x, y);
	return pos;
};

void two2two(size_t & n, size_t & m, const d_grid * from, const d_grid * to) 
{
	REAL x, y;
	from->getCoordNode(n, m, x, y);
	n = to->get_i(x);
	m = to->get_j(y);
};

bool one2two(size_t pos, size_t & i, size_t & j, size_t NN, size_t MM) 
{
	if (pos >= 0 && pos < NN*MM) {
		i = pos % NN;
		j = (pos - i)/NN;
		return true;
	}

	i = UINT_MAX;
	j = UINT_MAX;
	//assert(0);
	return false;
};

bool grid_bound(size_t pos, size_t NN, size_t MM) {
	size_t n, m;
	one2two(pos, n, m, NN, MM);
	return ( (n >= 0) && (n < NN) && (m >= 0) && (m < MM) );
};

bool grid_bound2(size_t n, size_t m, size_t NN, size_t MM) {
	return ( (n >= 0) && (n < NN) && (m >= 0) && (m < MM) );
};

template<class VEC, class iter>
void project_vector(VEC * A, size_t NN, size_t MM,
		    bool doubleX, bool doubleY) {

	if (!doubleX && !doubleY)
		return;

	if (doubleY) {
		size_t size = A->size();
		A->resize(size*2,0,0);
		iter A_it = A->begin() + size - 1;
		iter new_A_it = A->begin() + size*2 - 1;
		iter temp_it;
		iter A_beg = A->begin();
		while ( new_A_it != A->begin() - 1 ) {
			size_t i;
			temp_it = A_it;
			for ( i = 0; i < NN; i++) {
				*new_A_it = *A_it;
				new_A_it--;
				A_it--;
			}
			A_it = temp_it;
			for ( i = 0; i < NN; i++) {
				*new_A_it = *A_it;
				new_A_it--;
				A_it--;
			}
		}
	}

	if (doubleX) {
		NN *= 2;
		size_t size = A->size();
		A->resize(size*2,0,0);
		iter A_it = A->begin() + size - 1;
		iter new_A_it = A->begin() + size*2 - 1;
		iter A_beg = A->begin();
		while ( new_A_it != A->begin() - 1 ) {
			*new_A_it = *A_it;
			new_A_it--;
			*new_A_it = *A_it;
			new_A_it--;
			A_it--;
		}
		
	}
	 	
};

d_grid * create_calc_grd(size_t basis_cntX, size_t basis_cntY) 
{
	REAL grid_lengthX = surfit_grid->endX + surfit_grid->stepX - surfit_grid->startX;
	size_t grid_nodesX = surfit_grid->getCountX();
	REAL grid_lengthY = surfit_grid->endY + surfit_grid->stepY - surfit_grid->startY;
	size_t grid_nodesY = surfit_grid->getCountY();

	REAL grd_startX = surfit_grid->startX-surfit_grid->stepX/REAL(2);
	REAL grd_endX = surfit_grid->endX+surfit_grid->stepX/REAL(2);
	REAL grd_startY = surfit_grid->startY-surfit_grid->stepY/REAL(2);
	REAL grd_endY = surfit_grid->endY+surfit_grid->stepY/REAL(2);
	REAL grd_stepX = (grd_endX-grd_startX)/REAL(basis_cntX);
	REAL grd_stepY = (grd_endY-grd_startY)/REAL(basis_cntY);

	d_grid * grd = create_grid(grd_startX+grd_stepX/REAL(2), 
			           grd_endX-grd_stepX/REAL(2), 
			           grd_stepX, 
			           grd_startY+grd_stepY/REAL(2), 
			           grd_endY-grd_stepY/REAL(2), 
			           grd_stepY, 
			           NULL);
	return grd;

};

d_grid * create_last_grd() {

	REAL grid_lengthX = surfit_grid->endX+surfit_grid->stepX - surfit_grid->startX;
	size_t grid_nodesX = surfit_grid->getCountX();
	REAL grid_lengthY = surfit_grid->endY+surfit_grid->stepY - surfit_grid->startY;
	size_t grid_nodesY = surfit_grid->getCountY();

	double log2 = log(double(2));
	size_t last_basis_cntX = (size_t)ceil(log((REAL)grid_nodesX)/log2);
	size_t last_basis_cntY = (size_t)ceil(log((REAL)grid_nodesY)/log2);
	last_basis_cntX = (size_t)pow(2., (int)last_basis_cntX);
	last_basis_cntY = (size_t)pow(2., (int)last_basis_cntY);

	REAL grd_startX = surfit_grid->startX-surfit_grid->stepX/REAL(2);
	REAL grd_endX = surfit_grid->endX+surfit_grid->stepX/REAL(2);
	REAL grd_startY = surfit_grid->startY-surfit_grid->stepY/REAL(2);
	REAL grd_endY = surfit_grid->endY+surfit_grid->stepY/REAL(2);

	REAL grd_stepX = (grd_endX-grd_startX)/REAL(last_basis_cntX);
	REAL grd_stepY = (grd_endY-grd_startY)/REAL(last_basis_cntY);

	d_grid * last_grd = create_grid(grd_startX+grd_stepX/REAL(2), 
		                        grd_endX-grd_stepX/REAL(2), 
				        grd_stepX, 
				        grd_startY+grd_stepY/REAL(2), 
				        grd_endY-grd_stepY/REAL(2), 
				        grd_stepY, 
				        NULL);

	return last_grd;
};

////////////////////////////////
//
// functions for grid sequence
//
////////////////////////////////
void grid_init() {
	method_grid = NULL;
	method_sub_grid = NULL;
	method_prev_grid = NULL;
	method_X = NULL;
	method_mask_solved = NULL;
	method_mask_undefined = NULL;
	doubleX = false;
	doubleY = false;
};

void grid_prepare()
{
	method_basis_cntX = basis_cnt;
	method_basis_cntY = basis_cnt;
	method_phase_counter = 0;
	method_scaleX = 1;
	method_shiftX = 0;
	method_scaleY = 1;
	method_shiftY = 0;
	method_stepX = 0;
	method_stepY = 0;
	method_ok = false;

	if (surfit_grid == NULL) {
		grid();
	}

	if (surfit_grid == NULL) {
		return;
	}

	REAL startx, starty, endx, endy;
	surfit_grid->getCoordNode(0,0,startx,starty);
	startx -= surfit_grid->stepX/REAL(2);
	starty -= surfit_grid->stepY/REAL(2);
	surfit_grid->getCoordNode(surfit_grid->getCountX()-1,
		                  surfit_grid->getCountY()-1,
				  endx,endy);
	endx += surfit_grid->stepX/REAL(2);
	endy += surfit_grid->stepY/REAL(2);
	
	method_sub_grid = create_grid((startx+endx)/REAL(2), (startx+endx)/REAL(2), (endx-startx),
				      (starty+endy)/REAL(2), (starty+endy)/REAL(2), (endy-starty));
};

void grid_begin() {
	
	method_phase_counter++;

	writelog(LOG_MESSAGE,"");
	writelog(LOG_MESSAGE,"*************");
	if (map_name)
		writelog(LOG_MESSAGE,"* Phase %d, grid size = %d x %d (%s)",
		         method_phase_counter, method_basis_cntX, method_basis_cntY, map_name);
	else
		writelog(LOG_MESSAGE,"* Phase %d, grid size = %d x %d",
		         method_phase_counter, method_basis_cntX, method_basis_cntY);
	
	writelog(LOG_MESSAGE,"*************");

	// Создаем геометрию, с которой будем считать
	if (method_grid)
		method_grid->release();
	method_grid = create_calc_grd(method_basis_cntX, method_basis_cntY);
	
	size_t NN = method_grid->getCountX();
	size_t MM = method_grid->getCountY();
	size_t matrix_size = NN*MM;
	
	if (!method_X) 
		method_X = create_extvec(matrix_size);

	if (method_mask_solved)
		method_mask_solved->release();
	method_mask_solved = create_bitvec(matrix_size);
	method_mask_solved->init_false();
	if (method_mask_undefined)
		method_mask_undefined->release();
	method_mask_undefined = create_bitvec(matrix_size);
	method_mask_undefined->init_false();

	method_scaleX = REAL(1)/method_grid->stepX;
	method_shiftX = method_grid->startX;
	method_scaleY = REAL(1)/method_grid->stepY;
	method_shiftY = method_grid->startY;
	method_stepX = method_grid->stepX;
	method_stepY = method_grid->stepY;
	REAL div = method_stepX/method_stepY;
	if (div > 1) {
		method_stepX = 1;
		method_stepY = REAL(1)/div;
	} else {
		method_stepX = div;
		method_stepY = 1;
	}

};

void grid_finish() {

	if (
		(method_grid->getCountX() >= surfit_grid->getCountX()) &&
		(method_grid->getCountY() >= surfit_grid->getCountY())
	   )
		method_ok = true;

	if (method_ok) {
		size_t i;
		for (i = 0; i < method_mask_undefined->size(); i++) {
			if (method_mask_undefined->get(i)) {
				(*method_X)(i) = undef_value;
				continue;
			}
			if (method_mask_solved->get(i) == false)
				(*method_X)(i) = undef_value;
		}
		return;		
	}

	// solve problem with undefined values and projections
	{
		size_t i;
		REAL mean = 0;
		size_t cnt = 0;
		for (i = 0; i < method_mask_undefined->size(); i++)
		{
			if ((method_mask_undefined->get(i) == true) || (method_mask_solved->get(i) == false))
			{
				(*method_X)(i) = undef_value;
				continue;
			}
			mean += (*method_X)(i);
			cnt++;
		}
		if (cnt != 0)
		{
			mean /= REAL(cnt);
			size_t NN = method_grid->getCountX();
			size_t MM = method_grid->getCountY();
			for (i = 0; i < NN*MM; i++) {
				if ((*method_X)(i) == undef_value)
				{
					size_t ii,jj;
					one2two(i, ii, jj, NN, MM);
					REAL lmean = 0;
					size_t lcnt = 0;
					if (jj >= 1)
					{
						REAL val = (*method_X)( two2one(ii,jj-1,NN,MM) );
						if (val != undef_value) {
							lmean += val;
							lcnt++;
						}
					}
					if (ii >= 1)
					{
						REAL val = (*method_X)( two2one(ii-1,jj,NN,MM) );
						if (val != undef_value) {
							lmean += val;
							lcnt++;
						}
					}
					if (ii+1 < NN)
					{
						REAL val = (*method_X)( two2one(ii+1,jj,NN,MM) );
						if (val != undef_value) {
							lmean += val;
							lcnt++;
						}
					}
					if (jj+1 < MM)
					{
						REAL val = (*method_X)( two2one(ii,jj+1,NN,MM) );
						if (val != undef_value) {
							lmean += val;
							lcnt++;
						}
					}
					if (lcnt == 0)
						(*method_X)(i) = mean;
					else {
						lmean /= REAL(lcnt);
						(*method_X)(i) = lmean;
					}
				}
			}
		}
	}


	if (method_sub_grid)
		method_sub_grid->release();
	method_sub_grid = create_grid(method_grid);

	if (method_prev_grid)
		method_prev_grid->release();
	method_prev_grid = create_grid(method_grid);
	
	doubleX = false;
	doubleY = false;
	bool use_fast_project = true;
	
	if (method_grid->getCountX() < surfit_grid->getCountX()) {
		method_basis_cntX *= 2;
		doubleX = true;
		if (method_basis_cntX > surfit_grid->getCountX()) {
			doubleX = false;
			use_fast_project = false;
			method_basis_cntX = surfit_grid->getCountX();
		}
	}
	
	if (method_grid->getCountY() < surfit_grid->getCountY()) {
		method_basis_cntY *= 2;
		doubleY = true;
		if (method_basis_cntY > surfit_grid->getCountY()) {
			doubleY = false;
			use_fast_project = false;
			method_basis_cntY = surfit_grid->getCountY();
		}
	}
	
	// updating sigma's coeff
	if (use_fast_project)
	{
		project_vector<extvec,extvec::iterator>(method_X, method_grid->getCountX(), method_grid->getCountY(), doubleX, doubleY);

		// check for faults
		grid_line * faults = NULL;
		size_t i;
		for (i = 0; i < functionals->size(); i++)
		{
			
		}
		
	} else {
		d_surf * current_surf = create_surf(method_X, method_grid, map_name);
		d_surf * projected_surf = NULL;
		if (doubleX && doubleY)
			projected_surf = _surf_project(current_surf, surfit_grid);
		else {
			d_grid * proj_grid = create_grid(surfit_grid);
			if (doubleX)
				proj_grid->stepX = method_grid->stepX/REAL(2);
			if (doubleY)
				proj_grid->stepY = method_grid->stepY/REAL(2);
			projected_surf = _surf_project(current_surf, proj_grid);
			proj_grid->release();
			
		}
		current_surf->coeff = NULL;
		current_surf->grd = NULL;
		current_surf->release();
		method_X->release();
		method_X = projected_surf->coeff;
		projected_surf->coeff = NULL;
		method_grid->release();
		method_grid = projected_surf->grd;
		projected_surf->grd = NULL;
		projected_surf->release();
	}
		
	
};

void grid_release() {

	size_t i;
	for (i = 0; i < method_X->size(); i++) {
		if (method_mask_solved->get(i) == false)
			(*method_X)(i) = undef_value;
	}

	if (method_mask_solved)
		method_mask_solved->release();
	method_mask_solved = NULL;
	if (method_mask_undefined)
		method_mask_undefined->release();
	method_mask_undefined = NULL;
	if (method_sub_grid)
		method_sub_grid->release();
	method_sub_grid = NULL;

	if (method_prev_grid)
		method_prev_grid->release();
	
	d_surf * res_surf = create_surf(method_X, create_grid(method_grid), map_name);
	if (method_grid)
		method_grid->release();
	method_grid = NULL;
	method_X = NULL;

	res_surf->undef_value = surfit::undef_value;
	res_surf->setName(map_name);
	
	surfit_surfs->push_back(res_surf);	

	//surf_project();

};

void draw_grid_matlab(FILE * ff, const d_grid * grd, const char * color) 
{

#ifndef DEBUG
	return;
#endif

	fprintf(ff,"hold on; \n");

	size_t i;
	REAL x0, y0;
	grd->getCoordNode(0,0,x0,y0);
	REAL xN, yM;
	grd->getCoordNode(grd->getCountX()-1,grd->getCountY()-1,xN,yM);
	
	REAL stepX = grd->stepX/REAL(2);
	REAL stepY = grd->stepY/REAL(2);
	
	REAL x_0, x_1;
	REAL y_0, y_1;
	
	y_0 = y0 - stepY;
	y_1 = yM + stepY;
	for (i = 0; i < grd->getCountX()+1; i++) {
		x_0 = grd->getCoordNodeX(i)-stepX;
		x_1 = x_0;//grd->getCoordNodeX(i+1)+stepX;
		fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','%s');\n",x_0,x_1,y_0,y_1,color);
	}
	
	x_0 = x0 - stepX;
	x_1 = xN + stepX;
	for (i = 0; i < grd->getCountY()+1; i++) {
		y_0 = grd->getCoordNodeY(i)-stepY;
		y_1 = y_0;//grd->getCoordNodeY(i+1)+stepY;
		fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','%s');\n",x_0,x_1,y_0,y_1,color);
	}
	
	//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,y0);
	//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,yM);
	//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,y0);
	//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,yM);
	
	
	fflush(ff);
};

}; // namespace surfit;


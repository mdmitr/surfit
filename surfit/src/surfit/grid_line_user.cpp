
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
#include "grid_line.h"
#include "bitvec.h"
#include "intvec.h"
#include "grid.h"
#include "curv.h"
#include "curv_internal.h"

#include "grid_line_user.h"
#include "grid_user.h"

namespace surfit {

void draw_bitvec_matlab(FILE * ff, const d_grid * grd, const bitvec * data, const char * color)
{

#ifndef DEBUG
	return;
#endif
	
	size_t nn = grd->getCountX();
	size_t pos;
	size_t max_pos = grd->getCountX()*grd->getCountY();
	for (pos = 0; pos < max_pos; pos++) {

		if (data->get(pos) == false)
			continue;
		
		// paint flowed area
		
		int n = pos % nn;
		int m = (pos - n)/nn;
		
		REAL x, y;
		grd->getCoordNode(n,m,x,y);
		
		REAL stepX = grd->stepX/REAL(2);
		REAL stepY = grd->stepY/REAL(2);
		
		REAL x_, y_;
		
		y_ = y - stepY;
		x_ = x - stepX;
		
		fprintf(ff,"plot(%lf, %lf,'.','color','%s');\n",x,y,color);
		
	}

	fflush(ff);
};

void draw_filled_grid_matlab(FILE * ff, const d_grid * grd, const shortvec * data)
{
#ifndef DEBUG
	return;
#endif
	
	size_t nn = grd->getCountX();
	size_t pos;
	size_t max_pos = grd->getCountX()*grd->getCountY();
	for (pos = 0; pos < max_pos; pos++) {
		
		// paint flowed area
		
		int n = pos % nn;
		int m = (pos - n)/nn;
		
		REAL x, y;
		grd->getCoordNode(n,m,x,y);
		
		REAL stepX = grd->stepX/REAL(2);
		REAL stepY = grd->stepY/REAL(2);
		
		REAL x_, y_;
		
		y_ = y - stepY;
		x_ = x - stepX;
		
		short int j = (*data)(pos);
		
		while (j > 7)
			j-=7;
		
		if (j == 1)
			fprintf(ff,"plot(%lf, %lf,'.','color','green');\n",x,y);
		if (j == 2)
			fprintf(ff,"plot(%lf, %lf,'.','color','red');\n",x,y);
		if (j == 3)
			fprintf(ff,"plot(%lf, %lf,'.','color','blue');\n",x,y);
		if (j == 4)
			fprintf(ff,"plot(%lf, %lf,'.','color','magenta');\n",x,y);
		if (j == 5)
			fprintf(ff,"plot(%lf, %lf,'.','color','cyan');\n",x,y);
		if (j == 6)
			fprintf(ff,"plot(%lf, %lf,'.','color','black');\n",x,y);
		if (j == 7)
			fprintf(ff,"plot(%lf, %lf,'.','color','yellow');\n",x,y);
		
	}
	
	fflush(ff);
	
};

void draw_grid_line_matlab(FILE * ff, const grid_line * line, const d_grid * grd, const char * color, short thick) 
{
#ifndef DEBUG
	return;
#endif

	if (line == NULL)
		return;
	if (grd == NULL)
		return;

	size_t fl_size = line->size();
	size_t i;
	size_t J1, J2;
	size_t pos_i, pos_j;
	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();
	for (i = 0; i < fl_size; i++) {
		J1 = line->get_first_cell(i);
		J2 = line->get_second_cell(i);
		
		one2two(J1, pos_i, pos_j, NN+2, MM+2);
		pos_i--;
		pos_j--;
		
		REAL x, y;
		
		REAL stepX2 = grd->stepX/REAL(2);
		REAL stepY2 = grd->stepY/REAL(2);
		grd->getCoordNode(pos_i,pos_j,x,y);
		
		int diff = (J2-J1);
		
		// right line
		if (diff == 1) {
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x+stepX2, x+stepX2, y-stepY2, y+stepY2, color, thick);
		}
		
		// left line
		if (diff == -1) {
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x-stepX2, x-stepX2, y-stepY2, y+stepY2, color, thick);
		}
		
		// up line 
		if (diff == NN+2) {
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x-stepX2, x+stepX2, y+stepY2, y+stepY2, color, thick);
		}
		
		// down line
		if (-diff == NN+2) { // diff == -NN-2
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x-stepX2, x+stepX2, y-stepY2, y-stepY2, color, thick);
		}
		
	}
	
	fflush(ff);
};

void draw_brez_matlab(FILE * ff, const sizetvec * nns, const d_grid * grd, size_t NN, size_t MM) 
{
#ifndef DEBUG
	return;
#endif
	if (nns)
	{
		size_t i;
		size_t x, y, pos;
		//char text[10];
		for (i = 0; i < nns->size()-1; i++) {
			pos = (*nns)(i);
			one2two(pos,x,y,NN+1,MM+1);
			REAL X, Y;
			grd->getCoordNode(x,y,X,Y);
			fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",X,Y);
			//itoa(i , text, 10);
			//fprintf(ff,"text(%lf, %lf, '%s');\n",X,Y,text);
		}
	}
	fflush(ff);
};

inline
void add_val(sizetvec * v, size_t n, size_t m, size_t NN, size_t MM) {
	if ((n < 0) || (n >= NN))
		return;

	if ((m < 0) || (m >= MM))
		return;

	size_t val = n + m*NN;
	v->push_back(val);
};

inline
void add_val_pair(sizetvec * v1, size_t n1, size_t m1, 
		  sizetvec * v2, size_t n2, size_t m2, 
		  size_t NN, size_t MM) {
	
	size_t val1, val2;
	val1 = two2one(n1, m1, NN, MM);
	val2 = two2one(n2, m2, NN, MM);
	
	if ((val1 == UINT_MAX) || (val2 == UINT_MAX))
		return;
	
	if (v1->size() > 0) {
		size_t prev_val1, prev_val2;
		prev_val1 = *(v1->end()-1);
		prev_val2 = *(v2->end()-1);
		if ((val1 == prev_val1) && (val2 == prev_val2))
			return;
		
	}
	
	v1->push_back(val1);
	v2->push_back(val2);
		
};

void add_sect(sizetvec * nns, 
	      REAL X1, REAL Y1, REAL X2, REAL Y2,
	      d_grid * grd2)
{
	int dx, dy, i1, i2, i, kx, ky;
	int d;      // "residual" 
	size_t x, y;
	int flag;

	size_t NN = grd2->getCountX();
	size_t MM = grd2->getCountY();

	size_t x1 = grd2->get_i(X1);
	size_t x2 = grd2->get_i(X2);
	size_t y1 = grd2->get_j(Y1);
	size_t y2 = grd2->get_j(Y2);

	dy = y2 - y1;
	dx = x2 - x1;
	REAL DY = Y2-Y1;
	REAL DX = X2-X1;

	if (dx == 0 && dy == 0) { // only one point
		add_val(nns, x1, y1, NN, MM);
		return;
	}

	kx = 1; // step by OX
	ky = 1; // step by OY

	// Selection of the main direction 
	if ( dx < 0 ) { 
		dx = -dx; 
		kx = -1;       // Y
	} else {
		if(dx == 0)
			kx = 0;    // X 
	}

	if (dy < 0) { 
		dy = -dy; 
		ky = -1; 
	}

	if (dx < dy) { 
		flag = 0; 
		d = dx; 
		dx = dy; 
		dy = d; 
	}
	else         
		flag = 1;

	i1 = dy + dy; d = i1 - dx; i2 = d - dx;
	x = x1; y = y1;

	REAL p_x, p_y;

	for ( i = 0; i < dx; i++ ) {

		grd2->getCoordNode(x,y,p_x,p_y);
		add_val(nns, x, y, NN, MM);

		if (flag) 
			x += kx; // step by main direction
		else     
			y += ky;

		if( d < 0 ) {// horizontal step
			d += i1;
		} else {       // diagonal step

			int x_0;
			int x_1;
			int y_0;
			int y_1;

			if (flag) {
				x_0 = x-kx;
				x_1 = x;
				y_0 = y;
				y_1 = y+ky;
			} else {
				y_0 = y-ky;
				y_1 = y;
				x_0 = x;
				x_1 = x+kx;
			}
			REAL X_0 = grd2->getCoordNodeX(x_0);
			REAL X_1 = grd2->getCoordNodeX(x_1);
			REAL Y_0 = grd2->getCoordNodeY(y_0);
			REAL Y_1 = grd2->getCoordNodeY(y_1);

			if (flag) {

				if (fabs( DY*(X_0-X1) + DX*(Y1-Y_1) ) - fabs( DY*(X_1-X1) + DX*(Y1-Y_0)) < 0) {
					x -= kx;
					y += ky;
					grd2->getCoordNode(x,y,p_x,p_y);
					add_val(nns, x, y, NN, MM);
					x += kx;
				} else {
					grd2->getCoordNode(x,y,p_x,p_y);
					add_val(nns, x, y, NN, MM);
					y += ky; 
				}

			} else {

				if (fabs( DX*(Y_0-Y1) + DY*(X1-X_1) ) - fabs( DX*(Y_1-Y1) + DY*(X1-X_0)) < 0) {
					y -= ky;
					x += kx;
					grd2->getCoordNode(x,y,p_x,p_y);
					add_val(nns, x, y, NN, MM);
					y += ky;
				} else {
					grd2->getCoordNode(x,y,p_x,p_y);
					add_val(nns, x, y, NN, MM);
					x += kx;
				}
			}

			d += i2;
		}
	}
	add_val(nns, x2, y2, NN, MM); // last point
};

sizetvec * curv_to_nns(const d_curv * crv, d_grid * grd)
{
	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();
	sizetvec * nns = create_sizetvec(); // ?

	d_grid * grd2 = create_grid(grd);

	// extend grid
	grd2->startX -= grd2->stepX;
	grd2->startY -= grd2->stepY;
	grd2->endX += grd2->stepX;
	grd2->endY += grd2->stepY;

	REAL old2_startX = grd2->startX;
	REAL old2_startY = grd2->startY;
	REAL old2_endX = grd2->endX;
	REAL old2_endY = grd2->endY;

	size_t NNN = grd2->getCountX();
	size_t MMM = grd2->getCountY();

	// transform grid from cell-based to node-based
	grd2->startX -= grd2->stepX/REAL(2);
	grd2->startY -= grd2->stepY/REAL(2);
	grd2->endX += grd2->stepX/REAL(2);
	grd2->endY += grd2->stepY/REAL(2);

	NN = grd2->getCountX();
	MM = grd2->getCountY();

	bool closed = crv->is_closed();
	
	// using modified brezengham algorithm
	size_t qq;
	REAL X2, X1, Y2, Y1;
		
	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = (*(crv->X))(qq);
		X2 = (*(crv->X))(qq + 1);
		Y1 = (*(crv->Y))(qq);
		Y2 = (*(crv->Y))(qq + 1);
		
		add_sect(nns, X1, Y1, X2, Y2, grd2);
		
		
	}

	// repeats deletions
	size_t old_size = nns->size();
	size_t write_pos = 0;
	for (qq = 1; qq < nns->size(); qq++) {
		if ( (*nns)(write_pos) != (*nns)(qq) ) {
			write_pos++;
			(*nns)(write_pos) = (*nns)(qq);
		}
	}
	nns->resize(write_pos+1);

	grd2->release();
	return nns;
}

grid_line * curv_to_grid_line(grid_line * grd_line, const d_curv * in_crv, d_grid * grd) {

	d_curv * crv = NULL;
	if (in_crv->is_closed())
		crv = _curv_intersect_grid(in_crv, grd);
	else 
		crv = create_curv(in_crv);

	if (!crv)
		return grd_line;
		
	size_t NN = grd->getCountX()+3;
	size_t MM = grd->getCountY()+3;
	size_t NNN = NN-1;
	size_t MMM = MM-1;
	sizetvec * nns = curv_to_nns(crv, grd);
	
	if (nns->size() == 0) {
		nns->release();
		if (crv)
			crv->release();
		return grd_line;
	}

	sizetvec * cells1 = create_sizetvec();
	sizetvec * cells2 = create_sizetvec();
	cells1->reserve(nns->size());
	cells2->reserve(nns->size());

	size_t n1, m1, n2, m2, pos1, pos2;

	size_t i;
	for (i = 0; i < nns->size()-1; i++) {

		pos1 = (*nns)(i);
		if (one2two(pos1, n1, m1, NN, MM) == false)
			continue;
	
		pos2 = (*nns)(i+1);
		if (one2two(pos2, n2, m2, NN, MM) == false)
			continue;
		
		size_t max_n = MAX(n1, n2);
		size_t min_m = MIN(m1, m2);
		
		if (n2 != n1) { // horizontal line
			add_val_pair(cells1, max_n-1, min_m, 
				     cells2, max_n-1, min_m-1,
				     NNN,MMM);
		} else { // vertical line
			add_val_pair(cells1, max_n, min_m, 
				     cells2, max_n-1, min_m,
				     NNN,MMM);
		}
		
	}

	///*
	nns->release();  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nns = NULL;
	//*/
	
	if (!grd_line) {
		grd_line = create_grid_line(NNN, MMM, cells1, cells2);
	} else {
		grd_line->add(cells1, cells2);
	}

	/*
#ifdef DEBUG

	// restore extended grid
	grd2->startX = old2_startX;
	grd2->startY = old2_startY;
	grd2->endX = old2_endX;
	grd2->endY = old2_endY;
	NN = grd2->getCountX();
	MM = grd2->getCountY();

	FILE * ff = fopen("c:\\qqq.m","w+");
	fprintf(ff,"hold on\n");

	
	draw_curv_matlab(ff, crv);
	draw_brez_matlab(ff, nns, grd2, NN, MM);
	draw_grid_matlab(ff, grd);
	draw_grid_line_matlab(ff, grd_line, grd);
	
	fclose(ff);
#endif
	//*/

	if (crv)
		crv->release();
	return grd_line;

};

}; // namespace surfit;



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
#include "grid_line.h"
#include "bitvec.h"
#include "intvec.h"
#include "grid.h"
#include "curv.h"

#include "grid_line_user.h"
#include "grid_user.h"

namespace surfit {

grid_line * surfit_grid_line = NULL;

/*! \struct grid_line_garbage
    \brief struct for deletion of pointers
*/
struct grid_line_garbage : public binman {
	//! inits \ref surfit_grid_line
	grid_line_garbage() {
		surfit_grid_line = NULL;
	}
	//! removes \ref surfit_grid_line
	~grid_line_garbage() {
		delete surfit_grid_line;
		surfit_grid_line = NULL;
	};
};

grid_line_garbage grid_line_garb;


void debug_print_grid_line(const char * filename,
			   grid_line * grd_line, grid * grd,
			   bitvec * mask_solved, 
			   bitvec * mask_undefined,
			   curv * crv) {

	int NN = grd->getCountX();

	FILE * ff = fopen(filename,"w+");
	fprintf(ff,"hold on\n");
				
	// draw grid
	{
		int i;
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
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		x_0 = x0 - stepX;
		x_1 = xN + stepX;
		for (i = 0; i < grd->getCountY()+1; i++) {
			y_0 = grd->getCoordNodeY(i)-stepY;
			y_1 = y_0;//grd->getCoordNodeY(i+1)+stepY;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		//char text1[6];
		//char text2[6];
		int j;
		int J;
		if (mask_solved && mask_undefined)
		for (j = 0; j < grd->getCountY(); j++) {
			for (i = 0; i < grd->getCountX(); i++) {
				J = i + j*NN;
				x_0 = grd->getCoordNodeX(i);
				y_0 = grd->getCoordNodeY(j);
				if (mask_solved->get(J)) {
					fprintf(ff,"plot(%lf, %lf, '*', 'color', 'black');\n",x_0,y_0);
				}
				if (mask_undefined->get(J)) {
					fprintf(ff,"plot(%lf, %lf, 'o', 'color', 'black');\n",x_0,y_0);
				}
				x_0 -= grd->stepX/REAL(2) - grd->stepX/REAL(12);

				//itoa(i, text1, 10);
				//itoa(j, text2, 10);
				//fprintf(ff,"text(%lf, %lf, '%s:%s', 'FontSize', 8);\n",x_0,y_0,text1,text2);

			}
		}
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,yM);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,yM);
		
	}

	// draw fault line
	{
		int fl_size = grd_line->first_end - grd_line->first_begin;
		int i;
		int J1, J2;
		for (i = 0; i < fl_size; i++) {
			J1 = *(grd_line->first_begin + i);
			J2 = *(grd_line->second_begin + i);
			
			REAL x, y;
			int NN = grd->getCountX();
			int MM = grd->getCountY();
			
			REAL stepX2 = grd->stepX/REAL(2);
			REAL stepY2 = grd->stepY/REAL(2);
			
			int n1,m1;
			one2two(J1, n1, m1, NN, MM);
			grd->getCoordNode(n1,m1,x,y);

			int n2,m2;
			one2two(J2, n2, m2, NN, MM);
			
			//int diff = (J2-J1);
			int diff = 0;
			if (n2 > n1)
				diff = 1;
			if (n2 < n1)
				diff = -1;
			if (m2 > m1)
				diff = NN;
			if (m2 < m1)
				diff = -NN;
			
			// right line
			if (diff == 1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x+stepX2, x+stepX2, y-stepY2, y+stepY2);
			}
			
			// left line
			if (diff == -1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x-stepX2, y-stepY2, y+stepY2);
			}
			
			// up line 
			if (diff == NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y+stepY2, y+stepY2);
			}
			
			// down line
			if (diff == -NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black');\n", 
					x-stepX2, x+stepX2, y-stepY2, y-stepY2);
			}
			
		}
	}

	// draw curv
	if (crv) {
		int i;
		REAL x0, y0, x1, y1;
		for (i = 0; i < crv->size() - 1; i++) {
			x0 = *(crv->X_begin + i);
			y0 = *(crv->Y_begin + i);
			x1 = *(crv->X_begin + i+1);
			y1 = *(crv->Y_begin + i+1);

			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','blue','LineWidth',3);\n", 
					x0, x1, y0, y1);
		}
	}

	fflush(ff);
	fclose(ff);
};


inline
void add_val(intvec * v, int n, int m, int NN, int MM) {
	if ((n < 0) || (n >= NN))
		return;

	if ((m < 0) || (m >= MM+1))
		return;

	int val = n + m*NN;
	v->push_back(val);
};

inline
void add_val_pair(intvec * v1, int n1, int m1, 
		  intvec * v2, int n2, int m2, 
		  int NN, int MM) {
	
/*	if ( ((n1 < 0) || (n2 < 0)) || 
		 ((m1 < 0) || (m2 < 0)) || 
		 ((n1 >= NN) || (n2 >= NN)) || 
		 ((m1 >= MM) || (m2 >= MM)) )
		return;
		*/
	
	int val1, val2;
	two2one(val1, n1, m1, NN, MM);
	two2one(val2, n2, m2, NN, MM);
	if ((val1 == INT_MAX) || (val2 == INT_MAX))
		return;
	
	if (v1->size() > 0) {
		int prev_val1, prev_val2;
		prev_val1 = *(v1->end()-1);
		prev_val2 = *(v2->end()-1);
		if ((val1 == prev_val1) && (val2 == prev_val2))
			return;
		
	}
	
	v1->push_back(val1);
	v2->push_back(val2);
		
};

grid_line * curv_to_grid_line(grid_line * grd_line, const curv * crv, grid * grd) {
	
	int NN = grd->getCountX();
	int MM = grd->getCountY();
	intvec * nns = new intvec; // ?

	REAL old_startX = grd->startX;
	REAL old_startY = grd->startY;
	REAL old_endX = grd->endX;
	REAL old_endY = grd->endY;

	grd->startX -= grd->stepX/REAL(2);
	grd->startY -= grd->stepY/REAL(2);
	grd->endX += grd->stepX/REAL(2);
	grd->endY += grd->stepY/REAL(2);

	NN = grd->getCountX();
	MM = grd->getCountY();

	bool closed = false;
	if ( (*(crv->X_begin) == *(crv->X_end-1)) && (*(crv->Y_begin) == *(crv->Y_end-1)) )
		closed = true;
	
	// using modified brezengham algorithm
	int qq;
	REAL X2, X1, Y2, Y1;
		
	for (qq = 0; qq < crv->size()-1; qq++) {
		X1 = *(crv->X_begin + qq);
		X2 = *(crv->X_begin + qq + 1);
		Y1 = *(crv->Y_begin + qq);
		Y2 = *(crv->Y_begin + qq + 1);
		
		int x1 = grd->get_i(X1);
		int x2 = grd->get_i(X2);
		int y1 = grd->get_j(Y1);
		int y2 = grd->get_j(Y2);
			
		int dx, dy, i1, i2, i, kx, ky;
		int d;      // "residual" 
		int x, y;
		int flag;
			
		dy = y2 - y1;
		dx = x2 - x1;
		REAL DY = Y2-Y1;
		REAL DX = X2-X1;
		
		if (dx == 0 && dy == 0) { // only one point
			add_val(nns, x1, y1, NN, MM);
			continue;
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
			
			grd->getCoordNode(x,y,p_x,p_y);
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
				REAL X_0 = grd->getCoordNodeX(x_0);
				REAL X_1 = grd->getCoordNodeX(x_1);
				REAL Y_0 = grd->getCoordNodeY(y_0);
				REAL Y_1 = grd->getCoordNodeY(y_1);
				
				if (flag) {
					
					if (fabs( DY*(X_0-X1) + DX*(Y1-Y_1) ) - fabs( DY*(X_1-X1) + DX*(Y1-Y_0)) < 0) {
						x -= kx;
						y += ky;
						grd->getCoordNode(x,y,p_x,p_y);
						add_val(nns, x, y, NN, MM);
						x += kx;
					} else {
						grd->getCoordNode(x,y,p_x,p_y);
						add_val(nns, x, y, NN, MM);
						y += ky; 
					}
					
				} else {
					
					if (fabs( DX*(Y_0-Y1) + DY*(X1-X_1) ) - fabs( DX*(Y_1-Y1) + DY*(X1-X_0)) < 0) {
						y -= ky;
						x += kx;
						grd->getCoordNode(x,y,p_x,p_y);
						add_val(nns, x, y, NN, MM);
						y += ky;
					} else {
						grd->getCoordNode(x,y,p_x,p_y);
						add_val(nns, x, y, NN, MM);
						x += kx;
					}
				}
				
				d += i2;
			}
		}

		grd->getCoordNode(x,y,p_x,p_y);
		add_val(nns, x, y, NN, MM); // last point
		
	}

	grd->startX = old_startX;
	grd->startY = old_startY;
	grd->endX = old_endX;
	grd->endY = old_endY;
	int NNN = NN;
	int MMM = MM;
	NN = grd->getCountX();
	MM = grd->getCountY();

	if (nns->size() == 0) {
		delete nns;
		return grd_line;
	}

	// repeats deletions
	int old_size = nns->size();
	int write_pos = 0;
	for (qq = 1; qq < nns->size(); qq++) {
		if ( (*nns)(write_pos) != (*nns)(qq) ) {
			write_pos++;
			(*nns)(write_pos) = (*nns)(qq);
		}
	}
	nns->resize(write_pos+1);

	intvec * grd1 = new intvec();
	intvec * grd2 = new intvec();
	grd1->reserve(nns->size());
	grd2->reserve(nns->size());

	int n1, m1, n2, m2, pos1, pos2;

	int i;
	for (i = 0; i < nns->size()-1; i++) {

		pos1 = (*nns)(i);
		n1 = pos1 % NNN;
		m1 = (pos1 - n1)/NNN;	

		pos2 = (*nns)(i+1);
		n2 = pos2 % NNN;
		m2 = (pos2 - n2)/NNN;

		int max_n = MAX(n1, n2);
		int min_m = MIN(m1, m2);
		
		if (n2 != n1) { // horizontal line
			add_val_pair(grd1, max_n-1, min_m, 
				grd2, max_n-1, min_m-1,
				NN,MM);
		} else { // vertical line
			add_val_pair(grd1, max_n, min_m, 
				grd2, max_n-1, min_m,
				NN,MM);
		}
		
	}

	int * first_begin = grd1->ref_begin();
	int * first_end = grd1->end();
	int * second_begin = grd2->begin();
	int * second_end = grd2->end();

	grd1->drop_data();
	grd2->drop_data();
	
	delete nns;  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nns = NULL;
	delete grd1;
	delete grd2;

	if (!grd_line) {
		grd_line = new grid_line(first_begin, first_end,
		                         second_begin, second_end);
	} else {
		grd_line->add(first_begin, first_end,
			      second_begin,  second_end);
	}

	/*

	FILE * ff = fopen("c:\\qqq.m","w+");
	fprintf(ff,"hold on\n");

		// draw source line
	{
		int line_size = crv->size();
		int i;
		REAL x1, y1, x2, y2;
		for (i = 0; i < line_size-1; i++) {
			x1 = *(crv->X_begin+i);
			x2 = *(crv->X_begin+i+1);
			y1 = *(crv->Y_begin+i);
			y2 = *(crv->Y_begin+i+1);
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','blue','LineWidth',3);\n",x1,x2,y1,y2);
			fprintf(ff,"plot(%lf, %lf,'o');\n",x1,y1);
			fprintf(ff,"plot(%lf, %lf,'o');\n",x2,y2);
		}
	}

	// draw brez
	
	if (nns)
	{
		int i;
		int x, y, pos;
		int x2, y2, pos2;
		char text[6];
		for (i = 0; i < nns->size()-1; i++) {
			pos = (*nns)(i);
			x = pos % NN;
			y = (pos - x)/NN;
			pos2 = (*nns)(i+1);
			x2 = pos2 % NN;
			y2 = (pos2 - x2)/NN;

			REAL X, Y;
			grd->getCoordNode(x,y,X,Y);
			REAL X2, Y2;
			grd->getCoordNode(x2,y2,X2,Y2);
			fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",X,Y);
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','black','LineWidth',4);\n",X,X2,Y,Y2);
			//itoa(i , text, 10);
			//fprintf(ff,"text(%lf, %lf, '%s');\n",X,Y,text);

		}
	}

	// draw grid
	{
		int i;
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
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		x_0 = x0 - stepX;
		x_1 = xN + stepX;
		for (i = 0; i < grd->getCountY()+1; i++) {
			y_0 = grd->getCoordNodeY(i)-stepY;
			y_1 = y_0;//grd->getCoordNodeY(i+1)+stepY;
			fprintf(ff,"plot([%lf %lf],[%lf %lf],'color','cyan');\n",x_0,x_1,y_0,y_1);
		}
		
		char text[6];
		int j;
		for (j = 0; j < grd->getCountY(); j++) {
			for (i = 0; i < grd->getCountX(); i++) {
				x_0 = grd->getCoordNodeX(i);
				y_0 = grd->getCoordNodeY(j);
				itoa(i + j*NN, text, 10);
				//if ( (j > 40) && (i > 171))
				//fprintf(ff,"text(%lf, %lf, '%s');\n",x_0,y_0,text);

			}
		}
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",x0,yM);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,y0);
		//fprintf(ff,"plot(%lf, %lf,'*','color','black');\n",xN,yM);
		
	}
	

	// draw fault line
	{
		int fl_size = grd_line->first_end - grd_line->first_begin;
		int i;
		int J1, J2;
		for (i = 0; i < fl_size; i++) {
			J1 = *(grd_line->first_begin + i);
			J2 = *(grd_line->second_begin + i);
			
			REAL x, y;
			int NN = grd->getCountX();
			
			REAL stepX2 = grd->stepX/REAL(2);
			REAL stepY2 = grd->stepY/REAL(2);
			
			int n = J1 % NN;
			int m = (J1 - n)/NN;
			
			grd->getCoordNode(n,m,x,y);
			
			int diff = (J2-J1);
			
			// right line
			if (diff == 1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black','LineWidth',3);\n", 
					x+stepX2, x+stepX2, y-stepY2, y+stepY2);
			}
			
			// left line
			if (diff == -1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black','LineWidth',3);\n", 
					x-stepX2, x-stepX2, y-stepY2, y+stepY2);
			}
			
			// up line 
			if (diff == NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black','LineWidth',3);\n", 
					x-stepX2, x+stepX2, y+stepY2, y+stepY2);
			}
			
			// down line
			if (diff == -NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','black','LineWidth',3);\n", 
					x-stepX2, x+stepX2, y-stepY2, y-stepY2);
			}
			
		}
	}
	
	fflush(ff);

	// draw fault line
	{
		int fl_size = grd_line->first_end - grd_line->first_begin;
		int i;
		int J1, J2;
		for (i = 0; i < fl_size; i++) {
			J1 = *(grd_line->first_begin + i);
			J2 = *(grd_line->second_begin + i);
			
			REAL x, y;
			int NN = grd->getCountX();
			
			REAL stepX2 = grd->stepX/REAL(2);
			REAL stepY2 = grd->stepY/REAL(2);
			
			int n = J1 % NN;
			int m = (J1 - n)/NN;
			
			grd->getCoordNode(n,m,x,y);
			
			int diff = (J2-J1);
			
			// right line
			if (diff == 1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','red','LineWidth',3);\n", 
					x+stepX2, x+stepX2, y-stepY2, y+stepY2);
			}
			
			// left line
			if (diff == -1) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','red','LineWidth',3);\n", 
					x-stepX2, x-stepX2, y-stepY2, y+stepY2);
			}
			
			// up line 
			if (diff == NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','red','LineWidth',3);\n", 
					x-stepX2, x+stepX2, y+stepY2, y+stepY2);
			}
			
			// down line
			if (diff == -NN) {
				fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','red','LineWidth',3);\n", 
					x-stepX2, x+stepX2, y-stepY2, y-stepY2);
			}
			
		}
	}
	
	fflush(ff);
	fclose(ff);
	*/
	
	return grd_line;

};

}; // namespace surfit;


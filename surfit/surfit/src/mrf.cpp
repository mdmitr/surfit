
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
#include <memory.h>
#include "mrf.h"
#include "func_internal.h"
#include "fileio.h"
#include "vec.h"

namespace surfit {

void _decomp1d(const REAL * X_begin, const REAL * X_end, 
	       REAL * Xa_begin,      REAL * Xa_end,
	       REAL * Xd_begin,      REAL * Xd_end,
	       bool enlarge)
{
	REAL s = REAL(0.5);
	
	const REAL * pX = X_begin;
	REAL * pXa = Xa_begin;
	REAL * pXd = Xd_begin;
	REAL * ptr_Xa_end = enlarge ? (Xa_end-1) : Xa_end;
	REAL * ptr_Xd_end = enlarge ? (Xd_end-1) : Xd_end;

	while (pXa != ptr_Xa_end) {
		*pXa = (*pX + *(pX+1))*s;
		pXa++;
		pX += 2;
	};

	pX = X_begin;
	while (pXd != ptr_Xd_end) {
		*pXd = (*pX - *(pX+1))*s;
		pXd++;
		pX += 2;
	};

	if (enlarge) {
		*(Xa_end-1) = *(X_end-1);
		*(Xd_end-1) = 0;
	}
};

void _recons1d(REAL * X_begin,        REAL * X_end, 
	       const REAL * Xa_begin, const REAL * Xa_end,
	       const REAL * Xd_begin, const REAL * Xd_end,
	       bool enlarge)
{
	
	REAL * pX = X_begin;
	const REAL * pXa = Xa_begin;
	const REAL * pXd = Xd_begin;
	REAL * p_X_end = enlarge ? (X_end-1) : X_end;

	while (pX != p_X_end) {
		*pX = (*pXa + *pXd);
		pX++;
		*pX = (*pXa - *pXd);
		pXa++;
		pXd++;
		pX++;
	};

	if (enlarge)
		*pX = *(Xa_end-1);

};

void _decomp2d(REAL *& S_begin,  REAL *  S_end,
	       REAL *& Xa_begin, REAL *& Xa_end,
	       REAL *& Xd_begin, REAL *& Xd_end,
	       REAL *& Xh_begin, REAL *& Xh_end,
	       REAL *& Xv_begin, REAL *& Xv_end,
	       int N,
	       bool enlarge_X,
	       bool enlarge_Y)
{
	// N - количество элементов в строке
	// M - количество элементов в столбце
	// NM - общее кол-во элементов
	int NM = S_end-S_begin;
	int M = NM/N;

	int i, j;

	// dangerous!!!
	// Нужно заквадратить!
	if (enlarge_X) {
		int size_N = enlarge_X ? (N+1) : N;
		S_begin = (REAL*)realloc( S_begin, sizeof(REAL)*size_N*M );
		for (j = M-1; j >= 0; j--) {
			memcpy(S_begin + j*N + j, S_begin + j*N, N*sizeof(REAL));
			*(S_begin + j*N + j + N) = *(S_begin + j*N + j + N -1);
		}
		enlarge_X = false;
		N = size_N;
	}
	if (enlarge_Y) {
		int size_M = enlarge_Y ? (M+1) : M;
		S_begin = (REAL*)realloc( S_begin, sizeof(REAL)*N*size_M );
		memcpy( S_begin + (size_M-1)*N, S_begin + (size_M-2)*N, N*sizeof(REAL) );
		M = size_M;
		enlarge_Y = false;
	}

	vec * temp = new vec(N,0,0);   // do not fill this vector
	vec * xa   = new vec(N/2,0,0); // do not fill this vector
	vec * xd   = new vec(N/2,0,0); // do not fill this vector

	vec * A = new vec( S_begin, S_begin+(N*M/2) );
	vec * D = new vec( N*M/2 );
	
	int cnt = 0;
	for (j = 0; j < M; j++) {
	
		memcpy(temp->begin(), S_begin+j*N, sizeof(REAL)*N);
				
		_decomp1d(temp->begin(), temp->end(),
			      xa->begin(), xa->end(),
				  xd->begin(), xd->end(),
				  false);

		memcpy(A->begin()+cnt, xa->begin(), xa->size()*sizeof(REAL));
		memcpy(D->begin()+cnt, xd->begin(), xd->size()*sizeof(REAL));
		
		cnt += N/2;
		
	};

	// Разбиваем A - получаем a и v
	REAL * a_temp = S_begin+(N*M/2);
	REAL * v_temp = S_begin+(N*M/2)+(N*M/4);

	temp->resize(M,0,0);
	xa->resize(M/2,0,0);
	xd->resize(M/2,0,0);
	
	for (i = 0; i < N/2; i++) {
		
		int j;
		for (j = 0; j < M; j++)
			(*temp)(j) = *( A->begin() + i + j*N/2 );
		
		_decomp1d(temp->begin(), temp->end(),
			      xa->begin(), xa->end(),
				  xd->begin(), xd->end(),
				  false);

		// xa -> X_a
		vec::iterator it;
		int cnt_a = 0;
		for (it = xa->begin(); it != xa->end(); it++) { 
			*(a_temp + i + cnt_a*N/2 ) = *it;
			cnt_a++;
		}

		// xd -> X_v
		int cnt_v = 0;
		for (it = xd->begin(); it != xd->end(); it++) { 
			*(v_temp + i + cnt_v*N/2) = *it;
			cnt_v++;
		}

	}

	A->data = NULL;
	delete A;

	// Разбиваем Xd - Получаем X_h и X_d
	REAL * X_h_temp = S_begin;
	REAL * X_d_temp = S_begin+(N*M/4);

	for (i = 0; i < N/2; i++) {

		int j;
		for (j = 0; j < M; j++)
			(*temp)(j) = *( D->begin() + i + j*N/2 );

		_decomp1d(temp->begin(), temp->end(),
			      xa->begin(), xa->end(),
				  xd->begin(), xd->end(),
				  false);
		
		// xa -> X_h
		vec::iterator it;
		int cnt_h = 0;
		for (it = xa->begin(); it != xa->end(); it++) { 
			*(X_h_temp + i + cnt_h*N/2 ) = *it;
			cnt_h++;
		}

		// xd -> X_d
		int cnt_d = 0;
		for (it = xd->begin(); it != xd->end(); it++) { 
			*(X_d_temp + i + cnt_d*N/2) = *it;
			cnt_d++;
		}
		
	}

	delete D;

	Xv_begin = (REAL*)malloc(sizeof(REAL)*N*M/4);
	Xv_end = Xv_begin + (N*M/4);
	memcpy(Xv_begin,v_temp,sizeof(REAL)*N*M/4);

	S_begin = (REAL*)realloc(S_begin, (N*M/2 + N*M/4)*sizeof(REAL));
	a_temp = S_begin+(N*M/2);

	Xa_begin = (REAL*)malloc(sizeof(REAL)*N*M/4);
	Xa_end = Xa_begin + (N*M/4);
	memcpy(Xa_begin,a_temp,sizeof(REAL)*N*M/4);

	S_begin = (REAL*)realloc(S_begin, N*M/2*sizeof(REAL));
	X_d_temp = S_begin+(N*M/4);

	Xd_begin = (REAL*)malloc(sizeof(REAL)*N*M/4);
	Xd_end = Xd_begin + (N*M/4);
	memcpy(Xd_begin,X_d_temp,sizeof(REAL)*N*M/4);

	S_begin = (REAL*)realloc(S_begin, N*M/4*sizeof(REAL));
	Xh_begin = S_begin;
	Xh_end = Xh_begin + (N*M/4);
		
	S_begin = NULL;
	S_end = NULL;

	delete temp;
	delete xa;
	delete xd;

};

int calc_ptr(int i, int j, int N) {
	return i + j*N;
}

bool _recons2d(REAL *& X_begin,       REAL *& X_end,
	       const REAL *  a_begin, const REAL *  a_end,
	       const REAL *  d_begin, const REAL *  d_end,
	       const REAL *  h_begin, const REAL *  h_end,
	       const REAL *  v_begin, const REAL *  v_end,
	       int N,
	       bool enlarge_X,
	       bool enlarge_Y)
{

	// N - количество элементов в строке
	// M - количество элементов в столбце
	// NM - общее кол-во элементов
	int NM = a_end-a_begin;
	int M = NM/N;

	int newN = 2*N;
	int oldN = 2*N;
	
	if (enlarge_X)
		newN--;
	
	int newM = 2*M;
	
	if (enlarge_Y)
		newM--;
	
	int newNM = newN*newM;
	
	X_begin = (REAL*)malloc(newNM*sizeof(REAL));
	X_end = X_begin + newNM;
	if (!X_begin) {
		writelog(SURFIT_ERROR,"_recons2d : not enought memory");
		return false;
	}
	
	int cur_row = 0;
	int cur_col = 0;
	REAL * ptrX;
	int displace;
	
	// + + + +
	for (cur_col = 0; cur_col < newM; cur_col += 2) {
		for (cur_row = 0; cur_row < newN; cur_row += 2) {
			
			ptrX = X_begin + calc_ptr(cur_row,cur_col,newN);
			displace = (cur_row + cur_col*N)/2;
			*ptrX = *(a_begin + displace) + *(h_begin + displace) + *(v_begin + displace) + *(d_begin + displace);
			
		}
	}
			
	// + - + -
	for (cur_col = 0; cur_col < newM; cur_col += 2) {
		for (cur_row = 1; cur_row < newN; cur_row += 2) {

			ptrX = X_begin + calc_ptr(cur_row,cur_col,newN);
			displace = (cur_row-1 + cur_col*N)/2;
			*ptrX = *(a_begin + displace) - *(h_begin + displace) + *(v_begin + displace) - *(d_begin + displace);
			
		}
	}
			
	// + + - -
	for (cur_col = 1; cur_col < newM; cur_col += 2) {
		for (cur_row = 0; cur_row < newN; cur_row += 2) {

			ptrX = X_begin + calc_ptr(cur_row,cur_col,newN);
			displace = (cur_row + (cur_col-1)*N)/2;
			*ptrX = *(a_begin + displace) + *(h_begin + displace) - *(v_begin + displace) - *(d_begin + displace);

		}
	}

	// + - - +
	for (cur_col = 1; cur_col < newM; cur_col += 2) {
		for (cur_row = 1; cur_row < newN; cur_row += 2) {

			ptrX = X_begin + calc_ptr(cur_row,cur_col,newN);
			displace = ((cur_row-1) + (cur_col-1)*N)/2;
			*ptrX = *(a_begin + displace) - *(h_begin + displace) - *(v_begin + displace) + *(d_begin + displace);

		}
	}
			
	return true;

};

}; // namespace surfit;


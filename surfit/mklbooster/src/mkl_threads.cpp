
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

#include "mklbooster_ie.h"
#include "mklbooster.h"
#include "variables_tcl.h"
#include "threads.h"

#include <mkl_blas.h>

namespace surfit {

struct DAXPY_job : public job {

	DAXPY_job()
	{
		N = 0;
		alpha = 0;
		x = NULL;
		incx = NULL;
		y = NULL;
		incy = NULL;
	}

	void set(int iN, double ialpha, double * ix, int * iincx, double * iy, int * iincy)
	{
		N = iN;
		alpha = ialpha;
		x = ix;
		incx = iincx;
		y = iy;
		incy = iincy;
	}

	virtual void do_job()
	{
		DAXPY(&N, &alpha, x, incx, y, incy);
	}

	int N;
	double alpha;
	double * x;
	int * incx;
	double * y;
	int * incy;
};

DAXPY_job DAXPY_jobs[MAX_CPU];

void threaded_DAXPY(int *n,double *alpha,double *x,int *incx,double *y,int *incy)
{
	size_t i;
	unsigned int step = *n/(cpu);
	unsigned int ost = *n % (cpu);
	unsigned int J_from = 0;
	unsigned int J_to = 0;
	for (i = 0; i < cpu; i++) {
		J_to = J_from + step;
		if (i == 0)
			J_to += ost;
		
		DAXPY_job & f = DAXPY_jobs[i];
		f.set(J_to-J_from, *alpha, x+J_from, incx, y+J_from, incy);
		set_job(&f, i);
		J_from = J_to;
	}
	
	do_jobs();
};

struct DDOT_job : public job {

	DDOT_job()
	{
		N = 0;
		x = NULL;
		incx = NULL;
		y = NULL;
		incy = NULL;
		res = 0;
	}

	void set(int iN, double * ix, int * iincx, double * iy, int * iincy)
	{
		N = iN;
		x = ix;
		incx = iincx;
		y = iy;
		incy = iincy;
	}

	virtual void do_job()
	{
		res = DDOT(&N, x, incx, y, incy);
	}

	int N;
	double * x;
	int * incx;
	double * y;
	int * incy;
	double res;
};

DDOT_job DDOT_jobs[MAX_CPU];

double threaded_DDOT(int *n,double *x,int *incx,double *y,int *incy)
{
	size_t i;
	unsigned int step = *n/(cpu);
	unsigned int ost = *n % (cpu);
	unsigned int J_from = 0;
	unsigned int J_to = 0;
	for (i = 0; i < cpu; i++) {
		J_to = J_from + step;
		if (i == 0)
			J_to += ost;
		
		DDOT_job & f = DDOT_jobs[i];
		f.set(J_to-J_from, x+J_from, incx, y+J_from, incy);
		set_job(&f, i);
		J_from = J_to;
	}
	
	do_jobs();
	
	double res = 0;
	for (i = 0; i < cpu; i++) {
		DDOT_job & f = DDOT_jobs[i];
		res += f.res;
	}
	return res;
};

struct DSCAL_job : public job {

	DSCAL_job()
	{
		N = 0;
		alpha = 0;
		x = NULL;
		incx = NULL;
	}

	void set(int iN, double ialpha, double * ix, int * iincx)
	{
		N = iN;
		alpha = ialpha;
		x = ix;
		incx = iincx;
	}

	virtual void do_job()
	{
		DSCAL(&N, &alpha, x, incx);
	}

	int N;
	double alpha;
	double * x;
	int * incx;
};

DSCAL_job DSCAL_jobs[MAX_CPU];

void threaded_DSCAL(int *n,double *alpha,double *x,int *incx)
{
	size_t i;
	unsigned int step = *n/(cpu);
	unsigned int ost = *n % (cpu);
	unsigned int J_from = 0;
	unsigned int J_to = 0;
	for (i = 0; i < cpu; i++) {
		J_to = J_from + step;
		if (i == 0)
			J_to += ost;
		
		DSCAL_job & f = DSCAL_jobs[i];
		f.set(J_to-J_from, *alpha, x+J_from, incx);
		set_job(&f, i);
		J_from = J_to;
	}
	
	do_jobs();
};

}; // namespace surfit;


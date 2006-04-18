
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

#ifndef __surfit_matrD1__
#define __surfit_matrD1__

#include "matr.h"
#include <vector>

namespace surfit {

class grid_line;
class bitvec;

/*! \class matrD1
    \brief matrix to serve \ref completer functional for \ref completer::D1 > 0
*/
class SURFIT_EXPORT matrD1 : public matr {
public:

	/*! default constructor (use it very carefully)
	*/
	matrD1() {};

	/*! constructor
	    \param iN matrix size
	    \param iNN amount of cols in grid
	    \param ihx grid step by X
	    \param ihy grid step by Y
	    \param imask_solved bit-mask with solved cells
	    \param imask_undefined bit-mask with undefined cells
	    \param ifault grid based fault line
	*/
	matrD1(int iN, int iNN, 
	       REAL ihx, REAL ihy,
	       const bitvec * imask_solved,
	       const bitvec * imask_undefined,
	       grid_line * ifault);

	//! destructor
	virtual ~matrD1();

	REAL element_at(int i, int j, int * next_j = NULL) const;
	REAL element_at_transposed(int i, int j, int * next_j = NULL) const;
	REAL at(int i, int j, int * next_j = NULL) const;
	REAL at_transposed(int i, int j, int * next_j = NULL) const;
	REAL mult_line(int J, const REAL * b_begin, const REAL * b_end);
	REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end);
		
	virtual long cols() const;
	virtual long rows() const;

	REAL norm() const;

	virtual void skip(int i, int j);

protected:

	//! matrix size
	int N;
	//! cols in grid
	int NN; 
	//! rows in grid
	int MM; 

	//! square of grid step by X
	REAL hx2;
	//! square of grid step by Y
	REAL hy2;

	//! hy/hx
	REAL _hx2;
	//! hx/hy
	REAL _hy2;
	
	//! grid based fault line
	grid_line * fault;

	//! makes mask with fault, solved and undefined taken
	void make_mask(const bitvec * imask_solved, const bitvec * imask_undefined);

	//! bit-mask
	bitvec * mask;
	bitvec * mask_solved_undefined;

	//! calls from matrator()
	REAL matrator_serve(int i, int j, bool * b, int * next_j) const;

};

/*! \class matrD1_rect
    \brief matrix to serve \ref trend functional for trend::D1 > 0
*/
class SURFIT_EXPORT matrD1_rect : public matr_rect, public matrD1 {
public:
	/*! constructor
	    \param iN number of matrix elements 
	    \param iNN number of matrix elements in row
	    \param ihx grid step by X
	    \param ihy grid step by Y
	    \param x_from left index of the rect
	    \param x_to right index of the rect
	    \param y_from bottom index of the rect
	    \param y_to top index of the rect
	    \param imask_solved bit-mask with solved cells
	    \param imask_undefined bit-mask with undefined cells
	    \param ifault grid based fault line
	*/
	matrD1_rect(int iN, int iNN, 
		    REAL ihx, REAL ihy,
		    int x_from, int x_to, int y_from, int y_to,
		    const bitvec * imask_solved,
		    const bitvec * imask_undefined,
		    grid_line * ifault);

	//! A destructor
	virtual ~matrD1_rect() {};

	REAL element_at(int i, int j, int * next_j = NULL) const;
	REAL element_at_transposed(int i, int j, int * next_j = NULL) const;
	REAL at(int i, int j, int * next_j = NULL) const;
	REAL at_transposed(int i, int j, int * next_j = NULL) const;
	REAL mult_line(int J, const REAL * b_begin, const REAL * b_end);
	REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end);

	virtual long cols() const;
	virtual long rows() const;

	REAL norm() const;

protected:

	void make_mask(const bitvec * imask_solved, const bitvec * imask_undefined);
	
	//! matrix size 1
	int N_cols; 

	//! matrix size 2
	int N_rows; 

	//! cols in matrix
	int matrNN; 

	//! rows in matrix
	int matrMM; 

};

}; // namespace surfit;

#endif


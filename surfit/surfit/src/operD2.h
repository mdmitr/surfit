
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

#ifndef __surfit_operD2__
#define __surfit_operD2__

#include "oper.h"

#include <vector>

namespace surfit {

class grid_line;
class bitvec;

/*! \class operD2
    \brief matrix to serve \ref completer functional for \ref completer::D2 > 0
*/
class SURFIT_EXPORT operD2 : public oper {
public:

	/*! default constructor (use it very carefully)
	*/
	operD2() {};

	/*! constructor
	    \param iN matrix size
	    \param iNN amount of cols in grid
	    \param ihx grid step by X
	    \param ihy grid step by Y
	    \param imask_solved bit-mask with solved cells
	    \param imask_undefined bit-mask with undefined cells
	    \param ifault grid based fault line
	*/
	operD2(int iN, int iNN, 
	       REAL ihx, REAL ihy,
	       bitvec * imask_solved,
	       bitvec * imask_undefined,
	       grid_line * ifault);
 
	virtual ~operD2();

	REAL operator()(int i, int j, int * next_j = NULL) const;
	REAL at(int i, int j, int * next_j = NULL) const;
	REAL mult_line(int J, const REAL * b_begin, const REAL * b_end) const;
	REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const;

	virtual long cols() const;
	virtual long rows() const;

	REAL norm() const;

protected:

	//! matrix size
	int N;
	//! cols in grid
	int NN; 
	//! rows in geometry
	int MM;

	//! grid step by X
	REAL hx4;
	//! grid step by Y
	REAL hy4;

	//! = \f$ \frac{h_y^2}{h_x^2} \f$
	REAL _hx4;
	//! = \f$ \frac{h_x^2}{h_y^2} \f$
	REAL _hy4;
	//!  = 1
	REAL _hxy4;

	//! numbers of elements in row to skip in mult_line function (solved)
	bitvec * mask_solved;
	//! numbers of elements in row to skip in mult_line function (undefined)
	bitvec * mask_undefined;
	//! grid based fault line
	grid_line * fault;

	//! makes mask with fault, solved and undefined taken
	void make_mask();

	//! bit-mask
	bitvec * mask;

	//! calls from operator()
	REAL operator_serve(int i, int j,
			    bool first_x, bool second_x, bool third_x,
			    bool first_xx, bool second_xx,
			    bool first_yy, bool second_yy,
			    bool first_y, bool second_y, bool third_y,
			    int * next_j) const;

};


/*! \class operD2_rect
    \brief matrix to serve \ref trend functional for trend::D2 > 0
*/
class operD2_rect : public operD2 {
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
	operD2_rect(int iN, int iNN, 
		    REAL ihx, REAL ihy,
		    int x_from, int x_to, int y_from, int y_to,
		    bitvec * imask_solved,
		    bitvec * imask_undefined,
		    grid_line * ifault);

	//! A destructor
	virtual ~operD2_rect() {};

	REAL operator()(int i, int j, int * next_j = NULL) const;
	REAL at(int i, int j, int * next_j = NULL) const;
	REAL mult_line(int J, const REAL * b_begin, const REAL * b_end) const;
	REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const;

	virtual long cols() const;
	virtual long rows() const;

protected:

	void make_mask();
	
	//! matrix size 1
	int N_cols; 

	//! matrix size 2
	int N_rows; 

	//! cols in matrix
	int matrNN; 

	//! rows in matrix
	int matrMM; 

	//! left index of the rect
	int x_from;
	//! right index of the rect
	int x_to;
	//! bottom index of the rect
	int y_from;
	//! top index of the rect
	int y_to;

};

}; // namespace surfit

#endif


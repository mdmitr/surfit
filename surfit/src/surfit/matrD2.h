
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

#ifndef __surfit_matrD2__
#define __surfit_matrD2__

#include "matr.h"

#include <vector>

namespace surfit {

class grid_line;
class bitvec;

/*! \class matrD2
    \brief matrix to serve \ref completer functional for \ref completer::D2 > 0
*/
class SURFIT_EXPORT matrD2 : public matr {
public:

	/*! default constructor (use it very carefully)
	*/
	matrD2() {};

	/*! constructor
	    \param iN matrix size
	    \param iNN amount of cols in grid
	    \param ihx grid step by X
	    \param ihy grid step by Y
	    \param imask_solved bit-mask with solved cells
	    \param imask_undefined bit-mask with undefined cells
	    \param ifault grid based fault line
	*/
	matrD2(size_t iN, size_t iNN, 
	       REAL ihx, REAL ihy,
	       const bitvec * imask_solved,
	       const bitvec * imask_undefined,
	       grid_line * ifault);
 
	virtual ~matrD2();

	REAL element_at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL element_at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);
	REAL mult_transposed_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);

	virtual size_t cols() const;
	virtual size_t rows() const;

	REAL norm() const;

	virtual void skip(size_t i, size_t j);

protected:

	//! matrix size
	size_t N;
	//! cols in grid
	size_t NN; 
	//! rows in geometry
	size_t MM;

	//! grid step by X power of 4
	REAL hx4;
	//! grid step by Y power of 4
	REAL hy4;

	//! = \f$ \frac{h_y^2}{h_x^2} \f$
	REAL _hx4;
	//! = \f$ \frac{h_x^2}{h_y^2} \f$
	REAL _hy4;
	//!  = 1
	REAL _hxy4;

	//! grid based fault line
	grid_line * fault;

	//! makes mask with fault, solved and undefined taken
	void make_mask(const bitvec * imask_solved, const bitvec * imask_undefined);

	//! bit-mask
	bitvec * mask;
	bitvec * mask_solved_undefined;

	//! calls from matrator()
	REAL matrator_serve(size_t i, size_t j, bool * b,
			    size_t * next_j) const;

};


/*! \class matrD2_rect
    \brief matrix to serve \ref trend functional for trend::D2 > 0
*/
class matrD2_rect : public matr_rect, public matrD2 {
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
	matrD2_rect(size_t iN, size_t iNN, 
		    REAL ihx, REAL ihy,
		    size_t x_from, size_t x_to, size_t y_from, size_t y_to,
		    const bitvec * imask_solved,
		    const bitvec * imask_undefined,
		    grid_line * ifault);

	//! A destructor
	virtual ~matrD2_rect() {};

	REAL element_at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL element_at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);
	REAL mult_transposed_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);

	virtual size_t cols() const;
	virtual size_t rows() const;

	REAL norm() const;

protected:

	void make_mask(const bitvec * imask_solved, const bitvec * imask_undefined);
	
	//! matrix size 1
	size_t N_cols; 

	//! matrix size 2
	size_t N_rows; 

	//! cols in matrix
	size_t rectNN; 

	//! rows in matrix
	size_t rectMM; 

};

}; // namespace surfit

#endif


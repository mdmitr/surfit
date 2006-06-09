
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

#ifndef __surfit_matrD1_aniso__
#define __surfit_matrD1_aniso__

#include "matr.h"
#include <vector>

namespace surfit {

class grid_line;
class bitvec;

/*! \class matrD1_aniso
    \brief matrix to serve \ref completer functional for \ref completer::D1 > 0 and angle != 0, w != 1
*/
class SURFIT_EXPORT matrD1_aniso : public matr {
public:

	/*! default constructor (use it very carefully)
	*/
	matrD1_aniso() {};

	/*! constructor
	    \param iN matrix size
	    \param iNN amount of cols in grid
	    \param ihx grid step by X
	    \param ihy grid step by Y
	    \param imask_solved bit-mask with solved cells
	    \param imask_undefined bit-mask with undefined cells
	    \param ifault grid based fault line
	*/
	matrD1_aniso(size_t iN, size_t iNN, 
	       REAL ihx, REAL ihy,
	       const bitvec * imask_solved,
	       const bitvec * imask_undefined,
	       grid_line * ifault,
	       REAL iangle, REAL iw);

	//! destructor
	virtual ~matrD1_aniso();

	REAL element_at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL element_at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL mult_line(size_t J, const REAL * b_begin, const REAL * b_end);
	REAL mult_transposed_line(size_t J, const REAL * b_begin, const REAL * b_end);
		
	virtual size_t cols() const;
	virtual size_t rows() const;

	REAL norm() const;

	virtual void skip(size_t i, size_t j);

protected:

	//! matrix size
	size_t N;
	//! cols in grid
	size_t NN; 
	//! rows in grid
	size_t MM; 

	//! square of grid step by X
	REAL hx2;
	//! square of grid step by Y
	REAL hy2;

	//! hy/hx
	REAL _hx2;
	//! hx/hy
	REAL _hy2;

	// anisotropy angle
	REAL angle;
	// anisotropy factor
	REAL w;

	REAL wmxx, wmxy, wmyy;
	REAL mxx, mxy, myy;
		
	//! grid based fault line
	grid_line * fault;

	//! makes mask with fault, solved and undefined taken
	void make_mask(const bitvec * imask_solved, const bitvec * imask_undefined);

	//! bit-mask
	bitvec * mask;
	bitvec * mask_solved_undefined;

	//! calls from matrator()
	REAL matrator_serve(size_t i, size_t j, bool * b, size_t * next_j) const;

};

}; // namespace surfit;

#endif


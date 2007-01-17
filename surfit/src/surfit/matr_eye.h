
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

#ifndef __surfit_matr_eye__
#define __surfit_matr_eye__

#include "matr.h"

namespace surfit {

class bitvec;

class SURFIT_EXPORT matr_eye : public matr {
public:
	//! constructor
	matr_eye(REAL ival, size_t iN, bitvec *& imask,
		 const bitvec * imask_solved, const bitvec * imask_undefined);

	//! A destructor
	virtual ~matr_eye();

	REAL element_at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL element_at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at_transposed(size_t i, size_t j, size_t * next_j = NULL) const;
	
	REAL mult_line(size_t J, const REAL * b_begin, const REAL * b_end);
	REAL mult_transposed_line(size_t J, const REAL * b_begin, const REAL * b_end);
	
	virtual size_t cols() const;
	virtual size_t rows() const;

	REAL norm() const;

protected:

	size_t N;
	REAL val;
	bitvec * mask;
	const bitvec * mask_solved;
	const bitvec * mask_undefined;

};


}; // namespace surfit;

#endif



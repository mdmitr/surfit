
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

#ifndef __surfit_matr_onesrow__
#define __surfit_matr_onesrow__

#include "matr.h"

namespace surfit {

class bitvec;

//! matrix that filled with the same value
class SURFIT_EXPORT matr_onesrow : public matr {
public:
	//! constructor
	matr_onesrow(REAL ival, size_t iN, bitvec *& imask);

	//! A destructor
	virtual ~matr_onesrow();

	virtual REAL element_at(size_t i, size_t j, size_t * next_j = NULL) const;
	virtual REAL at(size_t i, size_t j, size_t * next_j = NULL) const;
	
	virtual REAL mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);
	virtual void call_after_mult();
	
	virtual size_t cols() const;
	virtual size_t rows() const;

	virtual REAL norm() const;

protected:

	//! matrix size
	size_t N;

	//! matrix value
	REAL val;

	//! mask for applying matrix
	bitvec * mask;

	//! data for optimization
	extvec::const_iterator * prev_b_begin;
	
	//! data for optimization
	REAL prev_val;

};

//! matrix with the same rows
class SURFIT_EXPORT matr_row : public matr {
public:
	//! constructor
	matr_row(size_t iN,
	         bitvec * imask,
		 extvec * ivalues);

	//! A destructor
	virtual ~matr_row();

	virtual REAL element_at(size_t i, size_t j, size_t * next_j = NULL) const;
	virtual REAL at(size_t i, size_t j, size_t * next_j = NULL) const;
	
	virtual REAL mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);
	virtual void call_after_mult();
	
	virtual size_t cols() const;
	virtual size_t rows() const;

	virtual REAL norm() const;

protected:

	//! matrix size
	size_t N;

	//! values for rows
	extvec * values;

	//! mask for applying matrix
	bitvec * mask;

	//! data for optimization
	extvec::const_iterator * prev_b_begin;

	//! data for optimization
	REAL prev_val;

};

}; // namespace surfit;

#endif


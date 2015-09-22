
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

#ifndef __surfit_matr_cntrs__
#define __surfit_matr_cntrs__

#include "matr.h"
#include <vector>

namespace surfit {

class bitvec;

//! special struct for \ref matr_rect class
struct cntr_rec {
	//! first cell number, which identifies cell boundary
	size_t pos1;
	//! second cell number, which identifies cell boundary
	size_t pos2;
	
	//! see matr_sect.tex for details
	REAL sum1;
	//! see matr_sect.tex for details
	REAL sum2;
	//! see matr_sect.tex for details
	REAL sum3;
	//! see matr_sect.tex for details
	REAL sum4;
	//! see matr_sect.tex for details
	REAL sum5;
};

//! special struct for \ref matr_rect class
struct fast_rec {
	//! constructor
	fast_rec(size_t ipos, 
		 const cntr_rec * ir1_1, const cntr_rec * ir1_2,
		 const cntr_rec * ir2_1, const cntr_rec * ir2_2) :
	         pos(ipos), r1_1(ir1_1), r1_2(ir1_2), r2_1(ir2_1), r2_2(ir2_2) {};

	//! cell number
	size_t pos;
	
	//! first cell bound data
	const cntr_rec * r1_1;
	
	//! 2-nd cell bound data
	const cntr_rec * r1_2;
	
	//! 3-d cell bound data
	const cntr_rec * r2_1;
	
	//! 4-th cell bound data
	const cntr_rec * r2_2;
};

//! special matrix for \ref f_cntr_smooth functional
class SURFIT_EXPORT matr_cntrs : public matr {
public:
	//! constructor
	matr_cntrs(REAL imult, std::vector<cntr_rec> * idata, size_t iN, bitvec * imask,
		   size_t iNN, size_t iMM);

	//! A destructor
	virtual ~matr_cntrs();

	REAL element_at(size_t i, size_t j, size_t * next_j = NULL) const;
	REAL at(size_t i, size_t j, size_t * next_j = NULL) const;
	
	REAL mult_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);
	
	virtual size_t cols() const;
	virtual size_t rows() const;

	REAL norm() const;

	//! fills the right side vector in matrix equation T*X=V
	void fill_vector(extvec * v);

protected:

	//! matrix size
	size_t N;
	//! number of grid nodes in OX direction
	size_t NN;
	//! number of grid nodes in OY direction
	size_t MM;

	//!  mask for applying matrix
	bitvec * mask;

	//! matrix data
	std::vector<cntr_rec> * data;

	//! data for fast multiplying matrix by vector
	std::vector<fast_rec *> * fast_data;

	//! matrix multiplier
	REAL mult;

public:
	//! iterator for navigating inside vector<cntr_rec>
	typedef std::vector<cntr_rec>::iterator data_it;

protected:
	//! index for matrix data
	std::vector<size_t> * pos2_sorted;

	//! function for finding information about cell
	void find_pos1(size_t pos, const cntr_rec *& r1, const cntr_rec *& r2) const;
	//! function for finding information about cell
	void find_pos2(size_t pos, const cntr_rec *& r1, const cntr_rec *& r2) const;
	
	//! function for fast finding information about cell
	bool find_fast(size_t pos, 
		       const cntr_rec *& r1_1, const cntr_rec *& r1_2,
		       const cntr_rec *& r2_1, const cntr_rec *& r2_2) const;
};

}; // namespace surfit

#endif



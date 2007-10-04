
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
	size_t pos1;
	size_t pos2;
	REAL sum1;
	REAL sum2;
	REAL sum3;
	REAL sum4;
	REAL sum5;
};

//! special struct for \ref matr_rect class
struct fast_rec {
	fast_rec(size_t ipos, 
		 const cntr_rec * ir1_1, const cntr_rec * ir1_2,
		 const cntr_rec * ir2_1, const cntr_rec * ir2_2) :
	         pos(ipos), r1_1(ir1_1), r1_2(ir1_2), r2_1(ir2_1), r2_2(ir2_2) {};
	size_t pos;
	const cntr_rec * r1_1;
	const cntr_rec * r1_2;
	const cntr_rec * r2_1;
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
	REAL mult_transposed_line(size_t J, extvec::const_iterator b_begin, extvec::const_iterator b_end);
	
	virtual size_t cols() const;
	virtual size_t rows() const;

	REAL norm() const;

	void fill_vector(extvec * v);

protected:

	size_t N;
	size_t NN, MM;
	bitvec * mask;
	std::vector<cntr_rec> * data;
	std::vector<fast_rec *> * fast_data;
	REAL mult;

public:
	typedef std::vector<cntr_rec>::iterator data_it;

protected:
	std::vector<size_t> * pos2_sorted;

	void find_pos1(size_t pos, const cntr_rec *& r1, const cntr_rec *& r2) const;
	void find_pos2(size_t pos, const cntr_rec *& r1, const cntr_rec *& r2) const;
	bool find_fast(size_t pos, 
		       const cntr_rec *& r1_1, const cntr_rec *& r1_2,
		       const cntr_rec *& r2_1, const cntr_rec *& r2_2) const;
};

}; // namespace surfit

#endif



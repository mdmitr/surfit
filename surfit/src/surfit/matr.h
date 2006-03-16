
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

#ifndef __surfit_matr__
#define __surfit_matr__

#include "matlab.h"
#include <vector>

namespace surfit {

class vec;
class bitvec;

/*! \class matr
    \brief interface class for sparce matrix
*/
class SURFIT_EXPORT matr : public matlabSparseMatrix {
public:
	//! destructor
	virtual ~matr() {};

	/*! \return i,j-th matrix element
	    \param i i-th index
	    \param j j-th index
	    \param next_j pointer, where next no-zero element index will be placed
	*/
	virtual REAL element_at(int i, int j, int * next_j = NULL) const = 0;

	/*! \return i,j-th transposed matrix element
	    \param i i-th index
	    \param j j-th index
	    \param next_j pointer, where next no-zero element index will be placed
	*/
	virtual REAL element_at_transposed(int i, int j, int * next_j = NULL) const = 0;

	/*! \return i,j-th matrix element after columns and rows removal
	    \param i i-th index
	    \param j j-th index
	    \param next_j pointer, where next no-zero element index will be placed
	*/
	virtual REAL at(int i, int j, int * next_j = NULL) const = 0;

	/*! \return i,j-th transposed matrix element after columns and rows removal
	    \param i i-th index
	    \param j j-th index
	    \param next_j pointer, where next no-zero element index will be placed
	*/
	virtual REAL at_transposed(int i, int j, int * next_j = NULL) const = 0;

	//! returns number of columns in matrix
	virtual long cols() const = 0;

	//! returns number of rows in matrix
	virtual long rows() const = 0;
	
	/*! returns result of multiplication J-th matrix row with vector
	    \param J J-th matrix row
	    \param b_begin pointer to begin of vector
	    \param b_end pointer to end of vector
	*/
	virtual REAL mult_line(int J, const REAL * b_begin, const REAL * b_end) = 0;

	/*! returns result of multiplication J-th matrix col with vector
	    \param J J-th matrix col
	    \param b_begin pointer to begin of vector
	    \param b_end pointer to end of vector
	*/
	virtual REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) = 0;

	virtual void call_after_mult();
	
	//! r = T*b
	void mult(const vec * b, vec * r);
	void mult(const REAL * b_begin, REAL * r_begin);

	//! r = T'*b
	void mult_transposed(const vec * b, vec * r);

	//! calculates norm estimation
	virtual REAL norm() const = 0;
};

/*! \class matr_sum
    \brief complex matrix, defined by formula \f$ T = w_1T_1 + w_2T_2 \f$
*/
class SURFIT_EXPORT matr_sum : public matr {
public:
	
	/*! constructor
	    \param iw1 weigth of first matrix
	    \param iT1 first matrix
	    \param iw2 weigth of second matrix
	    \param iT2 second matrix
	*/
	matr_sum(REAL iw1, matr *iT1, REAL iw2 = 0, matr *iT2 = NULL);
		
	//! destructor 
	virtual ~matr_sum();
	
	//! don't allows to delete input matrators
	void set_const();

	virtual REAL element_at(int i, int j, int * next_j = NULL) const;
	virtual REAL element_at_transposed(int i, int j, int * next_j = NULL) const;
	virtual REAL at(int i, int j, int * next_j = NULL) const;
	virtual REAL at_transposed(int i, int j, int * next_j = NULL) const;
    
	virtual REAL mult_line(int J, const REAL * b_begin, const REAL * b_end);
	virtual REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end);
	virtual void call_after_mult();
		    
	virtual REAL norm() const;
	
	virtual long cols() const;
	
	virtual long rows() const;

	//! weight of first matrix
	REAL w1;
	//! pointer to first matrix
	matr * T1;
	matr * cT1;
	//! weight of second matrix
	REAL w2;
	//! pointer to second matrix
	matr * T2;
	matr * cT2;
    
};

/*! \class matr_sums
    \brief complex matrix, defined by formula \f$ T = \sum_i w_IT_i \f$
*/
class SURFIT_EXPORT matr_sums : public matr {
public:
	
	/*! constructor
	*/
	matr_sums(vec * iweights, std::vector<matr *> * imatrices);

	//! destructor 
	virtual ~matr_sums();

	virtual REAL element_at(int i, int j, int * next_j = NULL) const;
	virtual REAL element_at_transposed(int i, int j, int * next_j = NULL) const;
	virtual REAL at(int i, int j, int * next_j = NULL) const;
	virtual REAL at_transposed(int i, int j, int * next_j = NULL) const;
    
	virtual REAL mult_line(int J, const REAL * b_begin, const REAL * b_end);
	virtual REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end);
	virtual void call_after_mult();
	    
	virtual REAL norm() const;
	virtual long cols() const;
	virtual long rows() const;

	//! weights
	vec * weights;
	//! pointer to first matrix
	std::vector<matr *> * matrices;
   
};

/*! \class matr_mask 
    \brief matrix with zeros rows and cols, where mask is false
*/
class SURFIT_EXPORT matr_mask : public matr {
public:
	
	/*! constructor
	*/
	matr_mask(const bitvec * mask, matr * imatrix);

	//! destructor 
	virtual ~matr_mask();

	virtual REAL element_at(int i, int j, int * next_j = NULL) const;
	virtual REAL element_at_transposed(int i, int j, int * next_j = NULL) const;
	virtual REAL at(int i, int j, int * next_j = NULL) const;
	virtual REAL at_transposed(int i, int j, int * next_j = NULL) const;
    
	virtual REAL mult_line(int J, const REAL * b_begin, const REAL * b_end);
	virtual REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end);
	virtual void call_after_mult();
	    
	virtual REAL norm() const;
	virtual long cols() const;
	virtual long rows() const;

	//! mask
	const bitvec * mask;
	//! pointer to matrix
	matr * matrix;
   
};

}; // namespace surfit;

#endif



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

#ifndef __surfit_oper__
#define __surfit_oper__

#include "matlab.h"

namespace surfit {

class vec;

/*! \class oper
    \brief interface class for sparce matrix
*/
class SURFIT_EXPORT oper : public matlabSparseMatrix {
public:
	//! destructor
	virtual ~oper() {};

	/*! \return i,j-th matrix element
	    \param i i-th index
	    \param j j-th index
	    \param next_j pointer, where next no-zero element index will be placed
	*/
	virtual REAL operator()(int i, int j, int * next_j = NULL) const = 0;

	/*! \return i,j-th matrix element after columns and rows removal
	    \param i i-th index
	    \param j j-th index
	    \param next_j pointer, where next no-zero element index will be placed
	*/
	virtual REAL at(int i, int j, int * next_j = NULL) const = 0;

	//! returns number of columns in matrix
	virtual long cols() const = 0;

	//! returns number of rows in matrix
	virtual long rows() const = 0;
	
	/*! returns result of multiplication J-th matrix row with vector
	    \param J J-th matrix row
	    \param b_begin pointer to begin of vector
	    \param b_end pointer to end of vector
	*/
	virtual REAL mult_line(int J, const REAL * b_begin, const REAL * b_end) const = 0;

	/*! returns result of multiplication J-th matrix col with vector
	    \param J J-th matrix col
	    \param b_begin pointer to begin of vector
	    \param b_end pointer to end of vector
	*/
	virtual REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const = 0;
	
	//! r = T*b
	void mult(vec * b, vec * r);

	//! r = T'*b
	void mult_transposed(vec * b, vec * r);

	//! calculates norm estimation
	virtual REAL norm() const = 0;
};

/*! \class oper_complex
    \brief complex matrix, defined by formula \f$ T = w_1T_1 + w_2T_2 \f$
*/
class SURFIT_EXPORT oper_complex : public oper {
public:
	
	/*! constructor
	    \param iw1 weigth of first matrix
	    \param iT1 first matrix
	    \param iw2 weigth of second matrix
	    \param iT2 second matrix
	*/
	oper_complex(REAL iw1, oper *iT1, REAL iw2 = 0, oper *iT2 = NULL);

	//! destructor 
	virtual ~oper_complex();

	virtual REAL operator()(int i, int j, int * next_j = NULL) const;
	virtual REAL at(int i, int j, int * next_j = NULL) const;
    
	virtual REAL mult_line(int J, const REAL * b_begin, const REAL * b_end) const;
	virtual REAL mult_transposed_line(int J, const REAL * b_begin, const REAL * b_end) const;
	    
	virtual REAL norm() const;
	
	virtual long cols() const;
	
	virtual long rows() const;

	//! weight of first matrix
	REAL w1;
	//! pointer to first matrix
	oper * T1;
	//! weight of second matrix
	REAL w2;
	//! pointer to second matrix
	oper * T2;
    
};

}; // namespace surfit;

#endif



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

#ifndef __surfit_oper_points__
#define __surfit_oper_points__

#include "oper.h"
#include <vector>

namespace surfit {

class vec;
class intvec;
class bitvec;

/*! \class oper_points
    \brief matrix for approximation problem solving subject to scattered data-points 

    This matrix supports taking into account of following data-types:
    \li \ref wtask
    \li \ref wfunc
    \li \ref wiso
    \li \ref wcntr
    \li \ref warea
*/
class SURFIT_EXPORT oper_points : public oper {
public:
	//! constructor
	oper_points(vec * iweights, intvec * iweights_cnt, 
	            bitvec * imask_solved,
		    bitvec * imask_undefined,
		    int iN);

	//! A destructor
	virtual ~oper_points();

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

	//! numbers of elements in row to skip in mult_line function (solved)
	bitvec * mask_solved;
	//! numbers of elements in row to skip in mult_line function (undefined)
	bitvec * mask_undefined;
	
	//! vector of informational weights
	vec * weights;
	//! vector of informational weights (amount of weights)
	intvec * weights_cnt;

};

}; // namespace surfit;

#endif


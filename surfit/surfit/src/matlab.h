
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

#ifndef __surfit_matlab__
#define __surfit_matlab__

#include <stdlib.h>

#include "real.h"

namespace surfit {

SURFIT_EXPORT
bool matlabWriteVector(const REAL * begin, const REAL * end, const char * filename, const char * name);

template <class V>
bool matlabWriteVirtualVector(V * vec, const char * filename, const char * name);

/*! \class matlabVector
    \brief vector of this type can be saved to matlab binary format

Vectors, inherited from matlabVector can be saved into matlab binary
file and then loaded in Matlab with "load" command.
    
\sa
http://www.mathworks.com/access/helpdesk/help/pdf_doc/matlab/matfile_format.pdf

*/
class SURFIT_EXPORT matlabVector {
public:
	/*! \return i-th vector element */	
	virtual REAL operator()(int i) const = 0;
	/*! \returns vector size */
	virtual long size() const = 0;
	/*! writes vector to mat-file (matlab binary format)
	    \param filename mat-file filename
	    \param name vector name
	*/
	bool writeMAT(const char * filename, const char * name);

};

/*! \class matlabSparseMatrix
    \brief matrix of this type can be saved to matlab binary format as 

Matrices, inherited from matlabSparceMatrix can be saved into matlab binary
file and then loaded in Matlab with "load" command.

\sa
http://www.mathworks.com/access/helpdesk/help/pdf_doc/matlab/matfile_format.pdf
  
*/
class SURFIT_EXPORT matlabSparseMatrix {
public:
	/*! \return col's amount */
	virtual long cols() const = 0;
	/*! \return row's amount */
	virtual long rows() const = 0;
	/*! \return i,j-th matrix element */
	virtual REAL operator()(int i, int j, int * next_i = NULL) const = 0;

	/*! writes matrix to mat file (matlab binary format)
	    \param filename mat-file filename
	    \param name matrix name
	*/
	bool writeMAT(const char * filename, const char * name);

};

}; // namespace surfit

#endif


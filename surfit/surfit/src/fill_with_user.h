
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

#ifndef __fill_with_user_included__
#define __fill_with_user_included__

#include "user.h"

namespace surfit {

class fill_with;

/*! \ingroup surfit_data_variables
    \var surfit_fill_with
    \brief set specified value for unsolved cells

Using fill_with you can set values of all unsolved cells.

By loading \ref warea object to surfit memory we write the following equations:

\f[
u_{i,j} = value,
\f]

where \f$u_{i,j}\f$ - are values of the "unsolved" cells.

\sa 
\li \ref fill_with
\li \ref tcl_fill_with "Tcl commands"

*/
extern SURFIT_EXPORT fill_with * surfit_fill_with;

/*! \class fill_with_user
    \brief interface class for making equations from \ref fill_with
*/
class SURFIT_EXPORT fill_with_user : public user {
public:

	//! constructor
	fill_with_user();

	//! destructor
	~fill_with_user();
	
	int max_priority();
	void init();
	void prepare();
	void begin();
	void stage1(int priority);
	void stage2(int priority);
	void stage3(int priority);
	void stage4(int priority);
	void stage5(int priority);
	void finish();
	void release();

};


}; // namespace surfit;

#endif


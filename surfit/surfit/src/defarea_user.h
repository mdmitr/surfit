
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

#ifndef __surfit_defarea_user_included__
#define __surfit_defarea_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class defarea;
class bitvec;
class grid;

SURFIT_EXPORT
void defarea_update_mask_solved(defarea * def, bitvec * mask_solved);

SURFIT_EXPORT
bool check_with_defareas(int pos, grid * grd);

/*! \ingroup surfit_data_variables
    \var surfit_defarea
    \brief surface domain of definition

Surface domain of definition. Using defarea (definition area) you can specify cells with undefined values.

By loading \ref warea object to surfit memory we write the following equations:

\f[
u_{i,j} = undefinedvalue,
\f]

where \f$u_{i,j}\f$ - are values of the cells, for which defarea returns "false".

\par Example : 
\li \ref map_defarea.tcl "Setting domain of definition"

\sa
\li \ref surfit_defareas
\li \ref defarea
\li \ref tcl_defarea "Tcl commands"

*/
extern SURFIT_EXPORT defarea * surfit_defarea;

/*! \ingroup surfit_variables_collections
    \var std::vector<defarea *> * surfit_defareas
    collection of \ref defarea objects
*/
extern SURFIT_EXPORT std::vector<defarea *> * surfit_defareas;

/*! \class defarea_user
    \brief interface class for making equations from \ref defarea
*/
class SURFIT_EXPORT defarea_user : public user {
public:

	//! constructor
	defarea_user();

	//! destructor
	~defarea_user();
	
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


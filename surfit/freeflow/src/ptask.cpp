
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

#include "flow_ie.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "ptask.h"

namespace surfit {

ptask::ptask() : task()
{
};

ptask::ptask(REAL *& iX_begin, REAL * iX_end, 
             REAL *& iY_begin, REAL * iY_end, 
             REAL *& iZ_begin, REAL * iZ_end,
             const char * iptaskname) : 
        task(iX_begin, iX_end,
	     iY_begin, iY_end,
	     iZ_begin, iZ_end,
	     iptaskname)
{
	
};

ptask::ptask(task * tsk) :
	task(tsk->X_begin, tsk->X_end,
	     tsk->Y_begin, tsk->Y_end,
	     tsk->Z_begin, tsk->Z_end,
	     tsk->getName())
{

};

}; // namespace surfit;


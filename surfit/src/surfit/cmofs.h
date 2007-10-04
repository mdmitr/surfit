
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

#ifndef __surfit_cmofs_included__
#define __surfit_cmofs_included__

#include <vector>

namespace surfit {

//! indicates cmofs calculation completness
extern SURFIT_EXPORT bool method_ok;

/*! \ingroup tcl_other
    executes gridding procedure. 

    \sa \ref surfit
*/    
SURFIT_EXPORT 
void surfit();

/*! \ingroup tcl_other
    removes all gridding rules
*/    
SURFIT_EXPORT
void clear_rules();

};

#endif


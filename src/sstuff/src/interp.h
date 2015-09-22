
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

#ifndef __sstuff_interp_included__
#define __sstuff_interp_included__

/*! \file
    \brief declaration of functions connected with using of Tcl interpretator
*/

struct Tcl_Interp;

//! Tcl scripting language interpretator
extern SSTUFF_EXPORT Tcl_Interp * interp;

//! initializes interp variable
SSTUFF_EXPORT
void init_interp(Tcl_Interp * iinterp);

//! Compares two strings, where the first is a string mask
SSTUFF_EXPORT
bool StringMatch(const char * match, const char * str);

#endif



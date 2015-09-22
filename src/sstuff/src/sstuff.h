
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

#ifndef __sstuff__included__
#define __sstuff__included__

/*! \namespace surfit
    \brief namespace where all surfit functions and classes are placed
*/

/*! \file
    \brief declaration of sstuff_free_char and str_to_upper
*/

//! function for freeing memory allocated by libsstuff library
SSTUFF_EXPORT
void sstuff_free_char(char * ptr);

//! converts string to uppercase
SSTUFF_EXPORT
void str_toupper(char * str);

#endif


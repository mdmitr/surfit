
/*------------------------------------------------------------------------------
 *	$Id: fileio.h 920 2007-01-16 16:56:25Z mishadm $
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

#ifndef __sstuff__findfile__
#define __sstuff__findfile__

namespace surfit {

SSTUFF_EXPORT
const char * find_first(const char * pattern);

SSTUFF_EXPORT
const char * find_next();

SSTUFF_EXPORT
void find_close();

};

#endif



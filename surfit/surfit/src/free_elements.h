
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

#ifndef __surfit_free_elements_included__
#define __surfit_free_elements_included__

namespace surfit {

template <class it>
void free_elements(it begin, it end) {
	it temp;
	for (temp = begin; temp != end; temp++) {
		delete *temp;
	}
};

template <class it>
void release_elements(it begin, it end) {
	it temp;
	for (temp = begin; temp != end; temp++) {
		delete (*temp);
	}
};

}; // namespace surfit;

#endif


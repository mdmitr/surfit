
/*------------------------------------------------------------------------------
 *	$Id: bitvec_alg.h 1090 2007-05-14 15:09:08Z mishadm $
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
#ifndef __surfit_incr_ptr_alg__
#define __surfit_incr_ptr_alg__

namespace surfit {

//! increments pointer when matrD* multiplies by vector
template <class iter>
inline
bool incr_ptr(iter & p, size_t i, 
              const bitvec * mask_solved_undefined,
	      size_t incr = 1) 
{
#ifdef XXL
	p = p + incr;
#else
	p += incr;
#endif
	
	if (mask_solved_undefined->get(i))
		return false;
	
	return true;
};

//! increments pointer when matrD* multiplies by vector
template <class iter>
inline
bool incr_ptr(iter & p, size_t i, 
              const bitvec * mask_solved_undefined,
	      size_t x_from, size_t x_to, size_t y_from, size_t y_to, size_t NN,
	      size_t incr = 1)
{
#ifdef XXL
	p = p + incr;
#else
	p += incr;
#endif
	
	size_t n = i % NN;
	size_t m = (i - n)/NN;
	
	if  (!( (n >= x_from) && (n <= x_to) && (m >= y_from) && (m <= y_to) ))
		return false;
	
	if (mask_solved_undefined->get(i))
		return false;

	return true;
};

}; // namespace surfit;

#endif


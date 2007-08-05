
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

#ifndef __surfit_byteswap_alg__
#define __surfit_byteswap_alg__

#include <algorithm>

/*! \file 
    \brief Declaration of ByteSwapFunc function and ByteSwap macro
*/
namespace surfit {

//! Macro for calling ByteSwapFunc
#define ByteSwap(x) ByteSwapFunc((unsigned char *) &x,sizeof(x))

//! Swaps byte order
inline
void ByteSwapFunc(unsigned char * b, int n)
{
   register int i = 0;
   register int j = n-1;
   while (i<j)
   {
      std::swap(b[i], b[j]);
      i++, j--;
   }
}

}; // namespace surfit;

#endif


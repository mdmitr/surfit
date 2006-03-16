
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

#ifndef __surfit_mklsolver_ie__included__
#define __surfit_mklsolver_ie__included__

#ifdef _MSC_VER
#include "config.h"
#else
#include "../config.h"
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#  if defined(_MSC_VER) || defined(__GNUC__)
#    if defined(STATIC_LINKED)
#      define SSTUFF_EXPORT extern 
#      define SURFIT_EXPORT extern 
#      define MKLSOLVER_EXPORT 
#    else
#      define SSTUFF_EXPORT __declspec(dllimport)
#      define SURFIT_EXPORT __declspec(dllimport)
#      define MKLBOOSTER_EXPORT __declspec(dllexport)
#    endif
#  endif
#else
#  define SSTUFF_EXPORT
#  define SURFIT_EXPORT
#  define MKLBOOSTER_EXPORT
#endif

#ifndef MIN
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#endif

#include "real.h"
#include <stdlib.h>

#endif



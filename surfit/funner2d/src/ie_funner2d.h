
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

#ifndef __surfit_funner2d_ie__included__
#define __surfit_funner2d_ie__included__

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#  if defined(_MSC_VER) || defined(__GNUC__)
#    if defined(STATIC_LINKED)
//#      define FL_EXPORT extern 
#      define FUNNER_EXPORT
#    else
//#      define FL_EXPORT       __declspec(dllimport)
#      define FUNNER_EXPORT   __declspec(dllexport)
#    endif
#  endif
#else
//#  define FL_EXPORT
#  define FUNNER_EXPORT
#endif

#ifndef MIN
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#endif

#endif



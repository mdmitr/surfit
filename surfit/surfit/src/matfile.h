
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

#ifndef __mat_file_defs__
#define __mat_file_defs__

// Mat-file datatypes
#define miINT8		1
#define miUINT8		2
#define miINT16		3
#define miUINT16	4
#define miINT32		5
#define miUINT32	6
#define miSINGLE	7
#define miDOUBLE	9
#define miINT64		12
#define miUINT64	13
#define miMATRIX	14

// Matlab array types
#define mxCELL_CLASS	1
#define mxSTRUCT_CLASS	2
#define mxOBJECT_CLASS	3
#define mxCHAR_CLASS	4
#define mxSPARSE_CLASS	5
#define mxDOUBLE_CLASS	6
#define mxSINGLE_CLASS	7
#define mxINT8_CLASS	8
#define mxUINT8_CLASS	9
#define mxINT16_CLASS	10
#define mxUINT16_CLASS	11
#define mxINT32_CLASS	12
#define mxUINT32_CLASS	13

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

#include <fcntl.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>

#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
bool mWrite1(int file, __int8 a) {
#else
bool mWrite1(int file, int8_t a) {
#endif
	bool res = (write(file, &a, 1) == 1);
	
	return res;
}

#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
bool mWrite2(int file, __int16 a) {
#else
bool mWrite2(int file, int16_t a) {
#endif
	bool res = (write(file, &a, 2) == 2);
	
	return res;
}

#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
bool mWrite4(int file, __int32 a) {
#else
bool mWrite4(int file, int32_t a) {
#endif
	bool res = (write(file, &a, 4) == 4);
	
	return res;
}

bool mWriteDouble(int file, double a) {
	bool res = (write(file, &a, 8) == 8);
	
	return res;
};

bool mWriteName(int file, const char * name) {
	int lname = MIN(strlen(name),4);
	if ( !mWrite2(file,miINT8) ) return false;
	if ( !mWrite2(file,lname) ) return false;
	if (strlen(name) < 4) {
		switch ( strlen(name) ) {
		case 1:
			if ( !mWrite1(file,*name) ) return false;
			if ( !mWrite1(file,0) ) return false;
			if ( !mWrite1(file,0) ) return false;
			if ( !mWrite1(file,0) ) return false;
			break;
		case 2:
			if ( !mWrite1(file,*name) ) return false;
			if ( !mWrite1(file,*(name+1)) ) return false;
			if ( !mWrite1(file,0) ) return false;
			if ( !mWrite1(file,0) ) return false;
			break;
		case 3:
			if ( !mWrite1(file,*name) ) return false;
			if ( !mWrite1(file,*(name+1)) ) return false;
			if ( !mWrite1(file,*(name+2)) ) return false;
			if ( !mWrite1(file,0) ) return false;
			break;
		}
	} else {
		if ( !mWrite1(file,*name) ) return false;
		if ( !mWrite1(file,*(name+1)) ) return false;
		if ( !mWrite1(file,*(name+2)) ) return false;
		if ( !mWrite1(file,*(name+3)) ) return false;
	}
	return true;
};

#endif


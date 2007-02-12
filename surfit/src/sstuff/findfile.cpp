
/*------------------------------------------------------------------------------
 *	$Id: fileio.cpp 934 2007-01-28 16:59:19Z mishadm $
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

#include "sstuff_ie.h"
#include "findfile.h"
#include "fileio.h"

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#else
#include <dirent.h>
#endif

#include <string.h>

namespace surfit {

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

static _finddata_t ff;
long file_handle = -1;

const char * find_first(const char * pattern)
{
	file_handle = _findfirst(pattern, &ff);
	if (file_handle == -1) {
		writelog(LOG_ERROR,"%s",strerror(errno));
		return NULL;
	}
	if (ff.attrib &= _A_SUBDIR)
		return find_next();
	return ff.name;
};

const char * find_next()
{
	int res = _findnext(file_handle, &ff);
	if (res == 0) {
		if (ff.attrib &= _A_SUBDIR)
			return find_next();
		return ff.name;
	}
	return NULL;
};

void find_close()
{
	_findclose(file_handle);
};

#else

int wildcmp(const char *wild, const char *string) {
	// Written by Jack Handy - jakkhandy@hotmail.com
	const char *cp = NULL, *mp = NULL;
	
	while ((*string) && (*wild != '*')) {
		if ((*wild != *string) && (*wild != '?')) {
			return 0;
		}
		wild++;
		string++;
	}
	
	while (*string) {
		if (*wild == '*') {
			if (!*++wild) {
				return 1;
			}
			mp = wild;
			cp = string+1;
		} else if ((*wild == *string) || (*wild == '?')) {
			wild++;
			string++;
		} else {
			wild = mp;
			string = cp++;
		}
	}
	
	while (*wild == '*') {
		wild++;
	}
	return !*wild;
};

DIR *dp = NULL;
struct dirent *entry = NULL;

const char * find_first(const char * pattern)
{
	if((dp = opendir(".")) == NULL)
		return NULL;

	return find_next();
};

const char * find_next() 
{
	entry = readdir(dp);
	if (entry == NULL)
		return NULL;
	else
		return entry->d_name;
};

void find_close() 
{
	closedir(dp);
};

#endif

}; // namespace surfit



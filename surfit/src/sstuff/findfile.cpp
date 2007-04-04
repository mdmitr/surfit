
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
#include "interp.h"

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#else
#include <dirent.h>
#endif

#include <string.h>
#include <stdlib.h>

namespace surfit {

char * find_pattern = NULL;
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
char find_res[_MAX_PATH];
#else
char find_res[512];
#endif
int path_pos = 0;

const char * make_find_res(const char * str) 
{
	strncpy(find_res+path_pos, str, strlen(str));
	find_res[path_pos + strlen(str)] = '\0';
	return find_res;
};

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
	find_pattern = strdup(pattern);

	int path_pos1 = 0;
	if ( strrchr(find_pattern+path_pos1, '/') != NULL )
		path_pos1 = strrchr(find_pattern+path_pos1, '/') - find_pattern + 1;
	
	int path_pos2 = 0;
	if ( strrchr(find_pattern+path_pos2, '\\') != NULL )
		path_pos2 = strrchr(find_pattern+path_pos2, '\\') - find_pattern + 1;

	path_pos = MAX(path_pos1, path_pos2);
	strncpy(find_res, find_pattern, path_pos);

	if (ff.attrib &= _A_SUBDIR)
		return find_next();
	return make_find_res(ff.name);
};

const char * find_next()
{
	int res = _findnext(file_handle, &ff);
	if (res == 0) {
		if (ff.attrib &= _A_SUBDIR)
			return find_next();
		return make_find_res(ff.name);
	}
	return NULL;
};

void find_close()
{
	free(find_pattern);
	_findclose(file_handle);
};

#else

bool wildcmp(const char *wild, const char *string) {
	return StringMatch( wild, string);
	/*
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
	*/
};

DIR *dp = NULL;
struct dirent *entry = NULL;

const char * find_first(const char * pattern)
{
	find_pattern = strdup(pattern);

	int path_pos1 = 0;
	if ( strrchr(find_pattern+path_pos1, '/') != NULL )
		path_pos1 = strrchr(find_pattern+path_pos1, '/') - find_pattern + 1;
	
	int path_pos2 = 0;
	if ( strrchr(find_pattern+path_pos2, '\\') != NULL )
		path_pos2 = strrchr(find_pattern+path_pos2, '\\') - find_pattern + 1;

	path_pos = MAX(path_pos1, path_pos2);
	if (path_pos != 0) {
		strncpy(find_res, find_pattern, path_pos);
		find_res[path_pos] = '\0';
	} else {
		find_res[0]='.';
		find_res[1]='\0';
	}

	if ((dp = opendir(find_res)) == NULL)
	{
		free(find_pattern);
		find_pattern = NULL;
		return NULL;
	}

	return find_next();
};

const char * find_next() 
{
	entry = readdir(dp);
	if (entry == NULL)
		return NULL;
	else {
		const char * name = make_find_res(entry->d_name);
		if ( wildcmp(find_pattern, name) ) {
			return name;
		} else
			return find_next();
	}
};

void find_close() 
{
	closedir(dp);
	free(find_pattern);
	find_pattern = NULL;
};

#endif

}; // namespace surfit



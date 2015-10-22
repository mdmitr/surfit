
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

#include "sstuff_ie.h"
#include "interp.h"
#include "fileio.h"

#include <string.h>

//Tcl_Interp * interp = NULL;

/*
void init_interp(Tcl_Interp * iinterp) {
	interp = iinterp;
};
*/

bool StringMatch(const char * match, const char * str)
{
	char * reg = strdup(match);
	char * s = strdup(str);
	int res = 0;
/*
	if (reg)
		res = Tcl_StringMatch(s, reg);
	else 
		res = Tcl_StringMatch(s, "*");
		*/
	free(reg);
	free(s);
	if (res == -1) 
		surfit::writelog(LOG_ERROR,"Wrong match : \"%s\"",match);
	return (res == 1);
};


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

#include "funner_channel.h"

#include <tcl.h>
#include <stdlib.h>
#include <string.h>

int
funnerCloseProc(ClientData instanceData, Tcl_Interp *interp) {
	return 0;
};

int
funnerOutputProc(ClientData instanceData, CONST char * buf, int toWrite, int * errorCode)
{
	*errorCode = 0;
	if (toWrite <= 0) 
		return -1;
    
	char * data = (((funnerChannelInfo*)instanceData)->data);
	
	if (data)
		free(data);
	data = (char*)malloc(sizeof(char)*strlen(buf)+1);
	strncpy(data,buf,strlen(buf)+1);
	data[strlen(buf)] = 0;
	//(((funnerChannelInfo*)instanceData)->data) = data;

	return toWrite;
};



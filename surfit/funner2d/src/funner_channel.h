
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

#ifndef __funner_channel_included__
#define __funner_channel_included__

#include <tcl.h>

typedef struct funnerChannelInfo {
    char * data;
} funnerChannelInfo;

int
funnerCloseProc(ClientData instanceData, Tcl_Interp *interp);

int
funnerOutputProc(ClientData instanceData, CONST char * buf, int toWrite, int * errorCode);

static Tcl_ChannelType funnerChannelType = {
    "file",						/* Type name. */
    TCL_CHANNEL_VERSION_2,				/* v2 channel */
    funnerCloseProc,					/* Close proc. */
    NULL,						/* Input proc. */
    (Tcl_DriverOutputProc *)funnerOutputProc,		/* Output proc. */
    NULL,						/* Seek proc. */
    NULL,						/* Set option proc. */
    NULL,						/* Get option proc. */
    NULL,						/* Set up the notifier to watch the channel. */
    NULL,						/* Get an OS handle from channel. */
    NULL,						/* close2proc. */
    NULL,   						/* Set blocking or non-blocking mode.*/
    NULL,						/* flush proc. */
    NULL,						/* handler proc. */
};


#endif



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

#ifndef __surfit__fileio__
#define __surfit__fileio__

#include <stdio.h>

namespace surfit {

#define SURFIT_MESSAGE 0
#define SURFIT_ERROR 1
#define SURFIT_WARNING 2
#define SURFIT_DEBUG 3

SURFIT_EXPORT
/*! \ingroup internal
    \fn void writelog (int errlevel, const char *tmplt, ...);
    \brief logfile's "printf" function
    \param errlevel errorlevel ( 0 - messages, 1 - errors, 2 - warnings, 3 - debug )
    \param tmplt template
*/
void writelog (int errlevel, const char *tmplt, ...);

SURFIT_EXPORT
/*! \ingroup internal
    \fn void Tcl_printf (const char *tmplt, ...);
    \brief Tcl-console 'printf"
*/
void Tcl_printf (const char *tmplt, ...);

SURFIT_EXPORT
void _file_info(const char * filename, char **& contents);

//////////////
// log

SURFIT_EXPORT
/*! \ingroup tcl_log
    \fn int log_open(int level = 3, const char * logname = NULL);
    \brief opens log for writing.
    \param level errorlevel ( 0 - messages, 1 - errors, 2 - warnings, 3 - debug )
    \param logname name for logfile (optional, surfit.log - default )
*/
int log_open(int level = 3, const char * logname = NULL);

SURFIT_EXPORT
/*! \ingroup tcl_log
    \fn int log_clear();
    \brief clears log file (if opened)
*/
int log_clear();

/*! \ingroup tcl_log
    \fn void putlog(const char * str);
    \brief writes string to logfile
*/
void putlog(const char * str);

};

#endif



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

#ifndef __sstuff__fileio__
#define __sstuff__fileio__

#include <stdio.h>

/*! \file
    \brief various file input/output functions declaration (mostly for working with log-file)
*/

namespace surfit {

//! number of points for printing progress bar
#define PROGRESS_POINTS 7

//! Error message
#define LOG_ERROR_TCL 0 

//! Usual message
#define LOG_MESSAGE 1

//! Error message
#define LOG_ERROR 2

//! Warning message
#define LOG_WARNING 3

//! Debug message
#define LOG_DEBUG 4

//! No message output
#define LOG_SILENT 5

//! global variable for stopping calculations or other operations 
extern SSTUFF_EXPORT int stop_on_error;

//! current log level (LOG_MESSAGE, LOG_ERROR or other). According to this variable
//! outputs functions writes all messages with level <= loglevel to logfile
extern SSTUFF_EXPORT int loglevel;

//! this variable shows how to work with file - append or rewrite it. 
extern SSTUFF_EXPORT bool fileio_append;

/*! \brief logfile's "printf" function
    \param errlevel errorlevel ( 0 - messages, 1 - errors, 2 - warnings, 3 - debug )
    \param tmplt template (like in printf function)
*/
SSTUFF_EXPORT
void writelog (int errlevel, const char *tmplt, ...);

/*! \brief logfile's "printf" function. Don't prints "\n" at the end of message
    \param errlevel errorlevel ( 0 - messages, 1 - errors, 2 - warnings, 3 - debug )
    \param tmplt template
*/
SSTUFF_EXPORT
void writelog2 (int errlevel, const char *tmplt, ...);

/*! \brief logfile's "printf" function
    \param tmplt template
*/
SSTUFF_EXPORT
void log_printf (const char *tmplt, ...);

//! Prints text to Tcl-console
SSTUFF_EXPORT
void Tcl_printf (const char *tmplt, ...);

//! prints contents of surfit datafile
SSTUFF_EXPORT
void _file_info(const char * filename, char **& contents);

//////////////
// log

/*! \brief opens log for writing.
    \param level errorlevel
    \param logname name for logfile (optional, surfit.log - default )
*/
SSTUFF_EXPORT
int log_open(int level = LOG_WARNING, const char * logname = NULL);

//! clears log file (if opened)
SSTUFF_EXPORT
int log_clear();

//! writes string with LOG_MESSAGE loglevel to logfile 
SSTUFF_EXPORT
void putlog(const char * str);

//! reads first 1024 bytes from file
SSTUFF_EXPORT
char * read_first1024(const char * filename, int & readed);

//! calculates number of columns in text file
SSTUFF_EXPORT
int calc_columns(const char * Str, int readed, char * seps);

//! calculates number of rows in text file
SSTUFF_EXPORT
int calc_rows(const char * Str, int readed);

//! returns filename without extension and path
SSTUFF_EXPORT
char * get_name(const char * filename);

//! returns filename extension (text after last ".")
SSTUFF_EXPORT
char * get_ext(const char * filename);

//! returns full filename extension
SSTUFF_EXPORT
char * get_full_ext(const char * filename);

};

#endif


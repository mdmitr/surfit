
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

#include "ie.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <tcl.h>
#include <time.h>
#include <errno.h>
#include "fileio.h"
#include "variables_internal.h"
#include "user.h"

namespace surfit {

char * error = "Error! ";
char * warning = "Warning! ";
char * debug = "Debug: ";

FILE * logfile = NULL;
char * logfilename = NULL;
int loglevel = 0;
// 0 - General messages
// 1 - Error messages
// 2 - Warning messages
// 3 - Debug messages

/*! \struct fileio_garbage
    \brief struct for log-file-around pointers deletions
*/
struct fileio_garbage : public binman {
	//! destructor
	~fileio_garbage() {
		free(logfilename);
		if (logfile)
			fclose(logfile);
	};
};

fileio_garbage garb2;

void writelog (int errlevel, const char *tmplt, ...) {
	if (errlevel > loglevel) return;

	Tcl_Channel out;
	if (surfit_interp) {
		out = Tcl_GetStdChannel(TCL_STDOUT);
	}
	char enter = '\n';

	struct tm * newtime;
	time_t aclock;


	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form 

	/* Print local time as a string */
	char tmpbuf[128];
	strftime(tmpbuf, 128, "%d/%m/%y %H:%M:%S : ", newtime);
	Tcl_printf("%s", tmpbuf);
	
	va_list ap;
	va_start (ap, tmplt);
	// console output

	if (surfit_interp) {

		switch (errlevel) {

		case SURFIT_MESSAGE:
			break;
		case SURFIT_ERROR: 
			Tcl_WriteChars(out, error, strlen(error));
			break;
		case SURFIT_WARNING:
				Tcl_WriteChars(out, warning, strlen(warning));
			break;
		case SURFIT_DEBUG:
				Tcl_WriteChars(out, debug, strlen(debug));
			break;
		};

		char buf[2048];
		int written = vsprintf(buf,tmplt, ap);
		if (written > 2048) 
			writelog(SURFIT_WARNING,"Too large error message. ");
		Tcl_WriteChars(out, buf, written);
		Tcl_WriteChars(out, &enter, 1);

	}

	if ( (logfile) && (ferror(logfile) == 0) ) {
		
		time_t ltime;
		time( &ltime );
		char * stime = ctime( &ltime );
		char * space = " :  ";
		
		fwrite(tmpbuf, 1, strlen(tmpbuf), logfile);
		switch (errlevel) {
		case SURFIT_MESSAGE:
			break;
		case SURFIT_ERROR:
			fprintf(logfile,"%s",error);
			break;
		case SURFIT_WARNING:
			fprintf(logfile,"%s",warning);
			break;
		case SURFIT_DEBUG:
			fprintf(logfile,"%s",debug);
			break;
		};
		vfprintf (logfile, tmplt, ap);
		fprintf (logfile,"\n");
	}

	va_end (ap);
	if ( (logfile) && (ferror(logfile) == 0) ) fflush(logfile);

	if (errlevel == SURFIT_ERROR) 
		throw "surfit_error_for_tcl";
};

void Tcl_printf (const char *tmplt, ...) {

	if (!surfit_interp)
		return;

	Tcl_Channel out = Tcl_GetStdChannel(TCL_STDOUT);
	
	va_list ap;
	va_start (ap, tmplt);
	// console output
		
	char buf[2048];
	int written = vsprintf(buf,tmplt, ap);
	if (written > 2048) 
		writelog(SURFIT_WARNING,"Too large message. ");
	Tcl_WriteChars(out, buf, written);
	
	va_end (ap);

};

int log_open(int level, const char * logname) {

    loglevel = level;
	if (logfile) {
		fclose(logfile);
	};
	
    if (logname) {
		logfilename = (char*)realloc(logfilename, strlen(logname)+1);
        strcpy(logfilename,logname);
    } else {
	    logfilename = (char*)realloc(logfilename, strlen("surfit.log")+1);
		if (logfilename)
			strcpy(logfilename,"surfit.log");
		else 
			return 0;
    }

    logfile = fopen(logfilename, "a");

	if (!logfile) {
		perror("Log file open error!");
		return 0;
	}
	int err = ferror(logfile);
	if (err != 0) {
		perror("Log file open error!");
        return 0;
	};
    return 1;
};

int log_clear() {
    if (!logfile) {
        perror("Log file not opened!");
        return 0;
    }
    if (logfile) {
        fclose(logfile);
        logfile = fopen(logfilename, "w+");
    }
    return (logfile != NULL);
};

void putlog(const char * str) {
	writelog(SURFIT_MESSAGE, str);
};

}; // namespace surfit;


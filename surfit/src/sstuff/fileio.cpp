
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
#include <stdio.h>
#include <stdarg.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <tcl.h>
#include <time.h>
#include <errno.h>

#include "interp.h"
#include "fileio.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <fcntl.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

namespace surfit {

const char * error = "Error! ";
const char * warning = "Warning! ";
const char * debug = "Debug: ";

FILE * logfile = NULL;
char * logfilename = NULL;
int loglevel = LOG_MESSAGE;
int stop_on_error = 1;
bool fileio_append = false;

/*! \struct fileio_garbage
    \brief struct for log-file-around pointers deletions
*/
struct fileio_garbage {
	//! destructor
	~fileio_garbage() {
		free(logfilename);
		if (logfile)
			fclose(logfile);
#ifdef _MSC_VER
#ifdef DEBUG
		_CrtDumpMemoryLeaks();
#endif
#endif
	};
};

fileio_garbage garb2;

void log_printf(const char *tmplt, ...) 
{
	if (loglevel == LOG_SILENT)
		return;
	Tcl_Channel out;
	if (interp) {
		out = Tcl_GetStdChannel(TCL_STDOUT);
		if (out == NULL)
			return;
	}

	va_list ap;
	va_start (ap, tmplt);

	// console output
	if (interp) {

		char buf[2048];
		int written = vsprintf(buf,tmplt, ap);
		va_end(ap);
		va_start(ap,tmplt);
		if (written > 2048) 
			writelog(LOG_WARNING,"Too large error message. ");
		Tcl_WriteChars(out, buf, written);
		Tcl_Flush(out);
	}

	// logfile output
	if ( (logfile) && (ferror(logfile) == 0) ) 
		vfprintf (logfile, tmplt, ap);
	
	va_end (ap);
	if ( (logfile) && (ferror(logfile) == 0) ) fflush(logfile);

};

void writelog (int errlevel, const char *tmplt, ...) 
{
	// don't print any messages in LOG_SILENT mode
	if (loglevel == LOG_SILENT)
		return;

	// don't print messages with higher loglevel
	if (errlevel > loglevel) 
		return;

	Tcl_Channel out;
	if (interp) {
		out = Tcl_GetStdChannel(TCL_STDOUT);
		if (out == NULL)
			return;
	}
	char enter = '\n';

	struct tm * newtime;
	time_t aclock;


	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form 

	// Print local time as a string
	char tmpbuf[128];
	strftime(tmpbuf, 128, "%d/%m/%y %H:%M:%S : ", newtime);
	Tcl_printf("%s", tmpbuf);
	
	va_list ap;
	va_start (ap, tmplt);
	
	// console output
	if (interp) {

		switch (errlevel) {

		case LOG_MESSAGE:
			break;
		case LOG_ERROR: 
		case LOG_ERROR_TCL:
			Tcl_WriteChars(out, error, strlen(error));
			break;
		case LOG_WARNING:
				Tcl_WriteChars(out, warning, strlen(warning));
			break;
		case LOG_DEBUG:
				Tcl_WriteChars(out, debug, strlen(debug));
			break;
		};

		char buf[2048];
		int written = vsprintf(buf,tmplt, ap);
		va_end(ap);
		va_start (ap, tmplt);
		if (written > 2048) 
			writelog(LOG_WARNING,"Too large error message. ");
		Tcl_WriteChars(out, buf, written);
		Tcl_WriteChars(out, &enter, 1);
		Tcl_Flush(out);

	}

	// logfile output
	if ( (logfile) && (ferror(logfile) == 0) ) {
		
		time_t ltime;
		time( &ltime );
		char * stime = ctime( &ltime );
		const char * space = " :  ";
		
		fwrite(tmpbuf, 1, strlen(tmpbuf), logfile);
		switch (errlevel) {
		case LOG_MESSAGE:
			break;
		case LOG_ERROR:
		case LOG_ERROR_TCL:
			fprintf(logfile,"%s",error);
			break;
		case LOG_WARNING:
			fprintf(logfile,"%s",warning);
			break;
		case LOG_DEBUG:
			fprintf(logfile,"%s",debug);
			break;
		};
		vfprintf (logfile, tmplt, ap);
		va_end(ap);
		fprintf (logfile,"\n");
	}

	if ( (logfile) && (ferror(logfile) == 0) ) fflush(logfile);

	if (stop_on_error == 1) {
		if (errlevel == LOG_ERROR) 
			throw "Execution stopped";
	}
};

void writelog2 (int errlevel, const char *tmplt, ...) 
{
	// don't print any messages in LOG_SILENT mode
	if (loglevel == LOG_SILENT)
		return;

	// don't print messages with higher loglevel
	if (errlevel > loglevel) 
		return;

	Tcl_Channel out;
	if (interp) {
		out = Tcl_GetStdChannel(TCL_STDOUT);
		if (out == NULL)
			return;
	}
	
	struct tm * newtime;
	time_t aclock;


	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form 

	// Print local time as a string 
	char tmpbuf[128];
	strftime(tmpbuf, 128, "%d/%m/%y %H:%M:%S : ", newtime);
	Tcl_printf("%s", tmpbuf);
	
	va_list ap;
	va_start (ap, tmplt);

	// console output
	if (interp) {

		switch (errlevel) {

		case LOG_MESSAGE:
			break;
		case LOG_ERROR: 
		case LOG_ERROR_TCL:
			Tcl_WriteChars(out, error, strlen(error));
			break;
		case LOG_WARNING:
				Tcl_WriteChars(out, warning, strlen(warning));
			break;
		case LOG_DEBUG:
				Tcl_WriteChars(out, debug, strlen(debug));
			break;
		};

		char buf[2048];
		int written = vsprintf(buf,tmplt, ap);
		va_end(ap);
		va_start(ap, tmplt);
		if (written > 2048) 
			writelog(LOG_WARNING,"Too large error message. ");
		Tcl_WriteChars(out, buf, written);
		Tcl_Flush(out);

	}

	// logfile output
	if ( (logfile) && (ferror(logfile) == 0) ) {
		
		time_t ltime;
		time( &ltime );
		char * stime = ctime( &ltime );
		const char * space = " :  ";
		
		fwrite(tmpbuf, 1, strlen(tmpbuf), logfile);
		switch (errlevel) {
		case LOG_MESSAGE:
			break;
		case LOG_ERROR:
		case LOG_ERROR_TCL:
			fprintf(logfile,"%s",error);
			break;
		case LOG_WARNING:
			fprintf(logfile,"%s",warning);
			break;
		case LOG_DEBUG:
			fprintf(logfile,"%s",debug);
			break;
		};
		vfprintf (logfile, tmplt, ap);
	}

	va_end (ap);
	if ( (logfile) && (ferror(logfile) == 0) ) fflush(logfile);

	if (stop_on_error == 1) {
		if (errlevel == LOG_ERROR) 
			throw "Execution stopped";
	}
};

void Tcl_printf (const char *tmplt, ...) 
{
	// don't print any messages in LOG_SILENT mode
	if (loglevel == LOG_SILENT)
		return;

	if (!interp)
		return;

	Tcl_Channel out = Tcl_GetStdChannel(TCL_STDOUT);
	if (out == NULL)
		return;
	
	va_list ap;
	va_start (ap, tmplt);

	// console output		
	char buf[2048];
	int written = vsprintf(buf,tmplt, ap);
	if (written > 2048) 
		writelog(LOG_WARNING,"Too large message. ");
	Tcl_WriteChars(out, buf, written);
	
	va_end (ap);

};

int log_open(int level, const char * logname) 
{	
	loglevel = level;

	// close log if it already opened
	if (logfile) {
		fclose(logfile);
	};
	
	if (logname) {
		logfilename = strdup(logname);
	} else {
		logfilename = strdup("surfit.log");
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

int log_clear() 
{
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

void putlog(const char * str) 
{
	writelog(LOG_MESSAGE, str);
};

char * read_first1024(const char * filename, int & readed) 
{
	int file = -1;
	readed = 0;
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	file = open(filename, O_BINARY);
#else
	file = open(filename, O_RDONLY);
#endif
	if (file == -1) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));

		return NULL;
	}

	char * res = (char *) malloc(1024*sizeof(char));

	readed = read(file, res, 1024*sizeof(char));

	close(file);
	return res;
	
};

int calc_columns(const char * Str, int readed, const char * seps) 
{
	char * str = strdup(Str);

	char * pos = strchr(str, '\n');
	if (pos != NULL) {
		*pos = '\0';
	}

	pos = strchr(str, '\r');
	if (pos != NULL) {
		*pos = '\0';
	}

	int columns = 0;

	char * token = strtok( str, seps );
	while (token != NULL) {
		REAL val = (REAL)atof(token);
		if (val != 0)
			columns++;
		else {
			if (strlen(token) != 0) {
				//if ( (token[0] >= '0') && (token[0] <= '9') )
				columns++;
			}
		}
		token = strtok( NULL, seps );
	};

	free(str);
	return columns;
};

int calc_rows(const char * Str, int readed) 
{
	char * str = strdup(Str);
	char seps[] = "\n";

	int rows = 0;

	char * token = strtok( str, seps );
	while (token != NULL) {
		rows++;
		token = strtok( NULL, seps );
	}

	free(str);
	return rows;
};

char * get_name(const char * filename) 
{
	const char * posLastDot = strrchr(filename, '.');

	// check whether this dot occurs at the very beginning of a path component
	if (posLastDot != NULL) {
		if ( strchr( posLastDot, '/' ) )
			posLastDot = NULL;
	}
	if (posLastDot != NULL) {
		if ( strchr( posLastDot, '\\' ) )
			posLastDot = NULL;
	}
	if (posLastDot == filename) {
			posLastDot = NULL;
	}

	const char * posLastSlash1 = strrchr(filename, '/')+1;
	const char * posLastSlash2 = strrchr(filename, '\\')+1;
	const char * posLastSlash = MAX(posLastSlash1, posLastSlash2);
	posLastSlash = MIN(filename + strlen(filename) - 1, posLastSlash);

	const char * pos_from = MAX(filename, posLastSlash);
	const char * pos_to = posLastDot;
	if (posLastDot == NULL)
		pos_to = filename + strlen(filename);

	int len = pos_to-pos_from;

	char * res = (char *)malloc( (len+1) * sizeof(char));
	strncpy(res, pos_from, len);
	res[len]='\0';
	return res;

};

char * get_full_ext(const char * filename) 
{
	const char * search_from = filename;
	const char * posFirstDot = NULL;
	int len = strlen(filename);
	
	while (!posFirstDot) {
		posFirstDot = strchr(search_from, '.');
		if ((posFirstDot-filename) == len)
			return NULL;
		
		// check whether this dot occurs at the very beginning of a path component
		if (posFirstDot != NULL) {
			if ( strchr( posFirstDot, '/' ) ) {
				search_from = posFirstDot+1;
				posFirstDot = NULL;
			}
		}
		if (posFirstDot != NULL) {
			if ( strchr( posFirstDot, '\\' ) ) {
				search_from = posFirstDot+1;
				posFirstDot = NULL;
			}
		}
		if (posFirstDot == filename) {
			posFirstDot = NULL;
		}
	}

	const char * pos_from = posFirstDot;
	const char * pos_to = filename + strlen(filename);
	
	len = pos_to-pos_from;

	char * res = (char *)malloc( (len+1) * sizeof(char));
	strncpy(res, pos_from, len);
	res[len]='\0';
	return res;
};

char * get_ext(const char * filename) 
{
	const char * posLastDot = strrchr(filename, '.');

	// check whether this dot occurs at the very beginning of a path component
	if (posLastDot != NULL) {
		if ( strchr( posLastDot, '/' ) )
			posLastDot = NULL;
	}
	if (posLastDot != NULL) {
		if ( strchr( posLastDot, '\\' ) )
			posLastDot = NULL;
	}
	if (posLastDot == filename) {
			posLastDot = NULL;
	}

	if (posLastDot == NULL)
		return NULL;

	const char * pos_from = posLastDot;
	const char * pos_to = filename + strlen(filename);
	
	int len = pos_to-pos_from;

	char * res = (char *)malloc( (len+1) * sizeof(char));
	strncpy(res, pos_from, len);
	res[len]='\0';
	return res;
};


}; // namespace surfit;



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
#include <string.h>
#include "task.h"
#include "task_internal.h"
#include "wtask.h"
#include "read_txt.h"
#include "vec.h"
#include "fileio.h"
#include "datafile.h"
#include "sort_alg.h"

#include "task_user.h"

#include <algorithm>

namespace surfit {

task * _task_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by) {

	if (taskname)
		writelog(SURFIT_MESSAGE,"reading task \"%s\" from file %s", taskname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading task from file %s", filename);

	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;
	REAL * col3_begin, * col3_end;

	if (!three_columns_read(filename, columns, col1, col2, col3, delimiter, grow_by, 
		col1_begin, col1_end,
		col2_begin, col2_end,
		col3_begin, col3_end))
		return NULL;
	
	task *res = new task(col1_begin, col1_end,
                             col2_begin, col2_end, 
                             col3_begin, col3_end,
                             taskname);
	
	return res;
};

task * _task_load_df(datafile * df, const char * taskname) {

	if (!taskname)
		writelog(SURFIT_MESSAGE,"loading task from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading task \"%s\" from file %s", taskname, df->get_filename());

	if (!df->condition())
		return NULL;
	
	char error[] = "task_load : wrong datafile format";

	task * tsk = new task();
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("task")) {
			
			df->skipTagName();
			
			REAL * X_begin = NULL;
			REAL * X_end = NULL;
			REAL * Y_begin = NULL;
			REAL * Y_end = NULL;
			REAL * Z_begin = NULL;
			REAL * Z_end = NULL;
			
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord("array") ) {
					// read array type
					if (!df->readWord()) goto exit;
					
					if ( df->isWord(REAL_NAME) ) {
						
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("x") ) {
							if ( !df->readRealArray(X_begin,X_end) ) goto exit;
							tsk->X_begin = X_begin;
							tsk->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							tsk->Y_begin = Y_begin;
							tsk->Y_end = Y_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
                        if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z_begin,Z_end) ) goto exit;
							tsk->Z_begin = Z_begin;
							tsk->Z_end = Z_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( !df->skipRealArray() ) goto exit;
						if ( !df->readWord() ) goto exit;		
						continue;
					}
					
					if ( !df->skipArray(false) ) goto exit;
				}
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						tsk->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(tsk->X_begin != NULL) &&
				(tsk->X_end != NULL) &&
				(tsk->Y_begin != NULL) &&
				(tsk->Y_end != NULL) &&
                (tsk->Z_begin != NULL) &&
				(tsk->Z_end != NULL) &&
				((tsk->X_end - tsk->X_begin) == (tsk->Y_end - tsk->Y_begin)) &&
                ((tsk->X_end - tsk->X_begin) == (tsk->Z_end - tsk->Z_begin))
				) 
			{
				if (!taskname) {
					return tsk;
				} else {
					if (tsk->getName()) {
						if ( strcmp(tsk->getName(),taskname) == 0 ) {
							return tsk;
						} else {
							tsk = new task();
						}
					}
				}
			}
		} else {
			if (!taskname)
				writelog(SURFIT_ERROR, "task_load : this file have no task");
			else
				writelog(SURFIT_ERROR, "task_load : this file have no task with name %s", taskname);
			delete tsk;
			return NULL;
		}
	};

exit:
	delete tsk;
	writelog(SURFIT_ERROR, error);
	return NULL;

};

task * _task_load(const char * filename, const char * taskname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode);
	
	task * tsk = _task_load_df(df, taskname);
	
	if (!tsk)
		goto exit;

	delete df;
	return tsk;

exit:
	delete tsk;
	delete df;
	return NULL;

};

bool _task_write(task * tsk, const char * filename, const char * mask) {
	if (!tsk) {
		writelog(SURFIT_WARNING, "NULL pointer to task.");
		return false;
	};
	return three_columns_write(filename, mask,
		                   tsk->X_begin, tsk->X_end,
				   tsk->Y_begin, tsk->Y_end,
				   tsk->Z_begin, tsk->Z_end);
};

bool _task_save(task * tsk, const char * filename, int mode) {

	if (!tsk) {
		writelog(SURFIT_WARNING, "NULL pointer to task.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _task_save_df(tsk, df);

	bool op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _task_save_df(task * tsk, datafile * df) {

	if (!tsk->getName()) 
		writelog(SURFIT_MESSAGE,"saving task with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving task \"%s\" to file %s",tsk->getName(),df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("task");				res = (op && res);
	if (tsk->getName()) {
		op = df->writeString("name",tsk->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", tsk->X_begin, tsk->size()); res = (op && res);
	op = df->writeRealArray("y", tsk->Y_begin, tsk->size()); res = (op && res);
	op = df->writeRealArray("z", tsk->Z_begin, tsk->size()); res = (op && res);
	op = df->writeEndTag();						res = (op && res);
	
	return res;
};

bool _task_check() {
	if (surfit_task)
		return true;
	return false;
};

void _task_info(task * tsk) {
	if (!tsk) {
		writelog(SURFIT_WARNING, "_task_info : NULL pointer given");
		return;
	}
	if (tsk->getName())
		writelog(SURFIT_MESSAGE,"task (%s) : %d data points.",tsk->getName(), tsk->size());
	else
		writelog(SURFIT_MESSAGE,"task noname : %d data points",tsk->size());
};

task * _get_surfit_task() {
	return surfit_task;
};

void _set_surfit_task(task * tsk) {
	delete surfit_task;
	surfit_task = tsk;
};

void _add_surfit_tasks(task * tsk) {
	if (!tsk)
		return;
	surfit_tasks->push_back(tsk);
};

wtask * _task_to_wtask(task * tsk, REAL weight) {
	if (!tsk)
		return false;

	REAL * X_begin = (REAL*)malloc(tsk->size()*sizeof(REAL));
	REAL * X_end = X_begin + tsk->size();
	memcpy(X_begin, tsk->X_begin, tsk->size()*sizeof(REAL));
	
	REAL * Y_begin = (REAL*)malloc(tsk->size()*sizeof(REAL));
	REAL * Y_end = Y_begin + tsk->size();
	memcpy(Y_begin, tsk->Y_begin, tsk->size()*sizeof(REAL));

	REAL * Z_begin = (REAL*)malloc(tsk->size()*sizeof(REAL));
	REAL * Z_end = Z_begin + tsk->size();
	memcpy(Z_begin, tsk->Z_begin, tsk->size()*sizeof(REAL));

	REAL * W_begin = (REAL*)malloc(tsk->size()*sizeof(REAL));
	REAL * W_end = W_begin + tsk->size();
	int i;
	for (i = 0; i < tsk->size(); i++) {
		*(W_begin + i) = weight;
	}

	wtask * wtsk = new wtask(X_begin, X_end,
		Y_begin, Y_end,
		Z_begin, Z_end,
		W_begin, W_end,
		tsk->getName());

	return wtsk;

};

}; // namespace surfit;


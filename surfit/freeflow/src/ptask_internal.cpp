
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


#include "flow_ie.h"
#include "ptask.h"
#include "ptask_internal.h"
#include "read_txt.h"
#include "vec.h"
#include "fileio.h"
#include "datafile.h"
#include "variables.h"
#include "sort_alg.h"

#include "ptask_user.h"

#include <string.h>
#include <algorithm>

namespace surfit {

ptask * _ptask_read(const char * filename, const char * ptaskname, int columns, int col1, int col2, int col3, const char * delimiter, int grow_by) {

	if (ptaskname)
		writelog(SURFIT_MESSAGE,"reading ptask \"%s\" from file %s", ptaskname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading ptask from file %s", filename);

	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;
	REAL * col3_begin, * col3_end;

	if (!three_columns_read(filename, columns, col1, col2, col3, delimiter, grow_by, 
		col1_begin, col1_end,
		col2_begin, col2_end,
		col3_begin, col3_end))
		return NULL;
	
	ptask *res = new ptask(col1_begin, col1_end,
                             col2_begin, col2_end, 
                             col3_begin, col3_end,
                             ptaskname);
	
	return res;
};

ptask * _ptask_load_df(datafile * df, const char * ptaskname) {

	if (!ptaskname)
		writelog(SURFIT_MESSAGE,"loading ptask from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading ptask \"%s\" from file %s", ptaskname, df->get_filename());

	if (!df->condition())
		return NULL;
	
	char error[] = "ptask_load : wrong datafile format";

	ptask * ptsk = new ptask();
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("ptask")) {
			
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
							ptsk->X_begin = X_begin;
							ptsk->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							ptsk->Y_begin = Y_begin;
							ptsk->Y_end = Y_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
                        			if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z_begin,Z_end) ) goto exit;
							ptsk->Z_begin = Z_begin;
							ptsk->Z_end = Z_end;
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
						ptsk->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(ptsk->X_begin != NULL) &&
				(ptsk->X_end != NULL) &&
				(ptsk->Y_begin != NULL) &&
				(ptsk->Y_end != NULL) &&
		                (ptsk->Z_begin != NULL) &&
				(ptsk->Z_end != NULL) &&
				((ptsk->X_end - ptsk->X_begin) == (ptsk->Y_end - ptsk->Y_begin)) &&
                		((ptsk->X_end - ptsk->X_begin) == (ptsk->Z_end - ptsk->Z_begin))
				) 
			{
				if (!ptaskname) {
					return ptsk;
				} else {
					if (ptsk->getName()) {
						if ( strcmp(ptsk->getName(),ptaskname) == 0 ) {
							return ptsk;
						} else {
							ptsk = new ptask();
						}
					}
				}
			}
		} else {
			if (!ptaskname)
				writelog(SURFIT_ERROR, "ptask_load : this file have no ptask");
			else
				writelog(SURFIT_ERROR, "ptask_load : this file have no ptask with name %s", ptaskname);
			delete ptsk;
			return NULL;
		}
	};

exit:
	delete ptsk;
	writelog(SURFIT_ERROR, error);
	return NULL;

};

ptask * _ptask_load(const char * filename, const char * ptaskname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode);
	
	ptask * ptsk = _ptask_load_df(df, ptaskname);
	
	if (!ptsk)
		goto exit;

	delete df;
	return ptsk;

exit:
	delete ptsk; 
	delete df;
	return NULL;

};

bool _ptask_write(ptask * ptsk, const char * filename, const char * mask) {
	if (!ptsk) {
		writelog(SURFIT_WARNING, "NULL pointer to ptask.");
		return false;
	};
	return three_columns_write(filename, mask,
		                   ptsk->X_begin, ptsk->X_end,
				   ptsk->Y_begin, ptsk->Y_end,
				   ptsk->Z_begin, ptsk->Z_end);
};

bool _ptask_save(ptask * ptsk, const char * filename, int mode) {
	if (!ptsk) {
		writelog(SURFIT_WARNING, "NULL pointer to ptask.");
		return false;
	};
	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _ptask_save_df(ptsk, df);

	bool op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _ptask_save_df(ptask * ptsk, datafile * df) {

	if (!ptsk->getName())
		writelog(SURFIT_MESSAGE,"saving ptask to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving ptask \"%s\" to file %s", ptsk->getName(), df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("ptask");				res = (op && res);
	if (ptsk->getName()) {
		op = df->writeString("name",ptsk->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", ptsk->X_begin, ptsk->size()); res = (op && res);
	op = df->writeRealArray("y", ptsk->Y_begin, ptsk->size()); res = (op && res);
	op = df->writeRealArray("z", ptsk->Z_begin, ptsk->size()); res = (op && res);
	op = df->writeEndTag();						res = (op && res);
	
	return res;
};

bool _ptask_check() {
	if (flow_ptask)
		return true;
	return false;
};

void _sort_ptask(ptask * ptsk, 
		 std::vector<unsigned int> * nums,
		 REAL **& sortx_begin, 
		 REAL **& sortx_end, 
		 REAL **& sorty_begin, 
		 REAL **& sorty_end) {

	_sort_points(ptsk, nums,
		     sortx_begin, sortx_end,
		     sorty_begin, sorty_end);
};

void _ptask_info(ptask * ptsk) {
	if (!ptsk) {
		writelog(SURFIT_WARNING, "_ptask_info : NULL pointer given");
		return;
	}
	if (ptsk->getName())
		writelog(SURFIT_MESSAGE,"ptask (%s) : %d data points.",ptsk->getName(), ptsk->size());
	else
		writelog(SURFIT_MESSAGE,"ptask noname : %d data points",ptsk->size());
};

void _ptask_transform(ptask * ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_points_transform(ptsk, shiftX, scaleX, shiftY, scaleY);
	
};

void _inverse_ptask_transform(ptask * ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY) {
	_inverse_points_transform(ptsk, shiftX, scaleX, shiftY, scaleY);
};

ptask * _get_flow_ptask() {
	return flow_ptask;
};

void _set_flow_ptask(ptask * ptsk) {
	delete flow_ptask;
	flow_ptask = ptsk;
};

void _add_flow_ptasks(ptask * ptsk) {
	if (!ptsk)
		return;
	flow_ptasks->push_back(ptsk);
};
                    
}; // namespace surfit;



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
#include "wtask.h"
#include "wtask_internal.h"
#include "read_txt.h"
#include "vec.h"
#include "fileio.h"
#include "datafile.h"

#include "wtask_user.h"

namespace surfit {

wtask * _wtask_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, int col4, const char * delimiter, int grow_by) {

	if (taskname)
		writelog(SURFIT_MESSAGE,"reading wtask \"%s\" from file %s", taskname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading wtask from file %s", filename);

	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;
	REAL * col3_begin, * col3_end;
	REAL * col4_begin, * col4_end;

	if (!four_columns_read(filename, columns, col1, col2, col3, col4, delimiter, grow_by, 
		col1_begin, col1_end,
		col2_begin, col2_end,
		col3_begin, col3_end,
		col4_begin, col4_end))
		return NULL;
	
	wtask *res = new wtask(col1_begin, col1_end,
                           col2_begin, col2_end, 
                           col3_begin, col3_end,
						   col4_begin, col4_end,
                           taskname);
	
	return res;
};

wtask * _wtask_load_df(datafile * df, const char * taskname) {

	if (!taskname)
		writelog(SURFIT_MESSAGE,"loading wtask from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading wtask \"%s\" from file %s", taskname, df->get_filename());

	if (!df->condition())
		return NULL;
	
	char error[] = "wtask_load : wrong datafile format";

	wtask * wtsk = new wtask();
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("wtask")) {
			
			df->skipTagName();
			
			REAL * X_begin = NULL;
			REAL * X_end = NULL;
			REAL * Y_begin = NULL;
			REAL * Y_end = NULL;
			REAL * Z_begin = NULL;
			REAL * Z_end = NULL;
			REAL * W_begin = NULL;
			REAL * W_end = NULL;
			
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
							wtsk->X_begin = X_begin;
							wtsk->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							wtsk->Y_begin = Y_begin;
							wtsk->Y_end = Y_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
                        if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z_begin,Z_end) ) goto exit;
							wtsk->Z_begin = Z_begin;
							wtsk->Z_end = Z_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("w") ) {
							if ( !df->readRealArray(W_begin,W_end) ) goto exit;
							wtsk->W_begin = W_begin;
							wtsk->W_end = W_end;
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
						wtsk->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(wtsk->X_begin != NULL) &&
				(wtsk->X_end != NULL) &&
				(wtsk->Y_begin != NULL) &&
				(wtsk->Y_end != NULL) &&
                		(wtsk->Z_begin != NULL) &&
				(wtsk->Z_end != NULL) &&
				(wtsk->W_begin != NULL) &&
				(wtsk->W_end != NULL) &&
				((wtsk->X_end - wtsk->X_begin) == (wtsk->Y_end - wtsk->Y_begin)) &&
				((wtsk->X_end - wtsk->X_begin) == (wtsk->W_end - wtsk->W_begin)) &&
                		((wtsk->X_end - wtsk->X_begin) == (wtsk->Z_end - wtsk->Z_begin))
				) 
			{
				if (!taskname) {
					return wtsk;
				} else {
					if (wtsk->getName()) {
						if ( strcmp(wtsk->getName(),taskname) == 0 ) {
							return wtsk;
						} else {
							wtsk = new wtask();
						}
					}
				}
			}
		} else {
			if (!taskname)
				writelog(SURFIT_ERROR, "wtask_load : this file have no wtask");
			else
				writelog(SURFIT_ERROR, "wtask_load : this file have no wtask with name %s", taskname);
			delete wtsk;
			return NULL;
		}
	};

exit:
	delete wtsk;
	writelog(SURFIT_ERROR, error);
	return NULL;

};

wtask * _wtask_load(const char * filename, const char * taskname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode);
	
	wtask * wtsk = _wtask_load_df(df, taskname);
	
	if (!wtsk)
		goto exit;

	delete df;
	return wtsk;

exit:
	delete wtsk; 
	delete df;
	return NULL;

};

bool _wtask_write(wtask * wtsk, const char * filename, const char * mask) {
	if (!wtsk) {
		writelog(SURFIT_WARNING, "NULL pointer to wtask.");
		return false;
	};
	return four_columns_write(filename, mask,
		                  wtsk->X_begin, wtsk->X_end,
				  wtsk->Y_begin, wtsk->Y_end,
				  wtsk->Z_begin, wtsk->Z_end,
				  wtsk->W_begin, wtsk->W_end);
};

bool _wtask_save(wtask * wtsk, const char * filename, int mode) {
	if (!wtsk) {
		writelog(SURFIT_WARNING, "NULL pointer to wtask.");
		return false;
	};
	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _wtask_save_df(wtsk, df);

	bool op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _wtask_save_df(wtask * wtsk, datafile * df) {

	if (!wtsk->getName()) 
		writelog(SURFIT_MESSAGE,"saving wtask with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving wtask \"%s\" to file %s",wtsk->getName(),df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("wtask");				res = (op && res);
	if (wtsk->getName()) {
		op = df->writeString("name",wtsk->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", wtsk->X_begin, wtsk->size()); res = (op && res);
	op = df->writeRealArray("y", wtsk->Y_begin, wtsk->size()); res = (op && res);
	op = df->writeRealArray("z", wtsk->Z_begin, wtsk->size()); res = (op && res);
	op = df->writeRealArray("w", wtsk->W_begin, wtsk->size()); res = (op && res);
	op = df->writeEndTag();						res = (op && res);
	
	return res;
};

bool _wtask_check() {
	if (surfit_wtask)
		return true;
	return false;
};

void _wtask_info(wtask * wtsk) {
	if (!wtsk) {
		writelog(SURFIT_WARNING, "_wtask_info : NULL pointer given");
		return;
	}
	if (wtsk->getName())
		writelog(SURFIT_MESSAGE,"wtask (%s) : %d data points.",wtsk->getName(), wtsk->size());
	else
		writelog(SURFIT_MESSAGE,"wtask noname : %d data points",wtsk->size());
};

wtask * _get_surfit_wtask() {
	return surfit_wtask;
};

void _set_surfit_wtask(wtask * wtsk) {
	delete surfit_wtask;
	surfit_wtask = wtsk;
};

void _add_surfit_wtasks(wtask * wtsk) {
	if (!wtsk)
		return;
	surfit_wtasks->push_back(wtsk);
};

wtask * _collect_all_wtasks() {
        
	wtask * res = NULL;

	vec * X = new vec;
	vec * Y = new vec;
	vec * Z = new vec;
	vec * W = new vec;

	if (surfit_wtask) {
		X->resize(surfit_wtask->size());
		memcpy(X->begin(), surfit_wtask->X_begin, surfit_wtask->size()*sizeof(REAL));
		Y->resize(surfit_wtask->size());
		memcpy(Y->begin(), surfit_wtask->Y_begin, surfit_wtask->size()*sizeof(REAL));
		Z->resize(surfit_wtask->size());
		memcpy(Z->begin(), surfit_wtask->Z_begin, surfit_wtask->size()*sizeof(REAL));
		W->resize(surfit_wtask->size());
		memcpy(W->begin(), surfit_wtask->W_begin, surfit_wtask->size()*sizeof(REAL));
	}

	unsigned int i;
	int prev_size;

	for (i = 0; i < surfit_wtasks->size(); i++) {
		prev_size = X->size();
		wtask * wtsk = *(surfit_wtasks->begin()+i);
		if (!wtsk)
			continue;
		X->resize(wtsk->size()+prev_size);
		memcpy(X->begin()+prev_size, wtsk->X_begin, wtsk->size()*sizeof(REAL));
		Y->resize(wtsk->size()+prev_size);
		memcpy(Y->begin()+prev_size, wtsk->Y_begin, wtsk->size()*sizeof(REAL));
		Z->resize(wtsk->size()+prev_size);
		memcpy(Z->begin()+prev_size, wtsk->Z_begin, wtsk->size()*sizeof(REAL));
		W->resize(wtsk->size()+prev_size);
		memcpy(W->begin()+prev_size, wtsk->W_begin, wtsk->size()*sizeof(REAL));
	};

	if (X->size() > 0) {
		res = new wtask(X->ref_begin(), X->end(), 
			            Y->ref_begin(), Y->end(),
						Z->ref_begin(), Z->end(),
						W->ref_begin(), W->end(),
						"All wtasks");
	}

	delete X;
	delete Y;
	delete Z;
	delete W;

	return res;

};

}; // namespace surfit;


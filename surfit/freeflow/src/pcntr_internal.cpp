
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
#include "pcntr.h"
#include "pcntr_internal.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"

#include "pcntr_user.h"

namespace surfit {

bool _pcntr_check() {
	if (flow_pcntr)
		return true;
	return false;
};

bool _pcntr_unload() {
	if (!_pcntr_check())
		return false;
	delete flow_pcntr;
	flow_pcntr = NULL;
	return true;
};

pcntr * _pcntr_read(const char * filename, const char * pcntrname,
		    int columns, 
		    int col1, int col2, int col3, 
		    int grow_by, const char * mask) 
{
	REAL * col1_begin, * col1_end;
	REAL * col2_begin, * col2_end;
	REAL * col3_begin, * col3_end;

	if (pcntrname)
		writelog(SURFIT_MESSAGE,"reading contour \"%s\" from file %s", pcntrname, filename);
	else 
		writelog(SURFIT_MESSAGE,"reading contour from file %s", filename);

	if (!three_columns_read(filename, columns, col1, col2, col3, mask, grow_by,
		col1_begin, col1_end,
		col2_begin, col2_end,
		col3_begin, col3_end))
		return NULL;

	pcntr * res = new pcntr(col1_begin, col1_end,
		                col2_begin, col2_end,
				col3_begin, col3_end,
                                pcntrname);

	return res;
};

bool _pcntr_write(pcntr * pcntrline, const char * filename, const char * mask) {
	if (!pcntrline)
		return false;
	return three_columns_write(filename, mask,
		                   pcntrline->X_begin, pcntrline->X_end,
		                   pcntrline->Y_begin, pcntrline->Y_end,
				   pcntrline->Z_begin, pcntrline->Z_end);
};

bool _pcntr_save(pcntr * contour, const char * filename, int mode) {
	if (!contour) {
		writelog(SURFIT_WARNING, "NULL pointer to pcntr.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE, mode); // write
	if (!df->condition())
		return false;

	bool res = _pcntr_save_df(contour, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _pcntr_save_df(pcntr * contour, datafile * df) {

	if (!contour->getName())
		writelog(SURFIT_MESSAGE,"saving pcntr to file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"saving pcntr \"%s\" to file %s", contour->getName(), df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("pcntr");				res = (op && res);
	if (contour->getName()) {
		op = df->writeString("name",contour->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", contour->X_begin, contour->size()); res = (op && res);
	op = df->writeRealArray("y", contour->Y_begin, contour->size()); res = (op && res);
	op = df->writeRealArray("z", contour->Z_begin, contour->size()); res = (op && res);
	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

pcntr * _pcntr_load_df(datafile * df, const char * pcntrname) {

	if (!pcntrname)
		writelog(SURFIT_MESSAGE,"loading pcntr from file %s", df->get_filename());
	else
		writelog(SURFIT_MESSAGE,"loading pcntr \"%s\" from file %s", pcntrname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "pcntr_load : wrong datafile format";

	pcntr * pcntrline = new pcntr(NULL, NULL, NULL, NULL, NULL, NULL);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("pcntr")) {
			
			df->skipTagName();
			
			REAL * X_begin = NULL;
			REAL * X_end   = NULL;
			REAL * Y_begin = NULL;
			REAL * Y_end   = NULL;
			REAL * Z_begin = NULL;
			REAL * Z_end   = NULL;
            
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
							pcntrline->X_begin = X_begin;
							pcntrline->X_end = X_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y_begin,Y_end) ) goto exit;
							pcntrline->Y_begin = Y_begin;
							pcntrline->Y_end = Y_end;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z_begin,Z_end) ) goto exit;
							pcntrline->Z_begin = Z_begin;
							pcntrline->Z_end = Z_end;
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
						pcntrline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(pcntrline->X_begin != NULL) &&
				(pcntrline->X_end != NULL) &&
				(pcntrline->Y_begin != NULL) &&
				(pcntrline->Y_end != NULL) &&
				(pcntrline->Z_begin != NULL) &&
				(pcntrline->Z_end != NULL) &&
		                ((pcntrline->X_end - pcntrline->X_begin) == (pcntrline->Y_end - pcntrline->Y_begin)) &&
				((pcntrline->X_end - pcntrline->X_begin) == (pcntrline->Z_end - pcntrline->Z_begin))
                	   ) 
			{
				if (!pcntrname) {
					return pcntrline;
				} else {
					if (pcntrline->getName()) {
						if ( strcmp(pcntrline->getName(),pcntrname) == 0 ) {
							return pcntrline;
						} else {
							delete pcntrline;
							pcntrline = new pcntr(NULL, NULL, NULL, NULL, NULL, NULL);
						}
					}
				}
			}
		} else {
			if (!pcntrname)
				writelog(SURFIT_ERROR, "pcntr_load : this file have no pcntrs");
			else
				writelog(SURFIT_ERROR, "pcntr_load : this file have no pcntr with name %s", pcntrname);
			delete pcntrline;
			return NULL;
		}
	};

exit:
	delete pcntrline; 
	writelog(SURFIT_ERROR, error);
	return NULL;

};

pcntr * _pcntr_load(const char * filename, const char * pcntrname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode);
	
	pcntr * pcntrline = _pcntr_load_df(df, pcntrname);

	if (!pcntrline)
		goto exit;

	delete df;
	return pcntrline;
	
exit:
	delete pcntrline; 
	delete df;
	return NULL;

};

void _pcntr_info(pcntr * pcntrline) {
	if (!pcntrline) {
		writelog(SURFIT_WARNING, "_pcntr_info : NULL pointer given");
		return;
	}
	if (pcntrline->getName()) {
		writelog(SURFIT_MESSAGE,"pcntr (%s) ",pcntrline->getName());
	} else {
		writelog(SURFIT_MESSAGE,"pcntr noname");
	}
};

pcntr * _get_flow_pcntr() {
	return flow_pcntr;
};

void _set_flow_pcntr(pcntr * contour) {
	delete flow_pcntr;
	flow_pcntr = contour;
};

void _add_flow_pcntrs(pcntr * contour) {
	if (!contour)
		return;
	flow_pcntrs->push_back(contour);
};

}; // namespace surfit;


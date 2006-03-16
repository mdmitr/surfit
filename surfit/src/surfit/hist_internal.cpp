
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

#include "surfit_ie.h"

#include "fileio.h"
#include "datafile.h"
#include "vec.h"
#include "read_txt.h"

#include "hist.h"
#include "hist_internal.h"

namespace surfit {

d_hist * _hist_read(const char * filename, const char * histname,
		    int col1, int col2, int col3, int skip_lines,
		    int grow_by, const char * mask) 
{
	vec * vcol1;
	vec * vcol2;
	vec * vcol3;

	if (histname)
		writelog(LOG_MESSAGE,"reading histogramm \"%s\" from file %s", histname, filename);
	else 
		writelog(LOG_MESSAGE,"reading histogramm from file %s", filename);

	if (!three_columns_read(filename, col1, col2, col3, skip_lines, mask, grow_by,
			        vcol1, vcol2, vcol3))
		return NULL;

	d_hist * res = create_hist(vcol1, vcol2, vcol3,
			           histname);

	return res;
};

bool _hist_write(const d_hist * histline, const char * filename, const char * mask) {
	if (!histline)
		return false;
	return three_columns_write(filename, mask,
				   histline->X1, histline->X2, histline->Z);
};

bool _hist_save(const d_hist * hst, const char * filename) {
	if (!hst) {
		writelog(LOG_WARNING, "NULL pointer to hist.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition())
		return false;

	bool res = _hist_save_df(hst, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _hist_save_df(const d_hist * hst, datafile * df) {

	if (!hst->getName())
		writelog(LOG_MESSAGE,"saving histogramm to file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"saving histogramm \"%s\" to file %s", hst->getName(), df->get_filename());
	
	bool res = true;
	bool op;
	if (hst->size() == 0) {
		writelog(LOG_WARNING, "Empty histogramm");
		return false;
	}

	op = df->writeTag("hist");				res = (op && res);
	if (hst->getName()) {
		op = df->writeString("name",hst->getName());  res = (op && res);
	}
	op = df->writeRealArray("x1", hst->X1); res = (op && res);
	op = df->writeRealArray("x2", hst->X2); res = (op && res);
	op = df->writeRealArray("z", hst->Z); res = (op && res);
	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

d_hist * _hist_load_df(datafile * df, const char * histname) {

	if (!histname)
		writelog(LOG_MESSAGE,"loading histogramm from file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"loading histogramm \"%s\" from file %s", histname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "hist_load : wrong datafile format";

	d_hist * histline = create_hist(NULL, NULL, NULL);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("hist")) {
			
			df->skipTagName();
			
			vec * X1 = NULL;
			vec * X2 = NULL;
			vec * Z = NULL;
			
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord("array") ) {
					// read array type
					if (!df->readWord()) goto exit;
					
					if ( df->isWord(REAL_NAME) ) {
						
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("x1") ) {
							if ( !df->readRealArray(X1) ) goto exit;
							histline->X1 = X1;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("x2") ) {
							if ( !df->readRealArray(X2) ) goto exit;
							histline->X2 = X2;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z) ) goto exit;
							histline->Z = Z;
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
						histline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(histline->X1 != NULL) &&
				(histline->X2 != NULL) &&
				(histline->Z != NULL) &&
				((histline->X1->size()) == (histline->Z->size())) &&
				((histline->X2->size()) == (histline->Z->size()))
			   ) 
			{
				if (!histname) {
					return histline;
				} else {
					if (histline->getName()) {
						if ( strcmp(histline->getName(),histname) == 0 ) {
							return histline;
						} else {
							if (histline)
								histline->release();
							histline = create_hist(NULL, NULL, NULL);
						}
					}
				}
			}
		} else {
			if (!histname)
				writelog(LOG_ERROR, "hist_load : this file have no hists");
			else
				writelog(LOG_ERROR, "hist_load : this file have no hist with name %s", histname);
			if (histline)
				histline->release();
			return NULL;
		}
	};

exit:
	if (histline)
		histline->release(); 
	writelog(LOG_ERROR, error);
	return NULL;

};

d_hist * _hist_load(const char * filename, const char * histname) {

	datafile * df = new datafile(filename, DF_MODE_READ);
	
	d_hist * histline = _hist_load_df(df, histname);

	if (!histline)
		goto exit;

	delete df;
	return histline;
	
exit:
	if (histline)
		histline->release(); 
	delete df;
	return NULL;

};

void _hist_info(const d_hist * histline) {
	if (!histline) {
		writelog(LOG_WARNING, "_hist_info : NULL pointer given");
		return;
	}
	if (histline->getName()) {
		writelog(LOG_MESSAGE,"hist (%s)",histline->getName());
	} else {
		writelog(LOG_MESSAGE,"hist noname");	
	}
};

void _add_surfit_hists(d_hist * hst) {
	if (!hst)
		return;
	surfit_hists->push_back(hst);
};

}; // namespace surfit;


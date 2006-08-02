
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

#include "sstuff.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "vec.h"
#include "strvec.h"

#include <string.h>
#include <assert.h>

#include "points.h"
#include "pnts_internal.h"
#include "sort_alg.h"
#include "free_elements.h"
#include "grid.h"

#include <algorithm>

namespace surfit {

d_points * _pnts_read(const char * filename, const char * pntsname, int col1, int col2, int col3, int col4, const char * delimiter, int skip_lines, int grow_by) {

	if (pntsname)
		writelog(LOG_MESSAGE,"reading points \"%s\" from file %s", pntsname, filename);
	else 
		writelog(LOG_MESSAGE,"reading points from file %s", filename);

	vec * vcol1 = NULL;
	vec * vcol2 = NULL;
	vec * vcol3 = NULL;
	strvec * names = NULL;
	d_points * res = NULL;

	if (col4 == 0) {
		if (!three_columns_read(filename, col1, col2, col3, skip_lines, delimiter, grow_by, 
			vcol1, vcol2, vcol3))
			return NULL;
		
		res = create_points(vcol1, vcol2, vcol3, pntsname);
	} else {
		
		if (!three_columns_read_with_names(filename, col1, col2, col3, col4, 
						   skip_lines, delimiter, grow_by, 
						   vcol1, vcol2, vcol3, names))
			return NULL;
		
		res = create_points(vcol1, vcol2, vcol3, names, pntsname);
	}

	if (pntsname == NULL) {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}
	
	return res;
};

d_points * _pnts_load_df(datafile * df, const char * pntsname) {

	if (!pntsname)
		writelog(LOG_MESSAGE,"loading points from file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"loading points \"%s\" from file %s", pntsname, df->get_filename());

	if (!df->condition())
		return NULL;
	
	char error[] = "pnts_load : wrong datafile format";

	d_points * pnts = create_points_default();
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("points")) {
			
			df->skipTagName();
			
			vec * X = NULL;
			vec * Y = NULL;
			vec * Z = NULL;
			strvec * names = NULL;
			
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord("array") ) {
					// read array type
					if (!df->readWord()) goto exit;
					
					if ( df->isWord(REAL_NAME) ) {
						
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("x") ) {
							if ( !df->readRealArray(X) ) goto exit;
							pnts->X = X;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y) ) goto exit;
							pnts->Y = Y;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z) ) goto exit;
							pnts->Z = Z;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( !df->skipRealArray() ) goto exit;
						if ( !df->readWord() ) goto exit;		
						continue;
					}

					if ( df->isWord("string") ) {
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("names") ) {
							if ( !df->readStringArray(names) ) goto exit;
							pnts->names = names;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( !df->skipStringArray() ) goto exit;
						if ( !df->readWord() ) goto exit;
						continue;
					};
					
					if ( !df->skipArray(false) ) goto exit;
				}
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						pnts->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(pnts->X != NULL) &&
				(pnts->Y != NULL) &&
				(pnts->Z != NULL) &&
				((pnts->X->size()) == (pnts->Y->size())) &&
				((pnts->X->size()) == (pnts->Z->size()))
				) 
			{
				if (!pntsname) {
					return pnts;
				} else {
					if (pnts->getName()) {
						if ( strcmp(pnts->getName(),pntsname) == 0 ) {
							return pnts;
						} else {
							pnts = create_points_default();
						}
					}
				}
			}
		} else {
			if (!pntsname)
				writelog(LOG_ERROR, "pnts_load : this file have no pnts");
			else
				writelog(LOG_ERROR, "pnts_load : this file have no task with name %s", pntsname);
			if (pnts)
				pnts->release();
			return NULL;
		}
	};

exit:
	if (pnts)
		pnts->release();
	writelog(LOG_ERROR, error);
	return NULL;

};

d_points * _pnts_load(const char * filename, const char * pntsname) {

	datafile * df = new datafile(filename, DF_MODE_READ);
	
	d_points * pnts = _pnts_load_df(df, pntsname);
	
	if (!pnts)
		goto exit;

	delete df;
	return pnts;

exit:
	if (pnts)
		pnts->release();
	delete df;
	return NULL;

};

bool _pnts_write(const d_points * pnts, const char * filename, const char * mask) {
	if (!pnts) {
		writelog(LOG_WARNING, "NULL pointer to points.");
		return false;
	};
	if (pnts->size() == 0) {
		writelog(LOG_WARNING, "No points to save.");
		return false;
	}
	return three_columns_write(filename, mask,
		                   pnts->X, pnts->Y, pnts->Z);
};

bool _pnts_save(const d_points * pnts, const char * filename) {

	if (!pnts) {
		writelog(LOG_WARNING, "NULL pointer to points.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition())
		return false;

	bool res = _pnts_save_df(pnts, df);

	bool op = df->writeEof();						res = (op && res);
	
	delete df;
	return res;
};

bool _pnts_save_df(const d_points * pnts, datafile * df) {

	if (pnts->size() == 0) {
		writelog(LOG_MESSAGE,"No points to save");
		return false;
	}

	if (!pnts->getName()) 
		writelog(LOG_MESSAGE,"saving points with no name to file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"saving points \"%s\" to file %s",pnts->getName(),df->get_filename());

	bool res = true;
	bool op;

	op = df->writeTag("points");				res = (op && res);
	if (pnts->getName()) {
		op = df->writeString("name",pnts->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", pnts->X); res = (op && res);
	op = df->writeRealArray("y", pnts->Y); res = (op && res);
	op = df->writeRealArray("z", pnts->Z); res = (op && res);
	if (pnts->names)
		op = df->writeStringArray("names", pnts->names); res = (op && res);
	op = df->writeEndTag();						res = (op && res);
	
	return res;
};

void _pnts_info(const d_points * pnts) {
	if (!pnts) {
		writelog(LOG_WARNING, "_pnts_info : NULL pointer given");
		return;
	}
	if (pnts->getName())
		writelog(LOG_MESSAGE,"points (%s) : %d data points.",pnts->getName(), pnts->size());
	else
		writelog(LOG_MESSAGE,"points noname : %d data points",pnts->size());
};

bool ptr_sub_points_less(sub_points * it1, sub_points * it2) {
	return (it1)->cell_number < (it2)->cell_number;
};

void free_scattered_points(std::vector<sub_points *> * proc_sub_tsks) {
	release_elements(proc_sub_tsks->begin(), proc_sub_tsks->end());
	delete proc_sub_tsks;
};

void prepare_scattered_points(const d_points * pnts, 
                              std::vector<sub_points *> *& proc_sub_tsks)
{
	if (!pnts)
		return;
	
	std::vector<size_t> * point_numbers = new std::vector<size_t>( pnts->size() );
	
	int point_counter;
	for (point_counter = 0; point_counter < pnts->size(); point_counter++) {
		*( point_numbers->begin() + point_counter ) = point_counter;
	}
	
	sub_points * sub_tsk = new sub_points(0, point_numbers);
	
	proc_sub_tsks = new std::vector<sub_points *>(1);
	(*proc_sub_tsks)[0] = sub_tsk;
};

void bind_points_to_grid(d_grid *& old_grid, 
			 const d_points * pnts,
			 std::vector<sub_points *> *& old_pnts,
			 d_grid *& grd)
{
	std::vector<sub_points *>::iterator it;
	REAL x_from, x_to, y_from, y_to;
	size_t i,j;
	size_t node;

	size_t old_size = old_pnts->size();

	std::vector<sub_points *> * tasks = new std::vector<sub_points *>;
	tasks->reserve(old_size);
	
	std::vector<size_t> * nums = new std::vector<size_t>;
	size_t nums_size;
	
	for (it = old_pnts->begin(); it != old_pnts->end(); it++) {
		
		size_t total_size = 0;
		sub_points * old_sub_points = *it;
		
		REAL minx, maxx, miny, maxy;
		old_sub_points->bounds(minx, maxx, miny, maxy, pnts);
		
		REAL ** sortx_begin = NULL;
		REAL ** sortx_end   = NULL;
		REAL ** sorty_begin = NULL;
		REAL ** sorty_end   = NULL;
		
		_sort_points(pnts, old_sub_points->point_numbers,
			sortx_begin, sortx_end, sorty_begin, sorty_end);
		
		size_t old_node = old_sub_points->cell_number;
		i = old_node % old_grid->getCountX();
		j = (old_node -i)/old_grid->getCountX();
		
		size_t i_from = grd->get_i(minx);
		size_t i_to   = grd->get_i(maxx);
		size_t j_from = grd->get_j(miny);
		size_t j_to   = grd->get_j(maxy);
		
		if (maxx <= grd->startX + (i_to + REAL(0.5))*grd->stepX)
			i_to++;
		if (maxy <= grd->startY + (j_to + REAL(0.5))*grd->stepY)
			j_to++;
		
		old_size = old_sub_points->point_numbers->size();
		
		for (i = i_from; i <= i_to; i++) {
			
			x_from = grd->startX + (i - REAL(0.5))*grd->stepX;
			x_to   = grd->startX + (i + REAL(0.5))*grd->stepX;
			
			if (i == i_from)
				x_from = MIN(x_from, minx);
			if (i == i_to)
				x_to = MAX(x_to, maxx);
			
			for (j = j_from; j <= j_to; j++) {
				
				y_from = grd->startY + (j - REAL(0.5))*grd->stepY;
				y_to   = grd->startY + (j + REAL(0.5))*grd->stepY;
				
				if (j == j_from)
					y_from = MIN(y_from, miny);
				if (j == j_to)
					y_to = MAX(y_to, maxy);
				
				getPointsInRect(x_from, x_to, y_from, y_to,
					sortx_begin, sortx_end,
					sorty_begin, sorty_end,
					pnts->X->begin(), pnts->Y->begin(),
					*nums);
				
				nums_size = nums->size();
				total_size += nums_size;
				
				if (nums_size > 0) {
					
					node = i+j*grd->getCountX();
					
					sub_points * new_sub_points = new sub_points(node, nums);
					tasks->push_back(new_sub_points);
					
					nums = new std::vector<size_t>;
				}
				
				if (total_size == old_size)
					break;
			}
			
			if (total_size == old_size)
				break;
		}
		if (total_size != old_size)
			assert(0);
		if (*it)
			(*it)->release();
		*it = NULL;
		
		free(sortx_begin);
		free(sorty_begin);
		
	}
	
	delete old_pnts;
	old_pnts = tasks;
	
	delete nums;
	
	std::sort(tasks->begin(), tasks->end(), ptr_sub_points_less);

};

void _surfit_pnts_add(d_points * pnts) {
	surfit_pnts->push_back(pnts);
};


}; // namespace surfit;


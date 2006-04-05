
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

#include <string.h>
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
	
	std::vector<unsigned int> * point_numbers = new std::vector<unsigned int>( pnts->size() );
	
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
	REAL oldx_from, oldx_to, oldy_from, oldy_to;
	REAL x_from, x_to, y_from, y_to;
	int i,j;
	int node;

	int old_size = old_pnts->size();

	std::vector<sub_points *> * tasks = new std::vector<sub_points *>;
	tasks->reserve(old_size);

	std::vector<unsigned int> * nums = new std::vector<unsigned int>;
	int nums_size;
	
	for (it = old_pnts->begin(); it != old_pnts->end(); it++) {

		int total_size = 0;
		sub_points * old_sub_points = *it;

		REAL ** sortx_begin = NULL;
		REAL ** sortx_end   = NULL;
		REAL ** sorty_begin = NULL;
		REAL ** sorty_end   = NULL;

		_sort_points(pnts, old_sub_points->point_numbers,
			     sortx_begin, sortx_end, sorty_begin, sorty_end);

		int old_node = old_sub_points->cell_number;
		i = old_node % old_grid->getCountX();
		j = (old_node -i)/old_grid->getCountX();

		// ????? ???????????? ??????points
		oldx_from = old_grid->startX + (old_grid->endX - old_grid->startX)/REAL(old_grid->getCountX()-1)*REAL(i-0.5);
		oldx_to   = old_grid->startX + (old_grid->endX - old_grid->startX)/REAL(old_grid->getCountX()-1)*REAL(i+0.5);
		oldy_from = old_grid->startY + (old_grid->endY - old_grid->startY)/REAL(old_grid->getCountY()-1)*REAL(i-0.5);
		oldy_to   = old_grid->startY + (old_grid->endY - old_grid->startY)/REAL(old_grid->getCountY()-1)*REAL(i+0.5);
		
		int prop_coeff_x = grd->getCountX()/old_grid->getCountX();
		int prop_coeff_y = grd->getCountY()/old_grid->getCountY();

		int i_from = i*prop_coeff_x;
		int i_to = i_from + prop_coeff_x-1;
		if (old_grid->stepX == grd->stepX) {
			i_from = i;
			i_to = i;
		}
		int j_from = j*prop_coeff_y;
		int j_to = j_from + prop_coeff_y-1;
		if (old_grid->stepY == grd->stepY) {
			j_from = j;
			j_to = j;
		}

		old_size = old_sub_points->point_numbers->size();
					
		for (i = i_from; i <= i_to; i++) {
			
			x_from = grd->startX + (i - REAL(0.5))*grd->stepX;
			x_to   = grd->startX + (i + REAL(0.5))*grd->stepX;

			for (j = j_from; j <= j_to; j++) {
				y_from = grd->startY + (j - REAL(0.5))*grd->stepY;
				y_to   = grd->startY + (j + REAL(0.5))*grd->stepY;
				
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
					
					nums = new std::vector<unsigned int>;
				}
				
				if (total_size == old_size)
					break;
			}

			if (total_size == old_size)
					break;
		}
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


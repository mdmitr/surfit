
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

#ifndef __surfit_freeflow_file_included__
#define __surfit_freeflow_file_included__

#include "data_manager.h"

namespace surfit {

//! serves file_load, file_save, clear_data and mem_info commands for libfreeflow
class freeflow_manager : public manager {
public:
	
	bool auto_load(const char * filename, const char * first1024, int readed) const;
	int load_tag(datafile *df, char * tag_name) const;
	bool save(datafile *df) const;
	void release();
	void clear_data() const;
	void mem_info() const;
	char * types_info() const;
#ifdef HAVE_GL_WORKS
	void mem_show() const;
	bool check_for_drawing(const char * type) const;
#endif
	int data_count() const;
	const data * data_get(int i) const;
	const char * getName() const {return "freeflow";};

};

}; // namespace surfit;

#endif



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

#ifndef __surfit_freeflow_file_included__
#define __surfit_freeflow_file_included__

#include "file_manager.h"

namespace surfit {

/*! \class freeflow_manager
    \brief serves \ref file_load, \ref file_save, \ref clear_data and \ref mem_info commands for libfreeflow
*/
class freeflow_manager : public manager {
public:
	
	int load_tag(datafile *df, char * tag_name) const;
	bool save(datafile *df) const;
	void clear_data() const;
	void mem_info() const;
#ifdef HAVE_GL_WORKS
	void mem_show() const;
	bool check_for_drawing(const char * type) const;
	void getMinMaxZ(REAL & minZ, REAL & maxZ) const;
#endif
	void release();
	int data_count() const;
	const data * data_get(int i) const;

};

}; // namespace surfit;

#endif


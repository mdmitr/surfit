
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

#ifndef __surfit_freeglobe_file_included__
#define __surfit_freeglobe_file_included__

#include "data_manager.h"

namespace surfit {

/*! \class freeglobe_manager
    \brief serves \ref file_load, \ref file_save, \ref clear_data and \ref mem_info commands for libfreeglobe
*/
class globe_manager : public manager {
protected:
	~globe_manager() {};
public:
	bool auto_load(const char * filename, const char * first1024, int readed) const;
	int load_tag(datafile *df, char * tag_name) const;
	bool save(datafile *df) const;
	void clear_data() const;
	void mem_info() const;
	char * types_info() const;
	void release();
	int data_count() const;
	const data * data_get(int i) const;
	const char * getName() const {return "globe";};
};

}; // namespace surfit;

#endif


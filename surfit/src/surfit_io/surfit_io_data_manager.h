
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

#ifndef __surfit_surfit_io_file_included__
#define __surfit_surfit_io_file_included__

#include "data_manager.h"

namespace surfit {

/*! \class freesurfit_io_manager
    \brief serves \ref file_load, \ref file_save, \ref clear_data and \ref mem_info commands for libfreesurfit_io
*/
class surfit_io_manager : public manager {
protected:
	~surfit_io_manager() {};
public:
	bool auto_load(const char * filename, const char * first1024, int readed) const;
	void release();
	const char * getName() const {return "surfit_io";};
};

}; // namespace surfit;

#endif


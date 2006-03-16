
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

#ifndef __surfit_load_file_included__
#define __surfit_load_file_included__

#include <vector>

namespace surfit {

class datafile;
class data;

///////////////
// file

SURFIT_EXPORT
/*! \ingroup tcl_file
    \fn char * file_info(const char * filename);
    \brief prints info about file contents
*/
char * file_info(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_file
    \fn void file_load(const char * filename);
    \brief loads all data from ROFF file (see \ref datafile for details)
*/
void file_load(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl_file
    \fn bool file_save(const char * filename);
    \brief saves all data from ROFF file (see \ref datafile for details)
*/
bool file_save(const char * filename);

SURFIT_EXPORT
/*! \ingroup tcl
    \fn void clear_data();
    \brief removes all data from memory
*/
void clear_data();

SURFIT_EXPORT
/*! \ingroup tcl
    \fn void mem_info();
    \brief prints information about data memory
*/
void mem_info();

char * types_info();

/*! \class manager
    \brief serves \ref file_load, \ref file_save, \ref clear_data and \ref mem_info commands
*/
class SURFIT_EXPORT manager {
public:
	virtual bool auto_load(const char * filename, const char * first1024, int readed) const = 0;
	//! loads tag with tag_name from ROFF file (if it is possible)	
	virtual int load_tag(datafile *df, char * tag_name) const = 0; // -1 = error, 0 = not found, 1 = ok
	//! saves memory to ROFF file (see \ref datafile)
	virtual bool save(datafile *df) const = 0;
	//! unloads data from memory
	virtual void clear_data() const = 0;
	//! prints some info about loaded \ref data into memory
	virtual void mem_info() const = 0;
	//! delete this
	virtual void release() = 0;
	//! returns amount of \ref data class supported by manager
	virtual int data_count() const = 0;
	//! returns i'th data
	virtual const data * data_get(int i) const = 0;
	//! returns names of supported data types
	virtual char * types_info() const = 0;
	//! returns maximum and minimum values for Z-coordinate
	virtual void getMinMaxZ(REAL & minZ, REAL & maxZ) const;
	//! if object have bounds, then fill them!
	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
};

/*! \class surfit_manager
    \brief serves \ref file_load, \ref file_save, \ref clear_data and \ref mem_info commands for libsurfit
*/
class surfit_manager : public manager {
public:
	int load_tag(datafile *df, char * tag_name) const;
	bool save(datafile *df) const;
	void clear_data() const;
	void mem_info() const;
	void release();
	int data_count() const;
	const data * data_get(int i) const;
	char * types_info() const;
	bool auto_load(const char * filename, const char * first1024, int readed) const;
};

/*! \class data_manager
    \brief serves different datatypes (\ref data) usage
*/
class SURFIT_EXPORT data_manager {
public:

	//! constructor
	data_manager();
	//! destructor
	~data_manager();

	//! serves \ref file_load command
	bool auto_load(const char * filename, const char * first1024, int readed) const;
	//! serves \ref file_load command
	bool load(datafile *df) const;
	//! serves \ref file_save command
	bool save(datafile *df) const;
	//! serves \ref clear_data command
	void clear_data() const;
	//! serves \ref mem_info command
	void mem_info() const;
	//! serves \ref types_info command
	char * types_info() const;
	//! returns maximum and minimum values for Z-coordinate
	void getMinMaxZ(REAL & minZ, REAL & maxZ) const;
	//! if object have bounds, then fill them!
	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const;
	//! returns amount of \ref data class supported by manager
	int data_count() const;
	//! returns i'th data
	const data * data_get(int i) const;
	//! returns data with specified type and name
	const data * data_get(const char * type, const char * name) const;

	//! vector of managers 
	std::vector<manager *> *  managers;
};

}; // namespace surfit;

#endif


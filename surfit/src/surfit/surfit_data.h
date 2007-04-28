
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

#ifndef __surfit_data_included__
#define __surfit_data_included__

#include "fileio.h"
#include "interp.h"

#include <string.h>
#include <vector>

#include <typeinfo>

namespace surfit {

/*! \class data
    \brief parent class for all kinds of data, using by surfit
*/
class SURFIT_EXPORT data {
protected:
	//! constructor
	data(const char * itype);
	//! destructor
	virtual ~data();
	
public:
	//! sets object name to newname 
	void setName(const char * newname);

	//! returns object name 
	const char * getName() const;

	//! return unique identificator
	int getId() const;

	//! sets object type to newtype
	void setType(const char * newtypename);

	//! returns object type
	const char * getType() const;

	//! if object have bounds, then fills them
	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const = 0;

	//! if object have vertical bounds, then fills them
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const = 0;

	//! removes data object and all depend functionals 
	virtual void release();
	//! removes data object from memory
	virtual void release_private();

protected:

	//! object name
	char * name;

	//! object type
	char * type;

	//! object id
	int id;

};

/*! \class binman
    \brief parent class for all garbages
*/
class SURFIT_EXPORT binman {
public:
	binman() {};
	virtual ~binman() {};
};

template <class T>
class objects_container
{
public:
	objects_container() 
	{
		data = new std::vector<T*>();
	};

	~objects_container()
	{
		delete data;
	}

	typename std::vector<T*>::iterator begin() 
	{
		return data->begin();
	};
	
	typename std::vector<T*>::const_iterator const_begin()
	{
		return data->begin();
	};

	typename std::vector<T*>::iterator end()
	{
		return data->end();
	};

	typename std::vector<T*>::const_iterator const_end()
	{
		return data->end();
	};
	
	typename std::vector<T*>::reference operator[](typename std::vector<T*>::size_type pos)
	{
		return (*data)[pos];
	};

	typename std::vector<T*>::const_reference operator[](typename std::vector<T*>::size_type pos) const
	{
		return (*data)[pos];
	};

	typename std::vector<T*>::size_type size() const
	{
		return data->size();
	};

	typename std::vector<T*>::iterator erase(typename std::vector<T*>::iterator _Where)
	{
		return data->erase(_Where);
	};

	void resize(typename std::vector<T*>::size_type _Newsize)
	{
		return data->resize(_Newsize);
	};

	virtual void push_back(T * elem) = 0;

protected:
	std::vector<T*> * data;
};

}; // namespace surfit;

#endif


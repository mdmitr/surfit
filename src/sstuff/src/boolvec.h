
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

#ifndef __surfit__boolvec__
#define __surfit__boolvec__

/*! \file
    \brief boolvec class (array of bool values) declaration
*/

#include <stdio.h>
#include "vec.h"

#ifdef _DEBUG
#define LSS_BOUNDS_CHECK
#else
#undef LSS_BOUNDS_CHECK
#endif

namespace surfit {

class boolvec;

//! creates boolvec object
SSTUFF_EXPORT
boolvec * create_boolvec(size_t size = 0, bool default_value = false, int fill_default = 1, size_t grow_by = 250);

//! creates boolvec object (makes a copy)
SSTUFF_EXPORT
boolvec * create_boolvec(const boolvec &in);

/*! \class boolvec
    \brief A boolean vector
*/
class SSTUFF_EXPORT boolvec {
public:

	//! iterator type for boolvec
	typedef         bool*  iterator;

	//! reference type for boolvec
	typedef         bool&  reference;

	//! const_iterator type for boolvec
	typedef const   bool*  const_iterator;

	//! const_reference type for boolvec
	typedef const   bool&  const_reference;
	
protected:
	/*! A consturtor
	    \param size vector size
	    \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
	*/
	boolvec(size_t size = 0, bool default_value = false, int fill_default = 1, size_t grow_by = 250);
	
	//! Copy constructor
	boolvec(const boolvec &in);
	
private:
	//! Destructor
	~boolvec();

public:

	//! constructor
	friend SSTUFF_EXPORT
	boolvec * create_boolvec(size_t size, bool default_value, int fill_default, size_t grow_by);

	//! copy constructor
	friend SSTUFF_EXPORT
	boolvec * create_boolvec(const boolvec &in);

	//! destructor
	void release();
	
	//! returns pointer to the begining of bool-array
	bool* begin() { return data; };

	//! returns reference-pointer to the begining of bool-array
	bool *& ref_begin() { return data; }

	//! returns const pointer to the begining of bool-array
	const bool* begin() const { return data;}
	
	//! returns pointer to the end of bool-array
	bool* end() { return data+datasize; }

	//! returns const pointer to the end of bool-array
	const bool* end() const { return data+datasize; }
	
	//! removes element by pointer
	void erase(bool*);

	//! removes element by index
	void erase(size_t index);
	
	//! changes vector size
	void resize(size_t newsize, bool default_value = false, int fill_default = 1);

	//! returns vector size
	size_t size() const { return datasize; };
	
	//! returns reference to i'th element
	bool& operator()(size_t i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		return *(data+i);
	};
		
	//! returns const reference to i'th element
	const bool& operator()(size_t i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const bool& res = *(data+i);
		return res;
	};
		
	//! adds one element at the end of array
	void push_back(const bool&);

	//! adds elements from other boolvec from another boolvec
	void push_back(boolvec * v);

	//! sets currently allocated vector size to reserve_size
	void reserve(size_t reserve_size);

	//! sets vector's grow factor
	void set_grow(size_t grow_by);
	
	//! changes two elements values
	void swap(size_t i, size_t j);
		
	//! frees all allocated memory
	void drop_data();
		
	//! returns void* to begin of vector-array
	void * getPointer() const { return (void*)data; };
		
public:
	//! pointer to vector-array
	bool * data;

	//! real vector size in elements
	size_t datasize;

	//! size of allocated memory in elements
	size_t bool_datasize;
	
	//! grow factor
	size_t grow_by;
};

}; // namespace surfit

#endif


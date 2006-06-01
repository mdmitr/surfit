
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

#ifndef __surfit__shortvec__
#define __surfit__shortvec__

#include <stdio.h>
#include "vec.h"

namespace surfit {

class shortvec;

SSTUFF_EXPORT
shortvec * create_shortvec(size_t size = 0, short default_value = short(0), int fill_default = 1, size_t grow_by = 250);
	
SSTUFF_EXPORT
shortvec * create_shortvec(const shortvec &in);

/*! \class shortvec
    \brief surfit vector class for shortegers
*/
class SSTUFF_EXPORT shortvec {
public:

	//! iterator type for shortvec
	typedef         short*  iterator;

	//! reference type for shortvec
	typedef         short&  reference;

	//! const_iterator type for vec
	typedef const   short*  const_iterator;

	//! const_reference type for vec
	typedef const   short&  const_reference;
		
protected:
	/*! A consturtor
	    \param size vector size
	    \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
	*/
	shortvec(size_t size = 0, short default_value = short(0), int fill_default = 1, size_t grow_by = 250);
	
	//! Copy constructor
	shortvec(const shortvec &in);

private:
	//! Destructor
	~shortvec();

public:

	friend SSTUFF_EXPORT
	shortvec * create_shortvec(size_t size, short default_value, int fill_default, size_t grow_by);
	
	friend SSTUFF_EXPORT
	shortvec * create_shortvec(const shortvec &in);

	void release();

	//! return pointer to begin of short-array
	short* begin() { return data; };

	//! return reference-pointer to begin of short-array
	short *& ref_begin() { return data; };

	//! return const pointer to begin of short-array
	const short* begin() const { return data; };

	//! return pointer to end of short-array
	short* end() { return data+datasize; };

	//! return const pointer to end of short-array
	const short* end() const { return data+datasize; };

	//! delete element by pointer
	void erase(short*);

	//! delete element by index
	void erase(size_t index);
		
	//! resize vector
	void resize(size_t newsize, short default_value = short(0), int fill_default = 1);

	//! return vector size
	size_t size() const { return datasize; };

	//! return reference to i'th element
	short& operator()(size_t i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
			
		return *(data+i);
	};
		
	//! return const reference to i'th element
	const short& operator()(size_t i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const short& res = *(data+i);
		return res;
	};

	//! add one element at the end of array
	void push_back(const short&);

	//! set currently allocated vector size to reserve_size
	void reserve(size_t reserve_size);

	//! set vector's grow factor
	void set_grow(size_t grow_by);

	//! swap two elements
	void swap(size_t i, size_t j);

	//! forget all allocated memory
	void drop_data();

	//! return void* to begin of vector-array
	void* getPointer() const { return (void*)data; };
	
protected:
	//! pointer to vector-array
	short* data;

	//! short vector size in elements
	size_t datasize;

	//! size of allocated memory in elements
	size_t short_datasize;
	
	//! grow factor
	size_t grow_by;
};

}; // namespace surfit

#endif


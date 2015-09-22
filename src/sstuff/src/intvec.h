
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

#ifndef __surfit__intvec__
#define __surfit__intvec__

/*! \file
    \brief intvec class (array of int values) declaration
*/

#include <stdio.h>
#include "vec.h"

namespace surfit {

class intvec;

//! creates intvec object
SSTUFF_EXPORT
intvec * create_intvec(size_t size = 0, int default_value = int(0), bool fill_default = true, size_t grow_by = 250);

//! creates intvec object (makes a copy)
SSTUFF_EXPORT
intvec * create_intvec(const intvec &in);

/*! \class intvec
    \brief vector for integers
*/
class SSTUFF_EXPORT intvec {
public:

	//! iterator type for intvec
	typedef         int*  iterator;

	//! reference type for intvec
	typedef         int&  reference;

	//! const_iterator type for vec
	typedef const   int*  const_iterator;

	//! const_reference type for vec
	typedef const   int&  const_reference;
		

protected:
	/*! A consturtor
	    \param size vector size
	    \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
	*/
	intvec(size_t size = 0, int default_value = int(0), bool fill_default = true, size_t grow_by = 250);
	
	//! Copy constructor
	intvec(const intvec &in);

private:
	//! Destructor
	~intvec();

public:

	//! constructor
	friend SSTUFF_EXPORT
	intvec * create_intvec(size_t size, int default_value, bool fill_default, size_t grow_by);

	//! copy constructor
	friend SSTUFF_EXPORT
	intvec * create_intvec(const intvec &in);

	//! destructor
	void release();

	//! returns pointer to begin of int-array
	int* begin() { return data; };

	//! returns reference-pointer to begin of int-array
	int *& ref_begin() { return data; };

	//! returns const pointer to begin of int-array
	const int* begin() const { return data; };

	//! returns pointer to end of int-array
	int* end() { return data+datasize; };

	//! returns const pointer to end of int-array
	const int* end() const { return data+datasize; };

	//! deletes element by pointer
	void erase(int*);

	//! deletes element by index
	void erase(size_t index);
		
	//! resizes vector
	void resize(size_t newsize, int default_value = int(0), bool fill_default = 1);

	//! returns vector size
	size_t size() const { return datasize; };

	//! returns reference to i'th element
	int& operator()(size_t i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
			
		return *(data+i);
	};
		
	//! returns const reference to i'th element
	const int& operator()(size_t i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const int& res = *(data+i);
		return res;
	};

	//! adds one element at the end of array
	void push_back(const int&);
	
	//! adds vector at the end of array
	void push_back(intvec * v);

	//! sets currently allocated vector size to reserve_size
	void reserve(size_t reserve_size);

	//! sets vector's grow factor
	void set_grow(size_t grow_by);

	//! swaps two elements
	void swap(size_t i, size_t j);

	//! forgets all allocated memory
	void drop_data();

	//! returns void* to begin of vector-array
	void* getPointer() const { return (void*)data; };
	
protected:
	//! pointer to vector-array
	int* data;

	//! int vector size in elements
	size_t datasize;

	//! size of allocated memory in elements
	size_t int_datasize;
	
	//! grow factor
	size_t grow_by;
};

}; // namespace surfit

#endif



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

#ifndef __surfit__intvec__
#define __surfit__intvec__

#include <stdio.h>
#include "vec.h"

namespace surfit {

/*! \class intvec
    \brief surfit vector class for integers
*/
class SURFIT_EXPORT intvec {
public:

	//! iterator type for intvec
	typedef         int*  iterator;

	//! reference type for intvec
	typedef         int&  reference;

	//! const_iterator type for vec
	typedef const   int*  const_iterator;

	//! const_reference type for vec
	typedef const   int&  const_reference;
		

	/*! A consturtor
	    \param size vector size
	    \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
	*/
	intvec(int size = 0, int default_value = int(0), int fill_default = 1, int grow_by = 250);
	
	//! A constructor
	intvec(int * vec_begin, int * vec_end);
	
	//! Copy constructor
	intvec(const intvec &in);

	//! Destructor
	virtual ~intvec();

	//! return pointer to begin of int-array
	int* begin() { return data; };

	//! return reference-pointer to begin of int-array
	int *& ref_begin() { return data; };

	//! return const pointer to begin of int-array
	const int* begin() const { return data; };

	//! return pointer to end of int-array
	virtual int* end() { return data+datasize; };

	//! return const pointer to end of int-array
	virtual const int* end() const { return data+datasize; };

	//! delete element by pointer
	virtual void erase(int*);

	//! delete element by index
	virtual void erase(int index);
		
	//! resize vector
	void resize(int newsize, int default_value = int(0), int fill_default = 1);

	//! return vector size
	int size() const { return datasize; };

	//! return reference to i'th element
	int& operator()(int i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
			
		return *(data+i);
	};
		
	//! return const reference to i'th element
	const int& operator()(int i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const int& res = *(data+i);
		return res;
	};

	//! add one element at the end of array
	virtual void push_back(const int&);

	//! set currently allocated vector size to reserve_size
	virtual void reserve(int reserve_size);

	//! set vector's grow factor
	virtual void set_grow(int grow_by);

	//! swap two elements
	virtual void swap(int i, int j);

	//! forget all allocated memory
	virtual void drop_data();

	//! return void* to begin of vector-array
	void* getPointer() const { return (void*)data; };
	
public:
	//! pointer to vector-array
	int* data;

	//! int vector size in elements
	int datasize;

	//! size of allocated memory in elements
	int int_datasize;
	
	//! grow factor
	int grow_by;
};

}; // namespace surfit

#endif


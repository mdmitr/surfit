
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

#ifndef __surfit__boolvec__
#define __surfit__boolvec__

#include <stdio.h>
#include "vec.h"

#ifdef _DEBUG
#define LSS_BOUNDS_CHECK
#else
#undef LSS_BOUNDS_CHECK
#endif

namespace surfit {

/*! \class boolvec
    \brief vector of bool type
*/
class boolvec {
public:

	//! iterator type for boolvec
	typedef         bool*  iterator;

	//! reference type for boolvec
	typedef         bool&  reference;

	//! const_iterator type for boolvec
	typedef const   bool*  const_iterator;

	//! const_reference type for boolvec
	typedef const   bool&  const_reference;
	
	/*! A consturtor
	    \param size vector size
	    \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
	*/
	boolvec(int size = 0, bool default_value = false, int fill_default = 1, int grow_by = 250);
	
	//! Constructor
	boolvec(bool * boolvec_begin, bool * boolvec_end);
	
	//! Copy constructor
	boolvec(const boolvec &in);
	
	//! Destructor
	virtual ~boolvec();
	
	//! returns pointer to begin of bool-array
	bool* begin() {  return data; };

	//! returns reference-pointer to begin of bool-array
	bool *& ref_begin() { return data; }

	//! returns const pointer to begin of bool-array
	const bool* begin() const { return data;}
	
	//! returns pointer to end of bool-array
	bool* end() { return data+datasize; }

	//! returns const pointer to end of bool-array
	const bool* end() const { return data+datasize; }
	
	//! removes element by pointer
	void erase(bool*);

	//! removes element by index
	void erase(int index);
	
	//! changes vector size
	void resize(int newsize, bool default_value = false, int fill_default = 1);

	//! returns vector size
	int size() const { return datasize; };
	
	//! returns reference to i'th element
	bool& operator()(int i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		return *(data+i);
	};
		
	//! returns const reference to i'th element
	const bool& operator()(int i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const bool& res = *(data+i);
		return res;
	};
		
	//! adds one element at the end of array
	virtual void push_back(const bool&);

	//! sets currently allocated vector size to reserve_size
	virtual void reserve(int reserve_size);

	//! sets vector's grow factor
	virtual void set_grow(int grow_by);
	
	//! exchanges two elements values
	virtual void swap(int i, int j);
		
	//! frees all allocated memory
	virtual void drop_data();
		
	//! returns void* to begin of vector-array
	void * getPointer() const { return (void*)data; };
		
public:
	//! pointer to vector-array
	bool * data;

	//! real vector size in elements
	int datasize;

	//! size of allocated memory in elements
	int bool_datasize;
	
	//! grow factor
	int grow_by;
};

}; // namespace surfit

#endif



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

#ifndef __surfit__vec__
#define __surfit__vec__

#include <stdio.h>

#ifdef _DEBUG
#define LSS_BOUNDS_CHECK
#else
#undef LSS_BOUNDS_CHECK
#endif

namespace surfit {

class vec;

SSTUFF_EXPORT
/*! \ingroup internal
    \fn vec * create_vec(int size = 0, REAL default_value = REAL(0), int fill_default = 1, int grow_by = 250);
    \brief creates \ref vec object
*/
vec * create_vec(int size = 0, REAL default_value = REAL(0), int fill_default = 1, int grow_by = 250);

SSTUFF_EXPORT
/*! \ingroup internal
    \fn vec * create_vec(const vec &in);
    \brief creates \ref vec object
*/
vec * create_vec(const vec &in);

/*! \class vec
    \brief surfit vector of REAL 
*/
class SSTUFF_EXPORT vec {
public:

	//! iterator type for vec
	typedef         REAL*  iterator;

	//! reference type for vec
	typedef         REAL&  reference;

	//! const_iterator type for vec
	typedef const   REAL*  const_iterator;

	//! const_reference type for vec
	typedef const   REAL&  const_reference;
		
protected:

	/*! A consturtor
	    \param size vector size
            \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
    	*/
	vec(int size = 0, REAL default_value = REAL(0), int fill_default = 1, int grow_by = 250);
	
	//! Copy constructor
	vec(const vec &in);

public:

	friend SSTUFF_EXPORT
	//! constructor
	vec * create_vec(int size, REAL default_value, int fill_default, int grow_by);

	friend SSTUFF_EXPORT
	//! copy constructor
	vec * create_vec(const vec &in);

private:
	//! Destructor
	~vec();

public:
	//! destructor
	void release();

	//! returns pointer to begin of REAL-array
	REAL* begin() { return data; };

	//! returns const pointer to begin of REAL-array
	const REAL* begin() const { return data; };

	//! returns pointer to end of REAL-array
	REAL* end() { return data+datasize; };

	//! returns const pointer to end of REAL-array
	const REAL* end() const { return data+datasize; };

	//! removes element by pointer
	void erase(REAL*);

	//! removes element by index
	void erase(int index);
		
	//! changes vector size
	void resize(int newsize, REAL default_value = REAL(0), int fill_default = 1);

	//! returns vector size
	int size() const { return datasize; };

	//! returns reference to i'th element
	REAL& operator()(int i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
			
		return *(data+i);
	};
		
	//! returns const reference to i'th element
	const REAL& operator()(int i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const REAL& res = *(data+i);
		return res;
	};

	//! copy operator
	vec& operator=(const vec & copy);

	//! adds one element at the end of array
	void push_back(const REAL&);

	//! sets currently allocated vector size to reserve_size
	void reserve(int reserve_size);

	//! sets vector's grow factor
	void set_grow(int grow_by);

	//! exchanges two elements
	void swap(int i, int j);

	//! forgets all allocated memory
	void drop_data();

	//! returns void* to begin of vector-array
	void* getPointer() const { return (void*)data; };
	
protected:
	//! pointer to vector-array
	REAL* data;

	//! real vector size in elements
	int datasize;

	//! size of allocated memory in elements
	int real_datasize;
	
	//! grow factor
	int grow_by;
};

}; // namespace surfit

#endif


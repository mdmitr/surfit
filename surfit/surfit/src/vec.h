
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

#ifndef __surfit__vec__
#define __surfit__vec__

#include <stdio.h>

#include "real.h"

#ifdef _DEBUG
#define LSS_BOUNDS_CHECK
#else
#undef LSS_BOUNDS_CHECK
#endif

namespace surfit {

/*! \class vec
    \brief surfit vector of REAL 
*/
class SURFIT_EXPORT vec {
public:

	//! iterator type for vec
	typedef         REAL*  iterator;

	//! reference type for vec
	typedef         REAL&  reference;

	//! const_iterator type for vec
	typedef const   REAL*  const_iterator;

	//! const_reference type for vec
	typedef const   REAL&  const_reference;
		

	/*! A consturtor
	    \param size vector size
            \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
    	*/
	vec(int size = 0, REAL default_value = REAL(0), int fill_default = 1, int grow_by = 250);
	
	//! Constructor
	vec(REAL * vec_begin, REAL * vec_end);
	
	//! Copy constructor
	vec(const vec &in);

	//! Destructor
	virtual ~vec();

	//! returns pointer to begin of REAL-array
	REAL* begin() { return data; };

	//! returns reference-pointer to begin of REAL-array
	REAL *& ref_begin() { return data; };

	//! returns const pointer to begin of REAL-array
	const REAL* begin() const { return data; };

	//! returns pointer to end of REAL-array
	virtual REAL* end() { return data+datasize; };

	//! returns const pointer to end of REAL-array
	virtual const REAL* end() const { return data+datasize; };

	//! removes element by pointer
	virtual void erase(REAL*);

	//! removes element by index
	virtual void erase(int index);
		
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
	virtual void push_back(const REAL&);

	//! sets currently allocated vector size to reserve_size
	virtual void reserve(int reserve_size);

	//! sets vector's grow factor
	virtual void set_grow(int grow_by);

	//! exchanges two elements
	virtual void swap(int i, int j);

	//! forgets all allocated memory
	virtual void drop_data();

	//! returns void* to begin of vector-array
	void* getPointer() const { return (void*)data; };
	
public:
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


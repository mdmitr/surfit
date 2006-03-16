
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

#ifndef __surfit__strvec__
#define __surfit__strvec__

#include <stdio.h>

namespace surfit {

class strvec;

SSTUFF_EXPORT
strvec * create_strvec(int size = 0, int grow_by = 250);

/*! \class vec
    \brief surfit vector of REAL 
*/
class SSTUFF_EXPORT strvec {
public:

	//! iterator type for strvec
	typedef         char**  iterator;

	//! reference type for vec
	typedef         char*&  reference;

	//! const_iterator type for vec
	typedef const   char**  const_iterator;

	//! const_reference type for vec
	typedef const   char*&  const_reference;
		
protected:

	/*! A consturtor
	    \param size vector size
            \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
    	*/
	strvec(int size = 0, int grow_by = 250);
	
public:

	friend SSTUFF_EXPORT
	strvec * create_strvec(int size, int grow_by);

private:
	//! Destructor
	~strvec();

public:
	void release();

	//! returns pointer to begin of REAL-array
	char** begin() { return data; };

	//! returns const pointer to begin of REAL-array
	const char** begin() const { return (const char **)data; };

	//! returns pointer to end of REAL-array
	char** end() { return data+datasize; };

	//! returns const pointer to end of REAL-array
	const char** end() const { return (const char **)data+datasize; };

	//! removes element by pointer
	void erase(char**);

	//! removes element by index
	void erase(int index);
		
	//! changes vector size
	void resize(int newsize);

	//! returns vector size
	int size() const { return datasize; };

	//! returns reference to i'th element
	char*& operator()(int i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
			
		return *(data+i);
	};
		
	//! returns const reference to i'th element
	const char * operator()(int i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const char* res = *(data+i);
		return res;
	};

	//! copy operator
	strvec& operator=(const strvec & copy);

	//! adds one element at the end of array
	void push_back(const char*);

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
	char** data;

	//! real vector size in elements
	int datasize;

	//! size of allocated memory in elements
	int real_datasize;
	
	//! grow factor
	int grow_by;
};

}; // namespace surfit

#endif


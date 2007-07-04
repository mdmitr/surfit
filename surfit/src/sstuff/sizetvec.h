
/*------------------------------------------------------------------------------
 *	$Id: vec.h 940 2007-01-31 12:56:27Z mishadm $
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

#ifndef __surfit_sizetvec__
#define __surfit_sizetvec__

#ifdef XXL
#include "../../src_xxl/sstuff/sizetvec_xxl.h"
#else

#include <vector>

namespace surfit {

class sizetvec;

/*! \ingroup sstuff_internal
    \fn sizetvec * create_sizetvec(size_t size = 0);
    \brief creates sizetvec object
*/
SSTUFF_EXPORT 
sizetvec * create_sizetvec(size_t size = 0);

/*! \class sizetvec
    \brief A vector of size_t type values
*/
class SSTUFF_EXPORT sizetvec
{
public:

	//! iterator type for vec
	typedef  std::vector<size_t>::iterator iterator;
	//! reference type for vec
	typedef  std::vector<size_t>::reference reference;

	//! const_iterator type for vec
	typedef  std::vector<size_t>::const_iterator const_iterator;
	//! const_reference type for vec
	typedef  std::vector<size_t>::const_reference const_reference;

	//! constructor
	friend SSTUFF_EXPORT
	sizetvec * create_sizetvec(size_t size);

	//! destructor
	virtual void release();

	//! returns pointer to begin of REAL-array
	inline iterator begin() {
		return data->begin();
	};

	//! returns const pointer to begin of REAL-array
	inline const_iterator const_begin() const
	{
		return data->begin();
	};

	//! returns pointer to end of REAL-array
	inline iterator end() {
		return data->end();
	};

	//! returns const pointer to end of REAL-array
	inline const_iterator const_end() const {
		return data->end();
	};

	//! changes vector size
	void resize(size_t newsize);

	//! returns vector size
	inline size_t size() const {
		return data->size();
	};

	//! returns reference to i'th element
	inline reference operator()(size_t i) {
		return (*data)[i];
	};
		
	//! returns const reference to i'th element
	inline const_reference operator()(size_t i) const {
		return (*data)[i];
	};

	//! adds one element at the end of array
	void push_back(size_t val);

	//! sets currently allocated vector size to reserve_size
	void reserve(size_t reserve_size);

	//! sets vector's grow factor
	inline void set_grow(size_t grow_by) {};
	
private:

	//! private constructor
	sizetvec(size_t size = 0);

	//! private destructor
	virtual ~sizetvec();

	//! vector data
	std::vector<size_t> * data;
};

}; // namespace surfit;

#endif

#endif


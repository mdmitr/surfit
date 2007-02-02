
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

#include "sstuff_ie.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <float.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

#include "vec.h"

namespace surfit {

vec * create_vec(size_t size, REAL default_value, int fill_default, size_t grow_by)
{
	return new vec(size, default_value, fill_default, grow_by);
};

vec * create_vec(const vec &in) {
	return new vec(in);
};

#ifdef XXL
vec * create_vec(const extvec &in) {
	return new vec(in);
};
#endif

vec::vec(const vec &in) {
	if (this != &in) {
		size_t newsize = in.size();
		data = (REAL*)malloc(sizeof(REAL)*newsize);
		if (data) {
			datasize = newsize;
			real_datasize = datasize;
			// init
			memcpy(data, in.data, sizeof(REAL)*newsize);
		};
		if ((data == NULL) && (newsize != 0)) {
			throw "out of memory";
		}	
		grow_by = in.grow_by;
	}
};

#ifdef XXL
vec::vec(const extvec &in) {
	size_t newsize = in.size();
	data = (REAL*)malloc(sizeof(REAL)*newsize);
	if (data) {
		datasize = newsize;
		real_datasize = datasize;
		// init
		std::copy(in.const_begin(), in.const_end(), data);
	};
	if ((data == NULL) && (newsize != 0)) {
		throw "out of memory";
	}	
	grow_by = 250;
};
#endif

vec::vec(size_t newsize, REAL default_value, int fill_default, size_t igrow_by) {
	grow_by = igrow_by;
	if (newsize == 0) {
		data = NULL;
		datasize = newsize;
		real_datasize = newsize;
		return;
	}
	data = (REAL*)malloc(sizeof(REAL)*newsize);
	if (data) {
		datasize = newsize;
		real_datasize = newsize;
		// init
		if (fill_default == 1) {
			size_t i;
			for (i = 0; i < size(); i++) {
				operator()(i) = default_value;
			}
		}
	};
	if ((data == NULL) && (newsize != 0)) {
		throw "out of memory";
	}
};

vec::~vec() {
	if (data) {
		free(data);
		datasize = 0;
		real_datasize = 0;
	}

};

void vec::release() {
	delete this;
};

void vec::resize(size_t newsize, REAL default_value, int fill_default) {
	if (datasize == newsize)
		return;
	if ((newsize == 0) && (data = NULL)) {
		datasize = 0;
		real_datasize = 0;
		return;
	}
	REAL *tmpData = (REAL*)realloc(data, sizeof(REAL)*newsize);
	if (tmpData) {
		data = tmpData;
		size_t oldsize = datasize;
		datasize = newsize;
		real_datasize = datasize;
		if (oldsize < newsize) {
			if (fill_default == 1) {
				size_t i;
				for (i = oldsize; i < newsize; i++) {
					operator()(i) = default_value;
				}
			}
		}
	} else {
		data = NULL;
		if (newsize == 0) {
			datasize = 0;
			real_datasize = 0;
		}
	}
	if ((data == NULL) && (newsize != 0)) 
		throw "out of memory";
};

void vec::push_back(const REAL& x) {
	if (datasize < real_datasize) {
		datasize++;
		operator()(size()-1) = x;
		return;
	} else {
		reserve(datasize + grow_by);
		push_back(x);
	}
};

void vec::set_grow(size_t igrow_by) {
	grow_by = igrow_by;
};

void vec::reserve(size_t reserve_size) {
	size_t oldsize = real_datasize;
	if (oldsize < reserve_size) {
		
		REAL *tmpData = (REAL*)realloc(data, sizeof(REAL)*reserve_size);
		if (tmpData) {
			data = tmpData;
			real_datasize = reserve_size;
		} else {
			data = NULL;
			if (reserve_size == 0) {
				datasize = 0;
				real_datasize = 0;
			}
		}
		if ((data == NULL) && (reserve_size != 0)) 
			throw "out of memory";

	}
};

void vec::swap(size_t i, size_t j) {
	#ifdef LSS_BOUNDS_CHECK
	if ((i < 1) || (i > size()))
			throw "invalid argument";
	if ((j < 1) || (j > size()))
			throw "invalid argument";
	#endif
	REAL temp = operator()(i);
	operator()(i) = operator()(j);
	operator()(j) = temp;
};

void vec::erase(vec::iterator del) {
	iterator cur = begin();
	size_t i = del-cur;
	erase(i);
};

void vec::erase(size_t index) {
#ifdef LSS_BOUNDS_CHECK
	if (index > datasize) 
		throw "invalid argument";
#endif
	REAL * cur = data;
	cur += index;
	memmove(cur,cur+1,(size()-index-1)*sizeof(REAL));
	datasize--;
	real_datasize--;
	return;
};

void vec::drop_data() {
	data = NULL;
	datasize = 0;
	real_datasize = 0;
};

vec& vec::operator=(const vec & copy) {
	if (this == &copy) {
		return *this;
	}
	if (datasize != copy.size()) {
		free(data);
		data = (REAL *) malloc(copy.size() * sizeof(REAL));
	}
	
	memcpy(data, &*(copy.const_begin()), copy.size()*sizeof(REAL));
	
	datasize = copy.size();
	return *this;
};

size_t vec::write_file(int file, size_t size) const {
	return write(file, data, size*sizeof(REAL));
};

size_t vec::read_file(int file, size_t size) {
	return read( file, data, sizeof(REAL)*size );
};

}; // namespace surfit;



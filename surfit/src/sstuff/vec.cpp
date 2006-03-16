
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

#include "vec.h"

namespace surfit {

vec * create_vec(int size, REAL default_value, int fill_default, int grow_by)
{
	return new vec(size, default_value, fill_default, grow_by);
};

vec * create_vec(const vec &in) {
	return new vec(in);
};

vec::vec(const vec &in) {
	if (this != &in) {
		int newsize = in.size();
		data = (REAL*)malloc(sizeof(REAL)*newsize);
		if (data) {
			datasize = newsize;
			real_datasize = datasize;
			// init
			memcpy(data, in.data, sizeof(REAL)*newsize);
			/*
			for (int i = 0; i < size(); i++) {
				operator()(i) = in(i);
			}
			*/
		};
		if ((data == NULL) && (newsize != 0)) {
			throw "not enough memory";
		}	
		grow_by = in.grow_by;
	}
};

vec::vec(int newsize, REAL default_value, int fill_default, int igrow_by) {
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
			for (int i = 0; i < size(); i++) {
				operator()(i) = default_value;
			}
		}
	};
	if ((data == NULL) && (newsize != 0)) {
		throw "not enough memory";
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

void vec::resize(int newsize, REAL default_value, int fill_default) {
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
		int oldsize = datasize;
		datasize = newsize;
		real_datasize = datasize;
		if (oldsize < newsize) {
			if (fill_default == 1) {
				for (int i = oldsize; i < newsize; i++) {
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
		throw "not enough memory";
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

void vec::set_grow(int igrow_by) {
	grow_by = igrow_by;
};

void vec::reserve(int reserve_size) {
	int oldsize = real_datasize;
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
			throw "not enough memory";

	}
};

void vec::swap(int i, int j) {
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

void vec::erase(REAL* del) {
	REAL* cur = begin();
	for (int i = 0; i < size(); i++, cur++) {
		if (cur == del) {
			// perform deletion;
			memmove(cur,cur+1,(size()-i+1)*sizeof(REAL));
			datasize--;
			real_datasize--;
			return;
		}
	}
};

void vec::erase(int index) {
#ifdef LSS_BOUNDS_CHECK
	if (index > datasize) 
		throw "invalid argument";
#endif
	REAL* cur = begin();
	cur += index-1;
	memmove(cur,cur+1,(size()-index+1)*sizeof(REAL));
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
	memcpy(data, copy.getPointer(), copy.size()*sizeof(REAL));
	datasize = copy.size();
	return *this;
};

}; // namespace surfit;



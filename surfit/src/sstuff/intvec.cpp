
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

#include "fileio.h"

#include <stdio.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "intvec.h"

namespace surfit {

intvec * create_intvec(size_t size, int default_value, int fill_default, size_t grow_by) {
	return new intvec(size, default_value, fill_default, grow_by);
}

intvec * create_intvec(const intvec &in) {
	return new intvec(in);
}

intvec::intvec(const intvec &in) {
	if (this != &in) {
		size_t newsize = in.size();
		data = (int*)malloc(sizeof(int)*newsize);
		if (data) {
			datasize = newsize;
			int_datasize = datasize;
			// init
			size_t i;
			for (i = 0; i < size(); i++) {
				operator()(i) = in(i);
			}
		};
		if ((data == NULL) && (newsize != 0)) {
			throw "out of memory";
		}	
		grow_by = in.grow_by;
	}
};

intvec::intvec(size_t newsize, int default_value, int fill_default, size_t igrow_by) {
	grow_by = igrow_by;
	if (newsize == 0) {
		data = NULL;
		datasize = newsize;
		int_datasize = newsize;
		return;
	}
	data = (int*)malloc(sizeof(int)*newsize);
	if (data) {
		datasize = newsize;
		int_datasize = newsize;
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

intvec::~intvec() {
	if (data) {
		free(data);
		datasize = 0;
		int_datasize = 0;
	}

};

void intvec::release() {
	delete this;
};

void intvec::resize(size_t newsize, int default_value, int fill_default) {
	if (datasize == newsize)
		return;
	if ((newsize == 0) && (data = NULL)) {
		datasize = 0;
		int_datasize = 0;
		return;
	}
	int *tmpData = (int*)realloc(data, sizeof(int)*newsize);
	if (tmpData) {
		data = tmpData;
		size_t oldsize = datasize;
		datasize = newsize;
		int_datasize = datasize;
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
			int_datasize = 0;
		}
	}
	if ((data == NULL) && (newsize != 0)) 
		throw "out of memory";
};

void intvec::push_back(const int& x) {
	if (datasize < int_datasize) {
		datasize++;
		operator()(size()-1) = x;
		return;
	} else {
		reserve(datasize + grow_by);
		push_back(x);
	}
};

void intvec::set_grow(size_t igrow_by) {
	grow_by = igrow_by;
};

void intvec::reserve(size_t reserve_size) {
	size_t oldsize = int_datasize;
	if (oldsize < reserve_size) {
		
		int *tmpData = (int*)realloc(data, sizeof(int)*reserve_size);
		if (tmpData) {
			data = tmpData;
			int_datasize = reserve_size;
		} else {
			data = NULL;
			if (reserve_size == 0) {
				datasize = 0;
				int_datasize = 0;
			}
		}
		if ((data == NULL) && (reserve_size != 0)) 
			throw "out of memory";

	}
};

void intvec::swap(size_t i, size_t j) {
	#ifdef LSS_BOUNDS_CHECK
	if ((i < 1) || (i > size()))
			throw "invalid argument";
	if ((j < 1) || (j > size()))
			throw "invalid argument";
	#endif
	size_t temp = operator()(i);
	operator()(i) = operator()(j);
	operator()(j) = temp;
};

void intvec::erase(int* del) {
	int* cur = begin();
	size_t i;
	for (i = 0; i < size(); i++, cur++) {
		if (cur == del) {
			// perform deletion;
			memmove(cur,cur+1,(size()-i+1)*sizeof(int));
			datasize--;
			int_datasize--;
			return;
		}
	}
};

void intvec::erase(size_t index) {
#ifdef LSS_BOUNDS_CHECK
	if (index > datasize) 
		throw "invalid argument";
#endif
	int* cur = begin();
	cur += index-1;
	memmove(cur,cur+1,(size()-index+1)*sizeof(int));
	datasize--;
	int_datasize--;
	return;
};

void intvec::drop_data() {
	data = NULL;
	datasize = 0;
	int_datasize = 0;
}

}; // namespace surfit;



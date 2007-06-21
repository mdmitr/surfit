
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

#include "strvec.h"

namespace surfit {

strvec * create_strvec(size_t size, size_t grow_by)
{
	return new strvec(size, grow_by);
};

strvec * create_strvec(const strvec & in) {
	return new strvec(in);
};

strvec::strvec(size_t newsize, size_t igrow_by) {
	grow_by = igrow_by;
	if (newsize == 0) {
		data = NULL;
		datasize = newsize;
		real_datasize = newsize;
		return;
	}
	data = (char**)malloc(sizeof(char*)*newsize);
	if (data) {
		datasize = newsize;
		real_datasize = newsize;
		// init
		for (size_t i = 0; i < size(); i++) {
			operator()(i) = NULL;
		}
	};
	if ((data == NULL) && (newsize != 0)) {
		throw "out of memory";
	}
};

strvec::~strvec() {
	if (data) {
		size_t i;
		for (i = 0; i < datasize; i++)
			free( *(data+i) );
		free(data);
		datasize = 0;
		real_datasize = 0;
	}

};

void strvec::release() {
	delete this;
};

void strvec::resize(size_t newsize) {
	if (datasize == newsize)
		return;
	if ((newsize == 0) && (data = NULL)) {
		datasize = 0;
		char*_datasize = 0;
		return;
	}
	char ** tmpData = (char**)realloc(data, sizeof(char*)*newsize);
	if (tmpData) {
		data = tmpData;
		size_t oldsize = datasize;
		datasize = newsize;
		real_datasize = datasize;
		if (oldsize < newsize) {
			for (size_t i = oldsize; i < newsize; i++) {
				operator()(i) = NULL;
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

void strvec::push_back(const char * x) {
	if (datasize < real_datasize) {
		datasize++;
		if (x)
			operator()(size()-1) = strdup(x);
		else 
			operator()(size()-1) = NULL;
		return;
	} else {
		reserve(datasize + grow_by);
		push_back(x);
	}
};

void strvec::set_grow(size_t igrow_by) {
	grow_by = igrow_by;
};

void strvec::reserve(size_t reserve_size) {
	size_t oldsize = real_datasize;
	if (oldsize < reserve_size) {
		
		char ** tmpData = (char**)realloc(data, sizeof(char*)*reserve_size);
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

void strvec::swap(size_t i, size_t j) {
	#ifdef LSS_BOUNDS_CHECK
	if ((i < 1) || (i > size()))
			throw "invalid argument";
	if ((j < 1) || (j > size()))
			throw "invalid argument";
	#endif
	char* temp = operator()(i);
	operator()(i) = operator()(j);
	operator()(j) = temp;
};

void strvec::erase(char** del) {
	char** cur = begin();
	size_t i = del - cur;
	erase(i);
};

void strvec::erase(size_t index) {
#ifdef LSS_BOUNDS_CHECK
	if (index > datasize) 
		throw "invalid argument";
#endif
	free ( operator()(index) );
	char** cur = begin();
	cur += index-1;
	memmove(cur,cur+1,(size()-index+1)*sizeof(char*));
	datasize--;
	real_datasize--;
	return;
};

void strvec::drop_data() {
	data = NULL;
	datasize = 0;
	real_datasize = 0;
};

}; // namespace surfit;



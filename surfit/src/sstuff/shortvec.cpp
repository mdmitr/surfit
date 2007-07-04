
/*--------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 M.V.Dmitrievsky
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
 *	Contact info: http://surfit.sourceforge.net
 *--------------------------------------------------------------------*/

#include "sstuff_ie.h"

#include <stdio.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) 
#include <io.h>
#endif

#include "shortvec.h"

namespace surfit {

#ifndef XXL

shortvec * create_shortvec(size_t size, short default_value, bool fill_default, size_t grow_by) {
	return new shortvec(size, default_value, fill_default, grow_by);
};

shortvec * create_shortvec(const shortvec &in) {
	return new shortvec(in);
};

shortvec::shortvec(const shortvec &in) {
	if (this != &in) {
		size_t newsize = in.size();
		data = (short*)malloc(sizeof(short)*newsize);
		if (data) {
			datasize = newsize;
			short_datasize = datasize;
			// init
			size_t i;
			for (i = 0; i < size(); i++) {
				operator()(i) = in(i);
			}
		};
		if ((data == NULL) && (newsize != 0)) {
			throw "out of memory";
		}	
	}
};

shortvec::shortvec(size_t newsize, short default_value, bool fill_default, size_t igrow_by) {
	grow_by = igrow_by;
	if (newsize == 0) {
		data = NULL;
		datasize = newsize;
		short_datasize = newsize;
		return;
	}
	data = (short*)malloc(sizeof(short)*newsize);
	if (data) {
		datasize = newsize;
		short_datasize = newsize;
		// init
		if (fill_default == true) {
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

shortvec::~shortvec() {
	if (data) {
		free(data);
		datasize = 0;
		short_datasize = 0;
	}
};

void shortvec::release() {
	delete this;
};

void shortvec::resize(size_t newsize, short default_value, bool fill_default) {
	if (datasize == newsize)
		return;
	if ((newsize == 0) && (data = NULL)) {
		datasize = 0;
		short_datasize = 0;
		return;
	}
	short *tmpData = (short*)realloc(data, sizeof(short)*newsize);
	if (tmpData) {
		data = tmpData;
		size_t oldsize = datasize;
		datasize = newsize;
		short_datasize = datasize;
		if (oldsize < newsize) {
			if (fill_default == true) {
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
			short_datasize = 0;
		}
	}
	if ((data == NULL) && (newsize != 0)) 
		throw "out of memory";
};

void shortvec::push_back(const short& x) {
	if (datasize < short_datasize) {
		datasize++;
		operator()(size()-1) = x;
		return;
	} else {
		reserve(datasize + grow_by);
		push_back(x);
	}
};

void shortvec::set_grow(size_t igrow_by) {
	grow_by = igrow_by;
};

void shortvec::reserve(size_t reserve_size) {
	size_t oldsize = short_datasize;
	if (oldsize < reserve_size) {
		
		short *tmpData = (short*)realloc(data, sizeof(short)*reserve_size);
		if (tmpData) {
			data = tmpData;
			short_datasize = reserve_size;
		} else {
			data = NULL;
			if (reserve_size == 0) {
				datasize = 0;
				short_datasize = 0;
			}
		}
		if ((data == NULL) && (reserve_size != 0)) 
			throw "out of memory";

	}
};

void shortvec::swap(size_t i, size_t j) {
	#ifdef LSS_BOUNDS_CHECK
	if ((i < 1) || (i > size()))
			throw "invalid argument";
	if ((j < 1) || (j > size()))
			throw "invalid argument";
	#endif
	short temp = operator()(i);
	operator()(i) = operator()(j);
	operator()(j) = temp;
};

void shortvec::drop_data() {
	data = NULL;
	datasize = 0;
	short_datasize = 0;
};

size_t shortvec::write_file(int file, size_t size) const {
	size_t res = write(file, const_begin(), size*sizeof(short));
	return res;
};

size_t shortvec::read_file(int file, size_t size) {
	size_t res = read( file, begin(), sizeof(short)*size );
	return res;
};

#endif

}; // namespace surfit;



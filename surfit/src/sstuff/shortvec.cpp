
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

#include "shortvec.h"

namespace surfit {

shortvec * create_shortvec(int size, short default_value, int fill_default, int grow_by) {
	return new shortvec(size, default_value, fill_default, grow_by);
};

shortvec * create_shortvec(const shortvec &in) {
	return new shortvec(in);
};

shortvec::shortvec(const shortvec &in) {
	if (this != &in) {
		int newsize = in.size();
		data = (short*)malloc(sizeof(short)*newsize);
		if (data) {
			datasize = newsize;
			short_datasize = datasize;
			// init
			for (int i = 0; i < size(); i++) {
				operator()(i) = in(i);
			}
		};
		if ((data == NULL) && (newsize != 0)) {
			throw "out of memory";
		}	
	}
};

shortvec::shortvec(int newsize, short default_value, int fill_default, int igrow_by) {
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
		if (fill_default == 1) {
			for (int i = 0; i < size(); i++) {
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

void shortvec::resize(int newsize, short default_value, int fill_default) {
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
		int oldsize = datasize;
		datasize = newsize;
		short_datasize = datasize;
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

void shortvec::set_grow(int igrow_by) {
	grow_by = igrow_by;
};

void shortvec::reserve(int reserve_size) {
	int oldsize = short_datasize;
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

void shortvec::swap(int i, int j) {
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

void shortvec::erase(short* del) {
	short* cur = begin();
	for (int i = 0; i < size(); i++, cur++) {
		if (cur == del) {
			// perform deletion;
			memmove(cur,cur+1,(size()-i+1)*sizeof(short));
			datasize--;
			short_datasize--;
			return;
		}
	}
};

void shortvec::erase(int index) {
#ifdef LSS_BOUNDS_CHECK
	if (index > datasize) 
		throw "invalid argument";
#endif
	short* cur = begin();
	cur += index-1;
	memmove(cur,cur+1,(size()-index+1)*sizeof(short));
	datasize--;
	short_datasize--;
	return;
};

void shortvec::drop_data() {
	data = NULL;
	datasize = 0;
	short_datasize = 0;
};

}; // namespace surfit;



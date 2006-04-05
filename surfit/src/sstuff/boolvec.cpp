
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

#include "boolvec.h"

namespace surfit {

boolvec * create_boolvec(int size, bool default_value, int fill_default, int grow_by) {
	return new boolvec(size, default_value, fill_default, grow_by);
};

boolvec * create_boolvec(const boolvec & in) {
	return new boolvec(in);
};

boolvec::boolvec(const boolvec &in) {
	if (this != &in) {
		int newsize = in.size();
		data = (bool*)malloc(sizeof(bool)*newsize);
		if (data) {
			datasize = newsize;
			bool_datasize = datasize;
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

boolvec::boolvec(int newsize, bool default_value, int fill_default, int igrow_by) {
	grow_by = igrow_by;
	if (newsize == 0) {
		data = NULL;
		datasize = newsize;
		bool_datasize = newsize;
		return;
	}
	data = (bool*)malloc(sizeof(bool)*newsize);
	if (data) {
		datasize = newsize;
		bool_datasize = newsize;
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

boolvec::~boolvec() {
	if (data) {
		free(data);
		datasize = 0;
		bool_datasize = 0;
	}
};

void boolvec::release() {
	delete this;
};

void boolvec::resize(int newsize, bool default_value, int fill_default) {
	if (datasize == newsize)
		return;
	if ((newsize == 0) && (data = NULL)) {
		datasize = 0;
		bool_datasize = 0;
		return;
	}
	bool *tmpData = (bool*)realloc(data, sizeof(bool)*newsize);
	if (tmpData) {
		data = tmpData;
		int oldsize = datasize;
		datasize = newsize;
		bool_datasize = datasize;
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
			bool_datasize = 0;
		}
	}
	if ((data == NULL) && (newsize != 0)) 
		throw "out of memory";
};

void boolvec::push_back(const bool& x) {
	if (datasize < bool_datasize) {
		datasize++;
		operator()(size()-1) = x;
		return;
	} else {
		reserve(datasize + grow_by);
		push_back(x);
	}
};

void boolvec::set_grow(int igrow_by) {
	grow_by = igrow_by;
};

void boolvec::reserve(int reserve_size) {
	int oldsize = bool_datasize;
	if (oldsize < reserve_size) {
		
		bool *tmpData = (bool*)realloc(data, sizeof(bool)*reserve_size);
		if (tmpData) {
			data = tmpData;
			bool_datasize = reserve_size;
		} else {
			data = NULL;
			if (reserve_size == 0) {
				datasize = 0;
				bool_datasize = 0;
			}
		}
		if ((data == NULL) && (reserve_size != 0)) 
			throw "out of memory";

	}
};

void boolvec::swap(int i, int j) {
	#ifdef LSS_BOUNDS_CHECK
	if ((i < 1) || (i > size()))
			throw "invalid argument";
	if ((j < 1) || (j > size()))
			throw "invalid argument";
	#endif
	bool temp = operator()(i);
	operator()(i) = operator()(j);
	operator()(j) = temp;
};

void boolvec::erase(bool* del) {
	bool* cur = begin();
	for (int i = 0; i < size(); i++, cur++) {
		if (cur == del) {
			// perform deletion;
			memmove(cur,cur+1,(size()-i+1)*sizeof(bool));
			datasize--;
			bool_datasize--;
			return;
		}
	}
};

void boolvec::erase(int index) {
#ifdef LSS_BOUNDS_CHECK
	if (index > datasize) 
		throw "invalid argument";
#endif
	bool* cur = begin();
	cur += index-1;
	memmove(cur,cur+1,(size()-index+1)*sizeof(bool));
	datasize--;
	bool_datasize--;
	return;
};

void boolvec::drop_data() {
	data = NULL;
	datasize = 0;
	bool_datasize = 0;
};

}; // namespace surfit;



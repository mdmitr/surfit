
/*------------------------------------------------------------------------------
 *	$Id: vec.cpp 940 2007-01-31 12:56:27Z mishadm $
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

#ifndef XXL

#include "sizetvec.h"

namespace surfit {

sizetvec * create_sizetvec(size_t size) {
	return new sizetvec(size);
};

sizetvec::sizetvec(size_t size) 
{
	data = new std::vector<size_t>(size);
};

sizetvec::~sizetvec()
{
	delete data;
};

void sizetvec::release()
{
	delete this;
};

void sizetvec::push_back(size_t  val)
{
	data->push_back(val);
};

void sizetvec::reserve(size_t reserve_size) 
{
	data->reserve(reserve_size);
};

void sizetvec::resize(size_t newsize) 
{
	data->resize(newsize);
};

}; // namespace surfit

#endif


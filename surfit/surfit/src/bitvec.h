
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#ifndef __surfit_bitvec_included__
#define __surfit_bitvec_included__

#include <math.h>
#include <memory.h>
#include <assert.h>

namespace surfit {

/*! \class bitvec
    \brief A boolean vector with bit-based storage
*/
class bitvec {
public:
	
	//! constructor
	bitvec(int size = 0) {
		data = NULL;
		bits_per_byte = sizeof(int)*8;
		offset = (int)floor(log((double)bits_per_byte)/0.693147180559945);
		byte_size = (size + bits_per_byte - 1)/bits_per_byte;
		data = (int*)malloc(byte_size*sizeof(int));
		datasize = size;
	};

	//! copy constructor
	bitvec(const bitvec * src) {
		copy(src);
	}

	//! destructor
	~bitvec() {
		free(data);
	};

	//! returns value at a specified location
	bool get(int pos) const {
		assert( (pos >= 0) && (pos < datasize) );
		return ( *(data + (pos >> offset)) & (1 <<(pos - ((pos >> offset)<<offset)))) != 0;
	};

	//! sets value of element at a specified location to true
	void set_true(int pos) {
		assert( (pos >= 0) && (pos < datasize) );
		*(data + (pos >> offset)) |= (1 <<(pos - ((pos >> offset)<<offset)));
	};

	//! sets value of element at a specified location to false
	void set_false(int pos) {
		assert( (pos >= 0) && (pos < datasize) );
		*(data + (pos >> offset)) &=~ (1 <<(pos - ((pos >> offset)<<offset)));
	};

	//! copy constructor
	void copy(const bitvec * src) {
		data = NULL;
		bits_per_byte = src->bits_per_byte;
		offset = src->offset;
		datasize = src->datasize;
		byte_size = src->byte_size;
		data = (int*)malloc(byte_size*sizeof(int));
		memcpy(data, src->data, byte_size*sizeof(int));
	}

	//! fills vector with false values
	void init_false() {
		int i;
		int * ptr = data;
		for (i = 0; i < byte_size; i++) {
			*ptr = 0;
			ptr++;
		}
	};

	//! fills vector with true values
	void init_true() {
		int i;
		for (i = 0; i < size(); i++) 
			set_true(i);
	};

	//! returns size of the vector
	int size() const {
		return datasize;
	};

	//! returns size of "true" elements
	int true_size() const {
		int i;
		int cnt = 0;
		for (i = 0; i < datasize; i++) {
			if (get(i))
				cnt++;
		}
		return cnt;
	};

	//! writes four values, starting from pos
	void write4(int pos, 
		    bool b1, bool b2, bool b3, bool b4) 
	{
		int real_pos = pos*4;
		
		if (b1)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b2)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b3)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b4)
			set_true(real_pos);
		else 
			set_false(real_pos);
	};

	//! reads four values, starting from pos
	void get4(int pos, 
		  bool & b1, bool & b2, bool & b3, bool & b4) 
	{
		int real_pos = pos*4;
		b1 = get(real_pos);
		real_pos++;
		b2 = get(real_pos);
		real_pos++;
		b3 = get(real_pos);
		real_pos++;
		b4 = get(real_pos);
	};

	//! writes 10 values, starting from pos
	void write10(int pos, 
		     bool b1, bool b2, bool b3, bool b4, bool b5,
		     bool b6, bool b7, bool b8, bool b9, bool b10) 
	{
		int real_pos = pos*10;
		
		if (b1)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b2)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b3)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b4)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b5)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b6)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b7)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b8)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b9)
			set_true(real_pos);
		else 
			set_false(real_pos);
		real_pos++;

		if (b10)
			set_true(real_pos);
		else 
			set_false(real_pos);
		
	};

	//! reads 10 values, starting from pos
	void get10(int pos, 
		   bool & b1, bool & b2, bool & b3, bool & b4, bool & b5,
		   bool & b6, bool & b7, bool & b8, bool & b9, bool & b10) 
	{
		int real_pos = pos*10;
		b1 = get(real_pos);
		real_pos++;
		b2 = get(real_pos);
		real_pos++;
		b3 = get(real_pos);
		real_pos++;
		b4 = get(real_pos);
		real_pos++;
		b5 = get(real_pos);
		real_pos++;
		b6 = get(real_pos);
		real_pos++;
		b7 = get(real_pos);
		real_pos++;
		b8 = get(real_pos);
		real_pos++;
		b9 = get(real_pos);
		real_pos++;
		b10 = get(real_pos);
	};

	//! pointer to bit-based array
	int * data;

	//! amount of bits in one byte
	int bits_per_byte;
	//! some offset
	int offset;
	//! amount of bits in bitvec
	int datasize;
	//! bitvec size in bytes
	int byte_size;
	
};

}; // namespace surfit;

#endif


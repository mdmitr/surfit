
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

#ifndef __surfit_bitvec_included__
#define __surfit_bitvec_included__

#include <math.h>
#include <memory.h>
#include <assert.h>

namespace surfit {

class bitvec;

SSTUFF_EXPORT
bitvec * create_bitvec(int size = 0);

SSTUFF_EXPORT
bitvec * create_bitvec(const bitvec * src);

//SSTUFF_EXPORT
//bitvec * create_bitvec(int * begin, int * end, int size);

/*! \class bitvec
    \brief A boolean vector with bit-based storage
*/
class SSTUFF_EXPORT bitvec {

protected:
	
	//! constructor
	bitvec(int size = 0);

	//! copy constructor
	bitvec(const bitvec * src);

	//! another constructor
	bitvec(__int32 * begin, __int32 * end, int size);

public:

	friend SSTUFF_EXPORT
	bitvec * create_bitvec(int size);

	friend SSTUFF_EXPORT
	bitvec * create_bitvec(const bitvec * src);

private:
	//! destructor
	~bitvec();

public:
	//! destructor
	void release();

	//! returns value at a specified location
	bool get(int pos) const {
		assert( (pos >= 0) && (pos < datasize) );
		//return ( *(data + (pos >> offset)) & (1 <<(pos - ((pos >> offset)<<offset)))) != 0;
		return ( *(data + (pos >> 5)) & (1 <<(pos & ((1 << 5) - 1)))) != 0;
	};

	//! sets value of element at a specified location to true
	void set_true(int pos) {
		assert( (pos >= 0) && (pos < datasize) );
		*(data + (pos >> 5)) |= (1 <<(pos - ((pos >> 5)<<5)));
	};

	//! sets value of element at a specified location to false
	void set_false(int pos) {
		assert( (pos >= 0) && (pos < datasize) );
		*(data + (pos >> 5)) &=~ (1 <<(pos - ((pos >> 5)<<5)));
	};

	//! copy constructor
	void copy(const bitvec * src);

	//! fills vector with false values
	void init_false();

	//! fills vector with true values
	void init_true();

	//! true becomes false and false becomes true
	void invert();
	
	//! returns size of the vector
	int size() const;

	//! returns amount of "int"'s for save vector in memory
	int int_size() const;

	//! returns size of "true" elements
	int true_size() const;

	//! writes four values, starting from pos
	void write4(int pos, 
		    bool b1, bool b2, bool b3, bool b4); 
	
	//! reads four values, starting from pos
	void get4(int pos, bool * b);
	
	//! writes 10 values, starting from pos
	void write10(int pos, 
		     bool b1, bool b2, bool b3, bool b4, bool b5,
		     bool b6, bool b7, bool b8, bool b9, bool b10);
	
	//! reads 10 values, starting from pos
	void get10(int pos, bool * b);

	void AND(const bitvec * b);
	void OR(const bitvec * b);
	void XOR(const bitvec * b);
	void NOT();

	const __int32 * begin() const { return data; };
	__int32 * begin() { return data; };

protected:

	//! pointer to bit-based array
	__int32 * data;

	//! amount of bits in bitvec
	int datasize;
	//! bitvec size in bytes
	int byte_size;
	
};

}; // namespace surfit;

#endif


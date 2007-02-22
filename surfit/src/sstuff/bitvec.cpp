
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
#include "bitvec.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) 
#include <io.h>
#endif

#ifndef XXL

namespace surfit {

static int bits_per_byte = 32;

bitvec * create_bitvec(size_t size) {
	return new bitvec(size);
};

bitvec * create_bitvec(const bitvec * src) {
	return new bitvec(src);
};

bitvec::bitvec(size_t size) {
	data = NULL;
	byte_size = (size + bits_per_byte - 1)/bits_per_byte;
	data = (surfit_int32*)malloc((byte_size+1)*sizeof(surfit_int32));
	datasize = size;
};

bitvec::bitvec(const bitvec * src) {
	data = NULL;
	copy(src);
};

bitvec::bitvec(surfit_int32 * begin, surfit_int32 * end, size_t size) {
	data = begin;
	byte_size = (size + bits_per_byte - 1)/bits_per_byte;
	datasize = size;
};

bitvec::~bitvec() {
	free(data);
};

void bitvec::release() {
	delete this;
};

void bitvec::copy(const bitvec * src) {
	if (data)
		free(data);
	data = NULL;
	datasize = src->datasize;
	byte_size = src->byte_size;
	data = (surfit_int32*)malloc((byte_size+1)*sizeof(surfit_int32));
	memcpy(data, src->data, (byte_size+1)*sizeof(surfit_int32));
};

void bitvec::init_false() {
	size_t i;
	surfit_int32 * ptr = data;
	for (i = 0; i < byte_size; i++) {
		*ptr = 0;
		ptr++;
	}
};

//! fills vector with true values
void bitvec::init_true() {
	size_t i;
	surfit_int32 * ptr = data;
	for (i = 0; i < byte_size; i++) {
		*ptr = -1;
		ptr++;
	}
};

void bitvec::invert() {
	size_t i;
	for (i = 0; i < size(); i++) {
		if (get(i))
			set_false(i);
		else
			set_true(i);
	}
};

size_t bitvec::size() const {
	return datasize;
};

size_t bitvec::int_size() const {
	return byte_size;
};

size_t bitvec::true_size() const {
	size_t i;
	size_t cnt = 0;
	for (i = 0; i < datasize; i++) {
		if (get(i))
			cnt++;
	}
	return cnt;
};

bool bitvec::is_half_solved() const {
	size_t solved = 0;
	size_t unsolved = 0;
	size_t half = size()/2;
	size_t i;
	for (i = 0; i < datasize; i++) {
		if (get(i))
			solved++;
		else
			unsolved++;
		if (solved >= half)
			return true;
		if (unsolved >= half)
			return false;
	}
	return false;
};

void bitvec::write4(size_t pos, 
		    bool b1, bool b2, bool b3, bool b4) 
{
	size_t real_pos = pos*4;
	
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

void bitvec::get4(size_t pos, bool * b) const
{
	size_t real_pos = pos*4;
	size_t d = real_pos & 31;
	size_t q = real_pos>>5;
	surfit_int32 t = ((surfit_int32)data[q]) >> d;
	if (d > 32-5) 
		t |= data[q+1] << (32-d);
	(char&)b[0] = (char)(1 & (t >> 0));
	(char&)b[1] = (char)(1 & (t >> 1));
	(char&)b[2] = (char)(1 & (t >> 2));
	(char&)b[3] = (char)(1 & (t >> 3));
};

void bitvec::write8(size_t pos, 
		    bool b1, bool b2, bool b3, bool b4, 
		    bool b5, bool b6, bool b7, bool b8) 
{
	size_t real_pos = pos*8;
	
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
	

};

void bitvec::get8(size_t pos, bool * b) const
{
	size_t real_pos = pos*8;
	size_t d = real_pos & 31;
	size_t q = real_pos>>5;
	surfit_int32 t = ((surfit_int32)data[q]) >> d;
	if (d > 32-5) 
		t |= data[q+1] << (32-d);
	(char&)b[0] = (char)(1 & (t >> 0));
	(char&)b[1] = (char)(1 & (t >> 1));
	(char&)b[2] = (char)(1 & (t >> 2));
	(char&)b[3] = (char)(1 & (t >> 3));
	(char&)b[4] = (char)(1 & (t >> 4));
	(char&)b[5] = (char)(1 & (t >> 5));
	(char&)b[6] = (char)(1 & (t >> 6));
	(char&)b[7] = (char)(1 & (t >> 7));
};

void bitvec::write10(size_t pos, 
		     bool b1, bool b2, bool b3, bool b4, bool b5,
		     bool b6, bool b7, bool b8, bool b9, bool b10) 
{
	size_t real_pos = pos*10;
	
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

void bitvec::get10(size_t pos, bool * b) const
{
	size_t real_pos = pos*10;
	size_t d = real_pos & 31;
	size_t q = real_pos>>5;
	surfit_int32 t = ((surfit_int32)data[q]) >> d;
	if (d > 32-10)
		t |= data[q+1] << (32-d);
	(char&)b[0] = (char)(1 & (t >> 0));
	(char&)b[1] = (char)(1 & (t >> 1));
	(char&)b[2] = (char)(1 & (t >> 2));
	(char&)b[3] = (char)(1 & (t >> 3));
	(char&)b[4] = (char)(1 & (t >> 4));
	(char&)b[5] = (char)(1 & (t >> 5));
	(char&)b[6] = (char)(1 & (t >> 6));
	(char&)b[7] = (char)(1 & (t >> 7));
	(char&)b[8] = (char)(1 & (t >> 8));
	(char&)b[9] = (char)(1 & (t >> 9));
};

void bitvec::AND(const bitvec * b) {
	size_t i;
	for (i = 0; i < byte_size; i++) 
		*(data + i) &= *(b->const_begin()+i);
};

void bitvec::OR(const bitvec * b) {
	size_t i;
	for (i = 0; i < byte_size; i++) 
		*(data + i) |= *(b->const_begin()+i);
};

void bitvec::XOR(const bitvec * b) {
	size_t i;
	for (i = 0; i < size(); i++) {
		bool bb = (get(i) ^ b->get(i));
		if (bb)
			set_true(i);
		else
			set_false(i);
	}
};

void bitvec::NOT() {
	size_t i;
	for (i = 0; i < size(); i++) {
		bool bb = !get(i);
		if (bb)
			set_true(i);
		else
			set_false(i);
	}
};

size_t bitvec::write_file(int file) const {
	return write(file, data, datasize*sizeof(surfit_int32));
};

size_t bitvec::read_file(int file, size_t size) {
	return read( file, data, sizeof(surfit_int32)*size );
}

}; // namespace surfit;

#endif


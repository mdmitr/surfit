
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

namespace surfit {

static int bits_per_byte = 32;

bitvec * create_bitvec(int size) {
	return new bitvec(size);
};

bitvec * create_bitvec(const bitvec * src) {
	return new bitvec(src);
};

bitvec::bitvec(int size) {
	data = NULL;
	byte_size = (size + bits_per_byte - 1)/bits_per_byte;
	data = (__int32*)malloc(byte_size*sizeof(__int32));
	datasize = size;
};

bitvec::bitvec(const bitvec * src) {
	data = NULL;
	copy(src);
};

bitvec::bitvec(__int32 * begin, __int32 * end, int size) {
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
	data = (__int32*)malloc(byte_size*sizeof(__int32));
	memcpy(data, src->data, byte_size*sizeof(__int32));
};

void bitvec::init_false() {
	int i;
	__int32 * ptr = data;
	for (i = 0; i < byte_size; i++) {
		*ptr = 0;
		ptr++;
	}
};

//! fills vector with true values
void bitvec::init_true() {
	int i;
	for (i = 0; i < size(); i++) 
		set_true(i);
};

void bitvec::invert() {
	int i;
	for (i = 0; i < size(); i++) {
		if (get(i))
			set_false(i);
		else
			set_true(i);
	}
};

int bitvec::size() const {
	return datasize;
};

int bitvec::int_size() const {
	return byte_size;
};

int bitvec::true_size() const {
	int i;
	int cnt = 0;
	for (i = 0; i < datasize; i++) {
		if (get(i))
			cnt++;
	}
	return cnt;
};

void bitvec::write4(int pos, 
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

void bitvec::get4(int pos, bool * b) 
{
	unsigned int real_pos = pos*4;
	unsigned int d = real_pos & 31;
	unsigned int q = real_pos>>5;
	unsigned int t = ((unsigned int)data[q]) >> d;
	if (d > 32-5)
		t |= data[q+1] << (32-d);
	(char&)b[0] = 1 & (t >> 0);
	(char&)b[1] = 1 & (t >> 1);
	(char&)b[2] = 1 & (t >> 2);
	(char&)b[3] = 1 & (t >> 3);
	
};


void bitvec::write10(int pos, 
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

void bitvec::get10(int pos, bool * b) 
{
	unsigned int real_pos = pos*10;
	unsigned int d = real_pos & 31;
	unsigned int q = real_pos>>5;
	unsigned int t = ((unsigned int)data[q]) >> d;
	if (d > 32-10)
		t |= data[q+1] << (32-d);
	(char&)b[0] = 1 & (t >> 0);
	(char&)b[1] = 1 & (t >> 1);
	(char&)b[2] = 1 & (t >> 2);
	(char&)b[3] = 1 & (t >> 3);
	(char&)b[4] = 1 & (t >> 4);
	(char&)b[5] = 1 & (t >> 5);
	(char&)b[6] = 1 & (t >> 6);
	(char&)b[7] = 1 & (t >> 7);
	(char&)b[8] = 1 & (t >> 8);
	(char&)b[9] = 1 & (t >> 9);
};

void bitvec::AND(const bitvec * b) {
	int i;
	for (i = 0; i < byte_size; i++) 
		*(data + i) &= *(b->begin()+i);
};

void bitvec::OR(const bitvec * b) {
	int i;
	for (i = 0; i < byte_size; i++) 
		*(data + i) |= *(b->begin()+i);
};

void bitvec::XOR(const bitvec * b) {
	int i;
	for (i = 0; i < size(); i++) {
		bool bb = (get(i) ^ b->get(i));
		if (bb)
			set_true(i);
		else
			set_false(i);
	}
};


void bitvec::NOT() {
	int i;
	for (i = 0; i < size(); i++) {
		bool bb = !get(i);
		if (bb)
			set_true(i);
		else
			set_false(i);
	}
};

}; // namespace surfit;



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

#include "surfit_ie.h"

#include "fileio.h"

#include "matlab.h"
#include "matfile.h"

#include <sys/stat.h>
#include <algorithm>
#include <assert.h>
#include <errno.h>

namespace surfit {

FILE * matlabOpenFile(const char * filename, bool & writeHeader, bool append_file) {
	FILE * file = NULL;
	writeHeader = false;
	if (append_file) {
		file = fopen(filename,"a+b");
		writeHeader = false;
	} else {
		file = fopen(filename,"w+b");
		writeHeader = true;
	}
	if (file == NULL) {
		writelog(LOG_ERROR,"Can't open file %s for writing MAT-file : %s",filename,strerror(errno));
	}
	return file;
};

bool matlabWriteVector(const REAL * begin, const REAL * end, const char * filename, const char * name, const std::vector<int> * zero_rows, bool append_file) {

	writelog(LOG_DEBUG,"Writing vector %s to MAT-file %s", name, filename);

	bool writeHeader = false;
	FILE * file = matlabOpenFile(filename, writeHeader, append_file);

	char header[124] = "MATLAB 5.0 MAT-file. Creator: surfit";
#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
	__int16 version = 0x0100;
#else
    int16_t version = 0x0100;
#endif
    
	wchar_t endian = 'MI';

	long matrix_size = 0;

	int count = end-begin-zero_rows->size();

	matrix_size += 8;  // for array flags
	matrix_size += 8;  // for DOUBLE_CLASS
	matrix_size += 16; // for dimensions array
	matrix_size += 8;  // for array name

	matrix_size += count*8 + 8; // + 8 for header

	if (writeHeader) {
		if ( fwrite(header, 124, 1, file) != 1 ) return false;
		if ( fwrite(&version, 2, 1, file) != 1 ) return false;
		if ( fwrite(&endian, 2, 1, file) != 1 ) return false;
	}

	// tag
	if ( !mWrite4(file, miMATRIX) ) return false;
	if ( !mWrite4(file, matrix_size) ) return false;
	fflush(file);

	// Array Flags
	if ( !mWrite4(file,miUINT32) ) return false;
	if ( !mWrite4(file,8) ) return false;
	fflush(file);
	
	if ( !mWrite1(file,mxDOUBLE_CLASS) ) return false;
	if ( !mWrite1(file,0) ) return false;
	if ( !mWrite2(file,0) ) return false;
	if ( !mWrite4(file,count) ) return false; // nzmax
	fflush(file);

	// Dimensions Array
	if ( !mWrite4(file,miINT32) ) return false;
	if ( !mWrite4(file,8) ) return false;
	if ( !mWrite4(file,count) ) return false;
	if ( !mWrite4(file,1) ) return false;
	fflush(file);

	// Array Name
	mWriteName(file, name);
	fflush(file);

	double val;
	if ( !mWrite4(file, miDOUBLE) ) return false;
	if ( !mWrite4(file, count*sizeof(double) ) ) return false;
	
	const REAL * ptr;
	int written = 0;
	for (ptr = begin; ptr != end; ptr++) {
		int i = ptr-begin;
		if ( std::find(zero_rows->begin(), zero_rows->end(), i) != zero_rows->end() )
			continue;
		val = *ptr;
		if ( !mWriteDouble(file, val) ) return false;
		written++;
	}
	
	fclose(file);

	return true;

};

/*
bool matlabVector::writeMAT(const char * filename, const char * name, const std::vector<int> * zero_rows) {
	
	writelog(LOG_DEBUG,"Writing vector %s to MAT-file %s", name, filename);

	bool writeHeader = false;
	int file = matlabOpenFile(filename, writeHeader);

	char header[124] = "MATLAB 5.0 MAT-file. Creator: surfit";
#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
	__int16 version = 0x0100;
#else
    int16_t version = 0x0100;
#endif

	wchar_t endian = 'MI';

	long matrix_size = 0;

	int count = size()-zero_rows->size();

	matrix_size += 8;  // for array flags
	matrix_size += 8;  // for DOUBLE_CLASS
	matrix_size += 16; // for dimensions array
	matrix_size += 8;  // for array name

	matrix_size += count*8 + 8; // + 8 for header

	if (writeHeader) {
		if ( write(file, header, 124) != 124 ) return false;
		if ( write(file, &version,2) != 2 ) return false;
		if ( write(file, &endian,2) != 2 ) return false;
	}

	// tag
	if ( !mWrite4(file, miMATRIX) ) return false;
	if ( !mWrite4(file, matrix_size) ) return false;

	// Array Flags
	if ( !mWrite4(file,miUINT32) ) return false;
	if ( !mWrite4(file,8) ) return false;
	
	if ( !mWrite1(file,mxDOUBLE_CLASS) ) return false;
	if ( !mWrite1(file,0) ) return false;
	if ( !mWrite2(file,0) ) return false;
	if ( !mWrite4(file,count) ) return false; // nzmax

	// Dimensions Array
	if ( !mWrite4(file,miINT32) ) return false;
	if ( !mWrite4(file,8) ) return false;
	if ( !mWrite4(file,count) ) return false;
	if ( !mWrite4(file,1) ) return false;

	// Array Name
	mWriteName(file, name);

	double val;
	if ( !mWrite4(file, miDOUBLE) ) return false;
	if ( !mWrite4(file, count*sizeof(double) ) ) return false;
	
	int i;
	for (i = 0; i < count; i++) {
		if ( std::find(zero_rows->begin(),zero_rows->end(), i) != zero_rows->end() )
			continue;
		val = operator()(i);
		if ( !mWriteDouble(file, val) ) return false;
	}
	
	close(file);

	return true;
};
*/

bool matlabSparseMatrix::writeMAT(const char * filename, const char * name, const std::vector<int> * zero_rows, bool append_file) {

	writelog(LOG_DEBUG,"Writing matrix %s to MAT-file %s", name, filename);
	
	bool writeHeader = false;
	FILE * file = matlabOpenFile(filename, writeHeader, append_file);

	char header[124] = "MATLAB 5.0 MAT-file. Creator: surfit";
#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
    __int16 version = 0x0100;
#else
    int16_t version = 0x0100;
#endif
	wchar_t endian = 'MI';

	long matrix_size = 0;

	matrix_size += 8;  // for array flags
	matrix_size += 8;  // for SPARSE_CLASS
	matrix_size += 16; // for dimensions array
	matrix_size += 8;  // for array name

	size_t i,j;
	size_t count = 0;
	
	for (i = 0; i < rows(); i++) {
		for (j = 0; j < cols();) {
			if ( at(i,j,&j) != 0 )
				count++;
		}
	}

	long ic = (count)*4;
	ic += ic % 8;
	matrix_size += ic + 8; // +8 for header

	int jc_count = cols()-zero_rows->size();
	
	long jc = (jc_count+1)*4;
	jc += jc % 8;
	matrix_size += jc + 8; // +8 for header

	long pr = (count)*sizeof(double);
	pr += pr % 8;
	matrix_size += pr + 8; // +8 for header

	if (writeHeader) {
		if ( fwrite(header, 124, 1, file) != 1 ) return false;
		if ( fwrite(&version, 2, 1, file) != 1 ) return false;
		if ( fwrite(&endian, 2, 1, file) != 1 ) return false;
	}
			
	// tag
	if ( !mWrite4(file, miMATRIX) ) return false;
	if ( !mWrite4(file, matrix_size) ) return false;

	// Array Flags
	if ( !mWrite4(file,miUINT32) ) return false;
	if ( !mWrite4(file,8) ) return false;
	
	if ( !mWrite1(file,mxSPARSE_CLASS) ) return false;
	if ( !mWrite1(file,0) ) return false;
	if ( !mWrite2(file,0) ) return false;
	if ( !mWrite4(file,count) ) return false; // nzmax

	// Dimensions Array
	if ( !mWrite4(file,miINT32) ) return false;
	if ( !mWrite4(file,8) ) return false;
	if ( !mWrite4(file,jc_count) ) return false;
	if ( !mWrite4(file,jc_count) ) return false;

	// Array Name
	mWriteName(file, name);
	
	// ir
	if ( !mWrite4(file, miINT32) ) return false;
	if ( !mWrite4(file, count*4) ) return false;

	size_t index_count = 0;
	int index;
	for (i = 0; i < rows(); i++) {
		for (j = 0; j < cols();) {
			index = (int)j;
			if ( at(i,j,&j) != 0 ) {
				std::vector<int>::const_iterator it = std::lower_bound(zero_rows->begin(), zero_rows->end(), index);
				//if (it != zero_rows->end())
				index -= it-zero_rows->begin();
				if ( !mWrite4(file, index) ) return false;
				index_count++;
			}
		}
	}
	
	size_t padding = (count*4) % 8;
	for (i = 0; i < padding;) {
		if ( !mWrite4(file, 0) ) return false;
		i += 4;
	};

	// jc
	if ( !mWrite4(file, miINT32) ) return false;
	if ( !mWrite4(file, (jc_count+1)*4) ) return false;

	int j_index = 0;
	for (i = 0; i < rows(); i++) {
		if (std::find(zero_rows->begin(), zero_rows->end(), i) != zero_rows->end())
			continue;
		j = 0;
		if ( at(i,j,&j) != 0 ) {
			if ( !mWrite4(file, j_index) ) return false;
			j_index++;
		} else {
			if ( !mWrite4(file, j_index) ) return false;
		}

		for (;j < cols();) {
			if ( at(i,j,&j) != 0 )
				j_index++;
		}
	}
	
	mWrite4(file,(int)count);
	
	padding = ( (jc_count+1)*4 ) % 8;
	for (i = 0; i < padding;) {
		if ( !mWrite4(file, 0) ) return false;
		i += 4;
	};

	// pr
	double val;
	if ( !mWrite4(file, miDOUBLE) ) return false;
	if ( !mWrite4(file, count*sizeof(double) ) ) return false;
	for (i = 0; i < rows(); i++) {
		for (j = 0; j < cols(); j) {
			val = at(i,j,&j);
			if (val != 0)
				if ( !mWriteDouble(file, val) ) return false;
		}
	}
	
	fclose(file);

	return true;

};

void matlabSparseMatrix::get_zero_rows(std::vector<int> & zero_rows)
{
	zero_rows.clear();
	size_t i,j;
	size_t count = 0;
	
	for (i = 0; i < rows(); i++) {
		size_t rows_count = count;
		for (j = 0; j < cols();) {
			if ( at(i,j,&j) != 0 )
				count++;
		}
		if (rows_count == count) { // empty row
			zero_rows.push_back(i);
		}
	}
};

}; // namespace surfit


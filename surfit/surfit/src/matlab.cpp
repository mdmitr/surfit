
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

#include "ie.h"
#include "matlab.h"
#include "fileio.h"
#include "matfile.h"

#include <sys/stat.h>

namespace surfit {

int matlabOpenFile(const char * filename, bool & writeHeader) {
	int file = -1;
	writeHeader = false;
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	file = open(filename, O_BINARY|O_RDWR|O_APPEND);
#else
    file = open(filename, O_RDWR|O_APPEND);
#endif
	if (file == -1) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
		file = open(filename, O_BINARY|O_CREAT|O_APPEND|O_RDWR, S_IREAD|S_IWRITE);
#else 
        file = open(filename, O_CREAT|O_APPEND|O_RDWR, S_IREAD|S_IWRITE);
#endif
		writeHeader = true;
	}

	if (file == -1) {
		writelog(SURFIT_ERROR,"Can't open file %s for write MAT-file",filename);
	}
	return file;
};

bool matlabWriteVector(const REAL * begin, const REAL * end, const char * filename, const char * name) {

	writelog(SURFIT_DEBUG,"Writing vector %s to MAT-file %s", name, filename);

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

	int count = end-begin;

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
	if ( !mWrite4(file,end-begin) ) return false;
	if ( !mWrite4(file,1) ) return false;

	// Array Name
	mWriteName(file, name);

	double val;
	if ( !mWrite4(file, miDOUBLE) ) return false;
	if ( !mWrite4(file, count*sizeof(double) ) ) return false;
	
	const REAL * ptr;
	for (ptr = begin; ptr != end; ptr++) {
		val = *ptr;
		if ( !mWriteDouble(file, val) ) return false;
	}
	
	close(file);

	return true;

};

bool matlabVector::writeMAT(const char * filename, const char * name) {
	
	writelog(SURFIT_DEBUG,"Writing vector %s to MAT-file %s", name, filename);

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

	int count = size();

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
		val = operator()(i);
		if ( !mWriteDouble(file, val) ) return false;
	}
	
	close(file);

	return true;
};

bool matlabSparseMatrix::writeMAT(const char * filename, const char * name) {

	writelog(SURFIT_DEBUG,"Writing matrix %s to MAT-file %s", name, filename);

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

	matrix_size += 8;  // for array flags
	matrix_size += 8;  // for SPARSE_CLASS
	matrix_size += 16; // for dimensions array
	matrix_size += 8;  // for array name

	int i,j;
	int count = 0;
	
	for (i = 0; i < rows(); i++) {
		for (j = 0; j < cols();) {
			if ( operator()(i,j,&j) != 0 )
				count++;
		}
	}

	long ic = (count)*4;
	ic += ic % 8;
	matrix_size += ic + 8; // +8 for header

	int jc_count = cols();
	
	long jc = (jc_count+1)*4;
	jc += jc % 8;
	matrix_size += jc + 8; // +8 for header

	long pr = (count)*sizeof(double);
	pr += pr % 8;
	matrix_size += pr + 8; // +8 for header

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
	
	if ( !mWrite1(file,mxSPARSE_CLASS) ) return false;
	if ( !mWrite1(file,0) ) return false;
	if ( !mWrite2(file,0) ) return false;
	if ( !mWrite4(file,count) ) return false; // nzmax

	// Dimensions Array
	if ( !mWrite4(file,miINT32) ) return false;
	if ( !mWrite4(file,8) ) return false;
	if ( !mWrite4(file,cols()) ) return false;
	if ( !mWrite4(file,rows()) ) return false;

	// Array Name
	mWriteName(file, name);
	
	// ir
	if ( !mWrite4(file, miINT32) ) return false;
	if ( !mWrite4(file, count*4) ) return false;

	int index;
	for (i = 0; i < rows(); i++) {
		for (j = 0; j < cols();) {
			index = j;
			if ( operator()(i,j,&j) != 0 )
				if ( !mWrite4(file, index) ) return false;
		}
	}
	
	int padding = (count*4) % 8;
	for (i = 0; i < padding;) {
		if ( !mWrite4(file, 0) ) return false;
		i += 4;
	};

	// jc
	if ( !mWrite4(file, miINT32) ) return false;
	if ( !mWrite4(file, (jc_count+1)*4) ) return false;

	int j_index = 0;
	for (i = 0; i < rows(); i++) {
		j = 0;
		if ( operator()(i,j,&j) != 0 ) {
			if ( !mWrite4(file, j_index) ) return false;
			j_index++;
		} else {
			if ( !mWrite4(file, j_index) ) return false;
		}

		for (;j < cols();) {
			if ( operator()(i,j,&j) != 0 )
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
			val = operator()(i,j,&j);
			if (val != 0)
				if ( !mWriteDouble(file, val) ) return false;
		}
	}
	
	close(file);

	return true;

};


}; // namespace surfit


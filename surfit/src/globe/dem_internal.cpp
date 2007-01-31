
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

#include "globe_ie.h"

#include "sstuff.h"
#include "fileio.h"
#include "datafile.h"
#include "shortvec.h"
#include "bitvec.h"
#include "vec.h"
#include "byteswap_alg.h"

#include "dem.h"
#include "dem_internal.h"
#include "grid.h"
#include "grid_internal.h"
#include "mask.h"
#include "points.h"
#include "grid_line.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "sort_alg.h"
#include "globe_variables.h"
#include "surf.h"
#include "free_elements.h"
#include "byteswap_alg.h"

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <float.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_ZLIB_H
#include "minizip/unzip.h"
#endif

namespace surfit {

void mirror_shortvec(shortvec * sv, size_t NN) {

	short * buff = (short*)malloc(NN*sizeof(short));

	size_t MM = sv->size()/NN;

	size_t j;
	for (j = 0; j < MM/2; j++) {
		shortvec::iterator src1 = sv->begin() + j*NN;
		shortvec::iterator src2 = sv->begin() + (MM-j-1)*NN;

		// swap src1 with src2
		
		// reading row in buff
#ifdef XXL
		std::copy(src1, src1+NN, buff);
		std::copy(src2, src2+NN, src1);
		std::copy(buff, buff+NN, src2);
#else
		memcpy(buff, src1, NN*sizeof(short));
		memcpy(src1, src2, NN*sizeof(short));
		memcpy(src2, buff, NN*sizeof(short));
#endif
	};

	free(buff);

};

size_t calc_ptr(size_t i, size_t j, size_t N);

bool _dem_unload(d_dem *& srf) {
	if (!srf)
		return false;
	if (srf->getName())
		writelog(LOG_MESSAGE,"unloading dem \"%s\"", srf->getName());
	else 
		writelog(LOG_MESSAGE,"unloading noname dem");
	
	if (srf)
		srf->release();
	srf = NULL;
	return true;
};

d_dem * _dem_load_df(datafile * df, const char * demname) {

	if (!demname) 
		writelog(LOG_MESSAGE,"loading dem from file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"loading dem \"%s\" from file %s",demname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "dem_load : wrong datafile format";

	bool err = false;
	d_dem * srf = NULL;
	shortvec * icoeff = NULL;
	d_grid * grd = NULL;
	char * name = NULL;
	short undef_value = SHRT_MAX;

	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("dem")) {
			
			df->skipTagName();
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						name = (char*)malloc(strlen(df->getWord())+1);
						strcpy(name,df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}

				if ( df->isWord("short") ) {
					// read char name
					if (!df->readWord()) goto exit;
					
					if ( df->isWord("undef_value") ) {
						if ( !df->readShort(undef_value) ) goto exit;
						goto cont;
					}

					if (!df->skipShort(false)) goto exit;
					goto cont;
				}
				
				if ( df->isWord("array") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord("short") ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("coeff") ) {
							df->readShortArray(icoeff);
							goto cont;
						}
					}
					if ( !df->skipArray(false) ) goto exit;
				}
				
				if ( df->isWord("tag") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord("grid") ) {
						if ( !_grid_load_df_tag_readed(df, grd) ) goto exit;
						goto cont;
					}
					if (!df->skipToEndTag()) goto exit;
					goto cont;
				}
								
				if ( !df->skip(false) ) goto exit;
				goto cont;
cont:
				if ( !df->readWord() ) goto exit;
				continue;
			}
		} else {
			goto exit;
		}
		
		if ( !icoeff ) {
			writelog(LOG_ERROR,"dem_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(LOG_ERROR,"dem_load : empty geometry");
			err = true;
		}
		
		if (err) {
			if (icoeff)
				icoeff->release();
			if (grd)
				grd->release();
			free(name);
			return false;
		}
		
		srf = create_dem(icoeff, grd, name);
		srf->undef_value = undef_value;
		free(name);
		
		if (!demname) {
			return srf;
		} else {
			if (srf->getName()) {
				if (strcmp(srf->getName(),demname) == 0) {
					return srf;
				}
			}
			if (srf)
				srf->release();
			srf = NULL;
		}
		
	}
	
	return srf;

exit:

	if (!demname)
		writelog(LOG_ERROR, "dem_load : this file have no dem");
	else 
		writelog(LOG_ERROR, "dem_load : this file have no dem named %s", demname);
	return NULL;

};

d_dem * _dem_load(const char * filename, const char * demname) {

	datafile * df = new datafile(filename, DF_MODE_READ); // read

	d_dem * res = _dem_load_df(df, demname);

	if (!res)
		goto exit;

	delete df;
	return res;

exit:

	if (res)
		res->release();
	delete df;
	return NULL;
};

bool read_esri_variable(FILE * f, char * read_buf, char * name, char *& value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		if (value)
			free(value);
		value = strdup(read_buf);
		return true;
	}
	return false;
};

bool read_esri_variable(FILE * f, char * read_buf, char * name, double & value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		value = atof(read_buf);
		return true;
	}
	return false;
};

bool read_esri_variable(FILE * f, char * read_buf, char * name, int & value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		value = atoi(read_buf);
		return true;
	}
	return false;
};

bool read_esri_variable(FILE * f, char * read_buf, char * name, size_t & value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		value = atoi(read_buf);
		return true;
	}
	return false;
};

void read_dtm_variable(FILE * f, char * read_buf, char * name, char *& value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		fscanf(f, "%[ ]s", read_buf);
		fscanf(f, "%[ !-~]s", read_buf);
		if (strlen(read_buf))
			value = strdup(read_buf);
		else
			value = NULL;
	}
};

void read_dtm_variable(FILE * f, char * read_buf, char * name, double & value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		fscanf(f, "%s", read_buf);
		value = atof(read_buf);
	}
};

void read_dtm_variable(FILE * f, char * read_buf, char * name, int & value) {
	if (strcmp( read_buf, name) == 0) {
		fscanf(f, "%s", read_buf);
		fscanf(f, "%s", read_buf);
		value = atoi(read_buf);
	}
};

d_dem * _dem_load_dtm(const char * hdr_file, const char * bin_file) {

	FILE * hdr = fopen(hdr_file, "r");
	if (!hdr) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",hdr_file,strerror( errno ));
		return false;
	}

	char * Bin_file = NULL;

	////////////////////////
	//
	// parse header file
	//
	////////////////////////
	writelog(LOG_MESSAGE, "Processing %s", hdr_file);
	
	bool esri_hdr = false;
	char read_buf[2048];

	// determine hdr format
	while ( !feof(hdr) ) {
		fscanf(hdr, "%s", read_buf);
		str_toupper(read_buf);
		if ( strcmp( read_buf, "NROWS" ) == 0 ) {
			esri_hdr = true;
			break;
		}
	}

	fseek(hdr, 0, SEEK_SET);

	char * dem_name = NULL;
	char * grid_cell_registration = NULL;

	bool by_cols = true;
		
	double upper_map_y = -1;
	double lower_map_y = -1;
	double left_map_x = -1;
	double right_map_x = -1;
	int number_of_rows = -1;
	int number_of_columns = -1;
	double grid_size_x_ = -1;
	double grid_size_y_ = -1;
	double missing_flag = -1;
	int skipbytes = 0;
	bool swap_bytes = false;

	if (esri_hdr) {
		if (!bin_file) {
			Bin_file = strdup(hdr_file);
			char * ptr = Bin_file + strlen(Bin_file)-4;
			*ptr = '\0'; 
		}

		size_t nrows = UINT_MAX;
		size_t ncols = UINT_MAX;
		int nbands = 1;
		int nbits = 8;
		char * byteorder = strdup("I");
		char * layout = strdup("bil");

		double ulxmap = 0;
		double ulymap = 0;
		double xdim = 1;
		double ydim = 1;
		int bandrowbytes = 0;
		size_t totalrowbytes = UINT_MAX;
		int bandgapbytes = 0;
		double nodata = 0;

		while (!feof(hdr)) {
			fscanf(hdr, "%s", read_buf);
			str_toupper(read_buf);
			bool readed = false;
			if ((ncols != UINT_MAX) && (nrows == UINT_MAX))
				by_cols = false;
			readed = read_esri_variable(hdr, read_buf, "NCOLS", ncols) && readed;
			readed = read_esri_variable(hdr, read_buf, "NROWS", nrows) && readed;
			readed = read_esri_variable(hdr, read_buf, "NBANDS", nbands) && readed;
			readed = read_esri_variable(hdr, read_buf, "NBITS", nbits) && readed;
			readed = read_esri_variable(hdr, read_buf, "BYTEORDER", byteorder) && readed;
			readed = read_esri_variable(hdr, read_buf, "LAYOUT", layout) && readed;
			readed = read_esri_variable(hdr, read_buf, "SKIPBYTES", skipbytes) && readed;
			readed = read_esri_variable(hdr, read_buf, "ULXMAP", ulxmap) && readed;
			readed = read_esri_variable(hdr, read_buf, "ULYMAP", ulymap) && readed;
			readed = read_esri_variable(hdr, read_buf, "XDIM", xdim) && readed;
			readed = read_esri_variable(hdr, read_buf, "YDIM", ydim) && readed;
			readed = read_esri_variable(hdr, read_buf, "BANDROWBYTES", bandrowbytes) && readed;
			readed = read_esri_variable(hdr, read_buf, "TOTALROWBYTES", totalrowbytes) && readed;
			readed = read_esri_variable(hdr, read_buf, "BANDGAPBYTES", bandgapbytes) && readed;
			readed = read_esri_variable(hdr, read_buf, "NODATA", nodata) && readed;
		}

		/*
		if (xdim != ydim) 
		{
			fclose(hdr);
			writelog(LOG_ERROR, "Wrong header: xdim and ydim must be equal!");
			return NULL;
		}
		*/

		if ((ncols == UINT_MAX) || (nrows == UINT_MAX))
		{
			fclose(hdr);
			writelog(LOG_ERROR, "Wrong header file");
			return NULL;
		}

		if (nbits != 16) {
			fclose(hdr);
			writelog(LOG_ERROR, "Unsupported format. nbits must be 16.");
			return NULL;
		}

		number_of_columns = ncols;
		number_of_rows = nrows;
		grid_size_x_ = xdim;
		grid_size_y_ = ydim;
		left_map_x = ulxmap - xdim/2.;
		lower_map_y = ulymap - nrows*ydim + ydim/2.;
		missing_flag = nodata;
		if (strcmp(byteorder, "M") == 0)
			swap_bytes = true;

	} else {
		if (!bin_file) {
			Bin_file = strdup(hdr_file);
			char * ptr = Bin_file + strlen(Bin_file)-3;
			*ptr = 'b'; 
			ptr++;
			*ptr = 'i'; 
			ptr++;
			*ptr = 'n'; 
			ptr++;
		}
			
		while (!feof(hdr)) {
			fscanf(hdr, "%s", read_buf);
			str_toupper(read_buf);
			read_dtm_variable(hdr, read_buf, "FILE_TITLE", dem_name);
			read_dtm_variable(hdr, read_buf, "UPPER_MAP_Y", upper_map_y);
			read_dtm_variable(hdr, read_buf, "LOWER_MAP_Y", lower_map_y);
			read_dtm_variable(hdr, read_buf, "LEFT_MAP_X",  left_map_x);
			read_dtm_variable(hdr, read_buf, "RIGHT_MAP_X", right_map_x);
			read_dtm_variable(hdr, read_buf, "NUMBER_OF_ROWS", number_of_rows);
			read_dtm_variable(hdr, read_buf, "NUMBER_OF_COLUMNS", number_of_columns);
			read_dtm_variable(hdr, read_buf, "GRID_SIZE(X)", grid_size_x_);
			read_dtm_variable(hdr, read_buf, "GRID_SIZE(Y)", grid_size_y_);
			read_dtm_variable(hdr, read_buf, "GRID_CELL_REGISTRATION", grid_cell_registration);
			read_dtm_variable(hdr, read_buf, "MISSING_FLAG", missing_flag);
		}
		
		fclose (hdr);
		
	}

	/////////////////////
	//
	// reading bin file
	//
	//////////////////////

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	int bin;
	if (bin_file)
		bin = open(bin_file, O_RDONLY|O_BINARY);
	else
		bin = open(Bin_file, O_RDONLY|O_BINARY);
#else
	int bin;
	if (bin_file)
		bin = open(bin_file, O_RDONLY);
	else
		bin = open(Bin_file, O_RDONLY);
#endif
	if (bin == -1) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",bin_file,strerror( errno ));
		return false;
	}

	if (grid_size_x_ == -1) {
		writelog(LOG_ERROR,"Unsupported format.");
		return false;
	}

	int i,j, read_bytes;
#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
	__int16 * val = NULL;
	int size_int16 = sizeof(__int16);
	val = (__int16*) malloc( number_of_rows*number_of_columns*size_int16 );
#else
	int16_t * val = NULL;
	int size_int16 = sizeof(int16_t);
	val = (int16_t*) malloc( number_of_rows*number_of_columns*size_int16 );
#endif

	if (!val) {
		writelog(LOG_ERROR,"Not enougth memory.");
		return false;
	}
	int cnt = 0;

	writelog(LOG_MESSAGE,"%d grid nodes", number_of_rows*number_of_columns);

	read_bytes = read(bin,val,size_int16*number_of_rows*number_of_columns);
	if (read_bytes != size_int16*number_of_rows*number_of_columns) {
		writelog(LOG_ERROR,"Read error!");
		free(val);
		return false;
	}

	if (swap_bytes) 
		ByteSwapFunc((unsigned char *)val, read_bytes);

	d_grid * grd = create_grid(left_map_x, left_map_x + grid_size_x_*(number_of_columns-1), grid_size_x_,
		                   lower_map_y, lower_map_y + grid_size_y_*(number_of_rows-1), grid_size_y_);

	if (grid_cell_registration) {
		if (strcmp(grid_cell_registration,"center of cell") == 0) {
			grd->startX += grd->stepX/REAL(2);
			grd->startY += grd->stepX/REAL(2);
			grd->endX += grd->stepX/REAL(2);
			grd->endY += grd->stepX/REAL(2);
		}
	}
											   
	shortvec * coeff = create_shortvec(number_of_rows*number_of_columns);
	
	int N = number_of_columns;
	int M = number_of_rows;
	int I, J;
	short res_val;
	
	for (j = 0; j < M; j++) {
		for (i = 0; i < N; i++) {
			if (by_cols) {
				I = i;
				J = M-1-j;
			} else {
				I = N-1-i;
				J = j;
			}
			
			res_val = (short)*(val + I + J*N );
			if (res_val == missing_flag)
				res_val = SHRT_MAX;
			*(coeff->begin() + i + j*N) = res_val;
		}
	}
		
	free(val);

	d_dem * res = create_dem(coeff, grd, dem_name);
	res->undef_value = SHRT_MAX;

	int sizex = grd->getCountX();
	int sizey = grd->getCountY();
	int size = coeff->size();

	if (sizex != number_of_columns)
		writelog(LOG_ERROR,"sizex = %d, number_of_columns = %d", sizex, number_of_columns);
	if (sizey != number_of_rows)
		writelog(LOG_ERROR,"sizey = %d, number_of_rows = %d", sizey, number_of_rows);

	close (bin);
	if (Bin_file)
		free(Bin_file);

	if (dem_name)
		free(dem_name);

	if (grid_cell_registration)
		free(grid_cell_registration);


	return res;
};	

d_dem * _dem_load_hgt_zip(const char * hgt_zip_file) {

#ifdef HAVE_ZLIB_H
	unzFile zfile = unzOpen(hgt_zip_file);
	if (zfile == NULL) {
		writelog(LOG_ERROR, "Can't open file %s", hgt_zip_file);
		return NULL;
	};

	char * filename = (char *)malloc(32);
	int name_len = 0;
	char * name = NULL;
	char c1;
	int int1_len;
	int longtitude;
	char * temp;
	int latitude;
	int int2_len;
	unz_file_info_s file_info;
	int size;
	shortvec * coeff = NULL;
	void * ptr = NULL;
	int read_bytes = 0;
	size_t i;
	int len;
	double step;
	d_grid * grd = NULL;
	d_dem * res = NULL;

	if (UNZ_OK != unzGoToFirstFile(zfile)) 
		goto exit;

	if (UNZ_OK != unzGetCurrentFileInfo(zfile, &file_info, filename, 32, NULL, 0, NULL, 0))
		goto exit;

	if (UNZ_OK != unzOpenCurrentFile(zfile))
		goto exit;
	
	name = get_name(filename);
	name_len = strlen(name);

	c1 = *name;
	if ( c1 != 'S' && c1 != 'N') {
		writelog(LOG_ERROR,"dem_load_hgt_zip : %s - wrong filename", filename);
		goto exit;
	}
	// read int1
	int1_len = 0;
	while ( int1_len + 1 < name_len ) {
		const char c = *( name+1+int1_len );
		if ( (c <= '9') && (c >= '0') )
			int1_len++;
		else
			break;
	}
	if ( int1_len + 1 >= name_len ) {
		writelog(LOG_ERROR,"dem_load_hgt_zip : %s - wrong filename", filename);
		goto exit;
	}
	temp = (char *)malloc(int1_len+1);
	memcpy(temp, name+1, int1_len);
	temp[int1_len]='\0';
	//!!!!!!!!!!!!!!!
	longtitude = atoi(temp);
	if (c1 == 'S')
		longtitude = -longtitude;
	free(temp);

	c1 = *(name + 1 + int1_len);
	if ( c1 != 'E' && c1 != 'W') {
		writelog(LOG_ERROR,"dem_load_hgt_zip : %s - wrong filename", filename);
		goto exit;
	}	
	// read int2
	int2_len = 0;
	while ( int1_len + int2_len + 2 < name_len ) {
		const char c = *( name+2+int1_len+int2_len );
		if ( (c <= '9') && (c >= '0') )
			int2_len++;
		else
			break;
	}
	if ( int1_len + int2_len + 2 > name_len ) {
		writelog(LOG_ERROR,"dem_load_hgt_zip : %s - wrong filename", filename);
		goto exit;
	}
	temp = (char *)malloc(int2_len+1);
	memcpy(temp, name+2+int1_len, int2_len);
	temp[int2_len]='\0';
	//!!!!!!!!!!!!!!!
	latitude = atoi(temp);
	if (c1 == 'W')
		latitude = -latitude;
	free(temp);

	writelog(LOG_MESSAGE, "loading SRTM file %s", filename);

	// get file size in bytes
	size = file_info.uncompressed_size;

	coeff = create_shortvec(size/2);

#ifdef XXL
	ptr = (short int*)malloc(size/2*sizeof(short int));
	read_bytes = unzReadCurrentFile(zfile, ptr, size);
	if (read_bytes != size) {
		unzCloseCurrentFile(zfile);
		writelog(LOG_ERROR, "_dem_load_hgt_zip : error while reading file: %s",filename);
		goto exit;
	}
	std::copy((short int*)ptr, (short int*)ptr+size/2, coeff->begin());
	free(ptr);
#else
	ptr = (void*)coeff->begin();
	read_bytes = unzReadCurrentFile(zfile, ptr, size);
	if (read_bytes != size) {
		unzCloseCurrentFile(zfile);
		writelog(LOG_ERROR, "_dem_load_hgt_zip : error while reading file: %s",filename);
		goto exit;
	}
#endif
	
	for (i = 0; i < coeff->size(); i++) {
		ByteSwap((*coeff)(i));
	}

	len = (int)sqrt(size/2.);
	if (len == 1201) 
		writelog(LOG_MESSAGE,"this is SRTM-3 file");
	if (len == 3601) 
		writelog(LOG_MESSAGE,"this is SRTM-1 file");
	if ( (len != 1201) &&  (len != 3601) ) {
		unzCloseCurrentFile(zfile);
		writelog(LOG_ERROR,"this is not SRTM file");
		goto exit;
	}
	
	mirror_shortvec(coeff, len);
		
	step = 1./len;

	grd = create_grid(latitude,  latitude+(len-1)*step,  step,
		          longtitude,longtitude+(len-1)*step, step);

	res = create_dem(coeff, grd, name);
	res->undef_value = -32768;

	sstuff_free_char(name);
	free(filename);
	unzClose(zfile);

	return res;

exit:

	if (coeff)
		coeff->release();
	sstuff_free_char(name);
	free(filename);
	unzClose(zfile);
	return NULL;
#else
	writelog(LOG_ERROR,"zlib not detected");
	return NULL;
#endif
};

d_dem * _dem_load_hgt(const char * hgt_file) {

	// analyze hgt_file to create grid
	char * Name = get_name(hgt_file);
	char * name = strdup(Name);
	sstuff_free_char(Name);
	int name_len = strlen(name);
	char c1 = *name;
	if ( c1 != 'S' && c1 != 'N') {
		writelog(LOG_ERROR,"dem_load_hgt : %s - wrong filename", hgt_file);
		free(name);
		return NULL;
	}
	// read int1
	int int1_len = 0;
	while ( int1_len + 1 < name_len ) {
		const char c = *( name+1+int1_len );
		if ( (c <= '9') && (c >= '0') )
			int1_len++;
		else
			break;
	}
	if ( int1_len + 1 >= name_len ) {
		writelog(LOG_ERROR,"dem_load_hgt : %s - wrong filename", hgt_file);
		free(name);
		return NULL;
	}
	char * temp = (char *)malloc(int1_len+1);
	memcpy(temp, name+1, int1_len);
	temp[int1_len]='\0';
	//!!!!!!!!!!!!!!!
	int longtitude = atoi(temp);
	if (c1 == 'S')
		longtitude = -longtitude;
	free(temp);

	c1 = *(name + 1 + int1_len);
	if ( c1 != 'E' && c1 != 'W') {
		writelog(LOG_ERROR,"dem_load_hgt : %s - wrong filename", hgt_file);
		free(name);
		return NULL;
	}	
	// read int2
	int int2_len = 0;
	while ( int1_len + int2_len + 2 < name_len ) {
		const char c = *( name+2+int1_len+int2_len );
		if ( (c <= '9') && (c >= '0') )
			int2_len++;
		else
			break;
	}
	if ( int1_len + int2_len + 2 > name_len ) {
		writelog(LOG_ERROR,"dem_load_hgt : %s - wrong filename", hgt_file);
		free(name);
		return NULL;
	}
	temp = (char *)malloc(int2_len+1);
	memcpy(temp, name+2+int1_len, int2_len);
	temp[int2_len]='\0';
	//!!!!!!!!!!!!!!!
	int latitude = atoi(temp);
	if (c1 == 'W')
		latitude = -latitude;
	free(temp);
	
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	int bin;
	bin = open(hgt_file, O_RDONLY|O_BINARY);
#else
	int bin;
	bin = open(hgt_file, O_RDONLY);
#endif

	if (bin == -1) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",hgt_file,strerror( errno ));
		return NULL;
	}

	writelog(LOG_MESSAGE, "loading SRTM file %s", hgt_file);

	// get file size in bytes
	int size = lseek(bin, 0L, SEEK_END);
	lseek(bin, 0L, SEEK_SET);

	shortvec * coeff = create_shortvec(size/2);
	int read_bytes = coeff->read_file(bin, size/2);
	if (read_bytes != size) {
		close(bin);
		writelog(LOG_ERROR, "_dem_load_hgt : error while reading file: %s",hgt_file);
	}

	size_t  i;
	for (i = 0; i < coeff->size(); i++) {
		ByteSwap((*coeff)(i));
	}

	int len = (int)sqrt(size/2.);
	if (len == 1201) 
		writelog(LOG_MESSAGE,"this is SRTM-3 file");
	if (len == 3601) 
		writelog(LOG_MESSAGE,"this is SRTM-1 file");
	if ( (len != 1201) &&  (len != 3601) ) {
		if (coeff)
			coeff->release();
		close(bin);
		writelog(LOG_ERROR,"this is not SRTM file");
		return NULL;
	}
	
	mirror_shortvec(coeff, len);
		
	double step = 1./len;

	d_grid * grd = create_grid(latitude,  latitude+(len-1)*step,  step,
			           longtitude,longtitude+(len-1)*step, step);

	d_dem * res = create_dem(coeff, grd, name);
	res->undef_value = -32768;
	free(name);
	return res;
	
};

d_dem * _dem_load_globe(const char * filename) {

	if (strlen(filename) < 4) {
		writelog(LOG_ERROR,"_dem_load_globe: bad filename : %s", filename);
		return NULL;
	}

	int len = strlen(filename);

	const char a = *(filename+len-4);
	if ((a < 'a') || (a > 'p')) {
		writelog(LOG_ERROR,"_dem_load_globe: bad filename : %s", filename);
		return NULL;
	}

	const char v1 = *(filename+len-4+1);
	const char v2 = *(filename+len-4+2);

	#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	int bin;
	bin = open(filename, O_RDONLY|O_BINARY);
#else
	int bin;
	bin = open(filename, O_RDONLY);
#endif

	if (bin == -1) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	}

	// get file size in bytes
	int size = lseek(bin, 0L, SEEK_END);
	lseek(bin, 0L, SEEK_SET);

	int columns = 10800;
	int rows = size/2/10800;

	writelog(LOG_MESSAGE,"reading GLOBE file %s, version %c.%c, %dx%d", filename, v1, v2, columns, rows);

	if ((rows != 4800) && (rows != 6000)) {
		close(bin);
		writelog(LOG_ERROR, "_dem_load_globe : wrong file size: %s",filename);
	}

	shortvec * coeff = create_shortvec(size/2);
	int read_bytes = coeff->read_file(bin, size/2);
	if (read_bytes != size) {
		close(bin);
		writelog(LOG_ERROR, "_dem_load_globe : error while reading file: %s",filename);
	}

	mirror_shortvec(coeff, columns);
	
	int startx = 0;
	int endx = 0;
	int starty = 0;
	int endy = 0;

	switch(a) {
		case 'a':
		{
			startx = -180;
			endx = -90;
			starty = 50;
			endy = 90;
		}
		break;
		case 'b':
		{
			startx = -90;
			endx = 0;
			starty = 50;
			endy = 90;
		}
		break;
		case 'c':
		{
			startx = 0;
			endx = 90;
			starty = 50;
			endy = 90;
		}
		break;
		case 'd':
		{
			startx = 90;
			endx = 180;
			starty = 50;
			endy = 90;
		}
		break;

		case 'e':
		{
			startx = -180;
			endx = -90;
			starty = 0;
			endy = 50;
		}
		break;
		case 'f':
		{
			startx = -90;
			endx = 0;
			starty = 0;
			endy = 50;
		}
		break;
		case 'g':
		{
			startx = 0;
			endx = 90;
			starty = 0;
			endy = 50;
		}
		break;
		case 'h':
		{
			startx = 90;
			endx = 180;
				starty = 0;
			endy = 50;
		}
		break;

		case 'i':
		{
			startx = -180;
			endx = -90;
			starty = -50;
			endy = 0;
		}
		break;
		case 'j':
		{
			startx = -90;
			endx = 0;
			starty = -50;
			endy = 0;
		}
		break;
		case 'k':
		{
			startx = 0;
			endx = 90;
			starty = -50;
			endy = 0;
		}
		break;
		case 'l':
		{
			startx = 90;
			endx = 180;
			starty = -50;
			endy = 0;
		}
		break;

		case 'm':
		{
			startx = -180;
			endx = -90;
			starty = -90;
			endy = -50;
		}
		break;
		case 'n':
		{
			startx = -90;
			endx = 0;
			starty = -90;
			endy = -50;
		}
		break;
		case 'o':
		{
			startx = 0;
			endx = 90;
			starty = -90;
			endy = -50;
		}
		break;
		case 'p':
		{
			startx = 90;
			endx = 180;
			starty = -90;
			endy = -50;
		}
		break;

	}

	REAL stepx = REAL(1./120.);
	REAL stepy = stepx;

	d_grid * grd = create_grid(startx, endx-stepx, stepx,
			           starty, endy-stepy, stepy);

	int countx = grd->getCountX();
	int county = grd->getCountY();

	d_dem * res = create_dem(coeff, grd, filename+len-4);
	res->undef_value = -500;
	return res;


};

bool _dem_save(const d_dem * srf, const char * filename) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	res = _dem_save_df(srf, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _dem_save_df(const d_dem * srf, datafile * df) {

	if (!srf->getName()) 
		writelog(LOG_MESSAGE,"saving dem with no name to file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"saving dem \"%s\" to file %s",srf->getName(),df->get_filename());
		
	bool res = true;
	bool op;
	
	op = srf->writeTags(df);           res = ( op && res );
	
	return res;
};

d_dem * _dem_load_grd(const char * filename, const char * demname) 
{
	writelog(LOG_MESSAGE, "loading surface from Surfer GRD-ASCII format file %s",filename);

	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(LOG_ERROR, "dem_load_grd : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	int nx, ny;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	d_grid * grd = NULL;
	d_dem * res = NULL;
	shortvec * data = NULL;

	char buf[200];
	if (fscanf(file, "%s", buf) == 0)
		goto exit;
		
	if (strcmp(buf,"DSAA") != 0) 
		goto exit;
	
	int ix, iy;

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	nx = atoi(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	ny = atoi(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	minx = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxx = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	miny = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxy = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	minz = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxz = atof(buf);

	data = create_shortvec(nx*ny);
	short value;

	for(iy=0; iy<ny; iy++) {
		for(ix=0; ix<nx; ix++) {
			
			if (fscanf(file, "%s", buf) != 1)
				goto exit;
	
			value = atoi(buf);
			if ((value >= minz) && (value <= maxz))
				(*data)(ix + iy*nx) = value;
			else 
				(*data)(ix + iy*nx) = SHRT_MAX;
		}
	}

	if (fscanf(file, "%s", buf) == 1)
		goto exit;

	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = create_grid(minx, maxx, stepX,
			  miny, maxy, stepY);
	
	res = create_dem(data, grd);
	res->undef_value = SHRT_MAX;

	fclose(file);

	if (demname)
		res->setName(demname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;

exit:
	writelog(LOG_ERROR, "dem_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	if (grd)
		grd->release();
	fclose(file);
	return NULL;
};

bool _dem_save_grd(const d_dem * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"dem_save_grd : no dem loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving dem %s to file %s (grd-ASCII)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving dem (noname) to file %s (grd-ASCII)", filename);

	fprintf(f,"DSAA\n");
	int nx = srf->getCountX();
	int ny = srf->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", srf->grd->startX, srf->grd->endX);
	fprintf(f,"%lf %lf\n", srf->grd->startY, srf->grd->endY);

	REAL minZ, maxZ;
	srf->getMinMaxZ(minZ, maxZ);
	fprintf(f,"%lf %lf\n", minZ, maxZ);

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
    
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = (*(srf->coeff))( ix + nx*iy );
			fprintf(f,"%lf ", val);
			if (ncnt>9) { 
				fprintf(f,"\n");
				ncnt = 0;
			}
			ncnt++;
		}
		fprintf(f,"\n");
	}

	fclose(f);

	return true;
};

bool _dem_save_xyz(const d_dem * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"dem_save_xyz : no dem loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving dem %s to file %s (xyz-ASCII)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving dem (noname) to file %s (xyz-ASCII)", filename);

	int nx = srf->getCountX();
	int ny = srf->getCountY();

	int iy, ix;
	int cnt = 0;
	REAL val;
	REAL x_coord, y_coord;
	
    
	for(iy=0; iy<ny; iy++)	{
		for(ix=0; ix<nx; ix++)	{
			srf->getCoordNode(ix, iy, x_coord, y_coord);
			val = (*(srf->coeff))( ix + nx*iy );
			fprintf(f,"%lf %lf %lf \n", x_coord, y_coord, val);
			
		}
	}

	fclose(f);

	return true;
};

bool _dem_save_dtm(const d_dem * srf, const char * filename)
{
	writelog(LOG_ERROR,"dem_save_dtm: Not implemented!");
	return false;
};

d_points * _dem_to_points(const d_dem * srf) {

	if (!srf->coeff) {
		writelog(LOG_ERROR,"convert_dem_to_pnts : wrong surf - no coeffs");
		return NULL;
	}

	vec * X = create_vec(srf->coeff->size());
	vec * Y = create_vec(srf->coeff->size());
	vec * Z = create_vec(srf->coeff->size());
	
	vec::iterator X_ptr = X->begin();
	vec::iterator Y_ptr = Y->begin();
	vec::iterator Z_ptr = Z->begin();

	size_t i,j;
	REAL x,y,z;
	for (j = 0; j < srf->getCountY(); j++) {
		for (i = 0; i < srf->getCountX(); i++) {
			srf->getCoordNode(i,j,x,y);
			z = srf->getValue(x, y);
			
			if (z != srf->undef_value) {
				*X_ptr = x;
				*Y_ptr = y;
				*Z_ptr = z;
				X_ptr++;
				Y_ptr++;
				Z_ptr++;
			}
		}
	}

	int size = X_ptr-X->begin();

	if (size == 0) {
		X->release();
		Y->release();
		Z->release();
		return NULL;
	}
	X->resize(size);
	Y->resize(size);
	Z->resize(size);

	return create_points(X, Y, Z,
			     srf->getName());
	
};

d_dem * _dem_project(const d_dem * srf, const d_grid * grd) {

	size_t size_x = grd->getCountX();
	size_t size_y = grd->getCountY();

	shortvec * coeff = create_shortvec(size_x*size_y,0,0);  // do not fill this vector
	
	size_t dem_size = srf->coeff->size();
	size_t dem_sizeX = srf->getCountX();
	size_t dem_sizeY = srf->getCountY();

	if (srf->getName())
		writelog(LOG_MESSAGE,"Projecting dem \"%s\" (%d x %d) => (%d x %d)",srf->getName(), dem_sizeX, dem_sizeY, size_x, size_y);
	else 
		writelog(LOG_MESSAGE,"Projecting dem (%d x %d) => (%d x %d)", dem_sizeX, dem_sizeY, size_x, size_y);

	{

		REAL x, y;
		size_t I0, J0, I1, J1;
		REAL value;
		size_t i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = srf->grd->stepX;
		REAL hY = srf->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
				
				d_grid * g = srf->grd;
				I0 = (size_t)MAX(0,floor( (x - g->startX)/g->stepX ));
				J0 = (size_t)MAX(0,floor( (y - g->startY)/g->stepY ));

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), dem_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), dem_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), dem_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), dem_sizeY-1);

				srf->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(srf->coeff))(I0 + dem_sizeX*J0);
				z1 = (*(srf->coeff))(I1 + dem_sizeX*J0);
				z2 = (*(srf->coeff))(I1 + dem_sizeX*J1);
				z3 = (*(srf->coeff))(I0 + dem_sizeX*J1);
				
				if (
					(z0 == srf->undef_value) ||
					(z1 == srf->undef_value) ||
					(z2 == srf->undef_value) ||
					(z3 == srf->undef_value) 
					) 
				{
					
					REAL sum = REAL(0);
					int cnt = 0;
					
					if (z0 != srf->undef_value) {
						sum += z0;
						cnt++;
					}
					if (z1 != srf->undef_value) {
						sum += z1;
						cnt++;
					}
					if (z2 != srf->undef_value) {
						sum += z2;
						cnt++;
					}
					if (z3 != srf->undef_value) {
						sum += z3;
						cnt++;
					}
					
					if (cnt == 0) {
						(*coeff)(i + j*size_x) = srf->undef_value;
						continue;
					}

					REAL mean_z = sum/REAL(cnt);
					if (z0 == srf->undef_value)
						z0 = mean_z;
					if (z1 == srf->undef_value)
						z1 = mean_z;
					if (z2 == srf->undef_value)
						z2 = mean_z;
					if (z3 == srf->undef_value)
						z3 = mean_z;
					
				}
				
				delta_x = x - x0;
				delta_y = y - y0;
				
				// первый шаг линейной интерпол€ции
				REAL z11 = (z2-z1)*delta_y/hY+z1;
				REAL z22 = (z3-z0)*delta_y/hY+z0;
				
				// второй шаг линейной интерпол€ции
				REAL res = (z11-z22)*delta_x/hX+z22;
								
				(*coeff)(i + j*size_x) = (short)res;
				
								
			}
		}
	}
	
	d_grid * new_grd = create_grid(grd);
	d_dem * res = create_dem(coeff, new_grd, srf->getName());
	res->undef_value = srf->undef_value;
	return res;
};

void _dem_info(const d_dem * srf) {
	if (!srf)
		return;
	if (srf->getName()) 
		writelog(LOG_MESSAGE,"dem (%s) : size=(%d x %d)", srf->getName(), srf->getCountX(), srf->getCountY());
	else 
		writelog(LOG_MESSAGE,"dem noname : size=(%d x %d)", srf->getCountX(), srf->getCountY());
};

bool _dem_resid(const d_dem * srf, const d_points * tsk, const char * filename) {
	if (!srf)
		return false;
	if (!tsk)
		return false;

	writelog(LOG_MESSAGE, "Calcualting residuals...");

	FILE * f = fopen(filename, "w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	int task_size = tsk->size();
	int cnt;
	REAL res;
	REAL x,y,z;

	REAL maxres = -FLT_MAX;

	for (cnt = 0; cnt < task_size; cnt++) {
		x = (*(tsk->X))(cnt);
		y = (*(tsk->Y))(cnt);
		z = (*(tsk->Z))(cnt);
		res = srf->getValue(x,y) - z;
		maxres = (REAL)MAX(fabs(res),maxres);
		fprintf(f,"%lf \t %lf \t %lf %lf\n",x,y,z,res);
	}
	
	fclose(f);
	writelog(LOG_MESSAGE,"max residual : %lf", maxres);

	return true;

};

REAL _dem_D1(const d_dem * srf) {

	size_t i,j;
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	shortvec::const_iterator ptr = srf->coeff->const_begin();

	REAL v1, v2;

	REAL dx = 0;
	int dx_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			if ((v1 != srf->undef_value) && (v2 != srf->undef_value)) {
				dx += (v2-v1)*(v2-v1);
				dx_cnt++;
			}
		}
	}

	dx /= REAL(dx_cnt);

	REAL dy = 0;
	int dy_cnt = 0;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-2; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + i + (j+1)*NN);
			if ((v1 != srf->undef_value) && (v2 != srf->undef_value)) {
				dy += (v2-v1)*(v2-v1);
				dy_cnt++;
			}
		}
	}

	dy /= REAL(dy_cnt);

	REAL h_x_2 = (srf->grd->stepX)*(srf->grd->stepX);
	REAL h_y_2 = (srf->grd->stepY)*(srf->grd->stepY);

	REAL res = dx/h_x_2 + dy/h_y_2;

	return res;

};

REAL _dem_D2(const d_dem * srf) {

	size_t i,j;
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	shortvec::const_iterator ptr = srf->coeff->const_begin();

	REAL v1, v2, v3, v4;

	REAL dx2 = 0;
	int dx2_cnt = 0;
	for (i = 0; i < NN-3; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + (i+2) + j*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value)) {
				dx2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dx2_cnt++;
			}
		}
	}

	REAL dxdy = 0;
	size_t dxdy_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-2; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + i + (j+1)*NN);
			v4 = *(ptr + (i+1) + (j+1)*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value) && 
				(v4 != srf->undef_value) ) {
				dxdy += (v4-v3-v2+v1)*(v4-v3-v2+v1);
				dxdy_cnt++;
			}
		}
	}

	REAL dy2 = 0;
	size_t dy2_cnt = 0;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-3; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + i + (j+1)*NN);
			v3 = *(ptr + i + (j+2)*NN);
			if ((v1 != srf->undef_value) && 
				(v2 != srf->undef_value) && 
				(v3 != srf->undef_value)) {
				dy2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dy2_cnt++;
			}
		}
	}

	REAL h_x_2 = (srf->grd->stepX)*(srf->grd->stepX);
	REAL h_y_2 = (srf->grd->stepY)*(srf->grd->stepY);
	writelog(LOG_DEBUG,"h_x_2 = %lf    h_y_2 = %lf",h_x_2, h_y_2);
	writelog(LOG_DEBUG,"dx2_cnt = %d dy2_cnt = %d dxdy_cnt = %d",dx2_cnt, dy2_cnt, dxdy_cnt);
	writelog(LOG_DEBUG,"dx2  = %lf",dx2);
	writelog(LOG_DEBUG,"dy2  = %lf",dy2);
	writelog(LOG_DEBUG,"dxdy = %lf",dxdy);

	dx2 /= REAL(dx2_cnt);
	dxdy /= REAL(dxdy_cnt);
	dy2 /= REAL(dy2_cnt);

	REAL res = dx2/(h_x_2*h_x_2) + 2*dxdy/(h_x_2*h_y_2) + dy2/(h_y_2*h_y_2);

	return res;
};

void _add_globe_dems(d_dem * srf) {
	if (!srf)
		return;
	globe_dems->push_back(srf);
};

d_dem * _dem_gradient(const d_dem * srf) {
	
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	bool first_x, second_x;
	bool first_y, second_y;

	shortvec * coeff = create_shortvec(NN*MM);

	size_t i, j, pos, pos1;
	REAL val;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			
			first_x = true;
			second_x = true;
			first_y = true;
			second_y = true;

			if (i == 0)
				second_x = false;
			if (i == NN-1)
				first_x = false;
			if (j == 0)
				second_y = false;
			if (j == MM-1)
				first_y = false;

			pos = i + j*NN;
			REAL pos_val = (*(srf->coeff))(pos);
			if (pos_val == srf->undef_value) {
				(*(coeff))(pos) = srf->undef_value;
				continue;
			}
			REAL pos1_val;

			val = REAL(0);

			if (first_x) {
				pos1 = (i+1) + j*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_x) {
				pos1 = (i-1) + j*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			if (first_y) {
				pos1 = (i) + (j+1)*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_y) {
				pos1 = i + (j-1)*NN;
				pos1_val = (*(srf->coeff))(pos1);
				if (pos1_val == srf->undef_value) {
					(*(coeff))(pos) = srf->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			(*(coeff))(pos) = (short int)val;
			
		}
	}

	d_grid * grd = create_grid(srf->grd);
	d_dem * res = create_dem(coeff, grd, srf->getName());
	res->undef_value = srf->undef_value;
	return res;

};

d_mask * _dem_to_mask(const d_dem * srf, short true_from, short true_to) {
	
	bitvec * bcoeff = create_bitvec( srf->coeff->size() );
	size_t  i;
	short val;
	for (i = 0; i < srf->coeff->size(); i++) {
		val = (*(srf->coeff))(i);
		bool bval = ( (val >= true_from) && (val <= true_to) );
		if (bval)
			bcoeff->set_true(i);
		else
			bcoeff->set_false(i);
	};

	d_grid * fgrd = srf->grd;
	d_grid * grd = create_grid(fgrd);

	d_mask * msk = create_mask(bcoeff, grd);

	return msk;
};

d_surf * _dem_to_surf(const d_dem * srf) {
	
	extvec * coeff = create_extvec( srf->coeff->size() );
	size_t i;
	short val;
	for (i = 0; i < srf->coeff->size(); i++) {
		val = (*(srf->coeff))(i);
		if (val == srf->undef_value)
			(*coeff)(i) = FLT_MAX;
		else
			(*coeff)(i) = (REAL)val;
	};

	d_grid * fgrd = srf->grd;
	d_grid * grd = create_grid(fgrd);

	d_surf * res = create_surf(coeff, grd);

	return res;
};

bool _dem_decomp(d_dem * srf) {
	if (!srf)
		return false;
	
	return srf->decompose();
};

bool _dem_auto_decomp(d_dem * srf, REAL eps) {
	if (!srf)
		return false;

	return srf->auto_decompose(eps);
};

bool _dem_recons(d_dem * srf) {
	if (!srf)
		return false;

	return srf->reconstruct();
};

bool _dem_full_recons(d_dem * srf) {
	if (!srf)
		return false;

	return srf->full_reconstruct();
};


}; // namespace surfit;




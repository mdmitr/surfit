
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
#include "real.h"
#include "func.h"
#include "func_internal.h"
#include "grid.h"
#include "grid_internal.h"
#include "task.h"
#include "vec.h"
#include "fileio.h"
#include "datafile.h"
#include "grid_line.h"
#include "wfunc.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "func_user.h"

#include "color_scale.h" // for bmp saving
#include "sort_alg.h"

#include <math.h>
#include <float.h>
#include <errno.h>

namespace surfit {

int calc_ptr(int i, int j, int N);

bool _func_unload(func *& fnc) {
	if (!fnc)
		return false;
	if (fnc->getName())
		writelog(SURFIT_MESSAGE,"unloading func \"%s\"", fnc->getName());
	else 
		writelog(SURFIT_MESSAGE,"unloading noname func");
	
	delete fnc;
	fnc = NULL;
	return true;
};

bool _func_check() {
	if (surfit_func)
		return true;
	return false;
};

func * _func_load_df(datafile * df, const char * funcname) {

	if (!funcname) 
		writelog(SURFIT_MESSAGE,"loading func with no name from file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"loading func \"%s\" from file %s",funcname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "func_load : wrong datafile format";

	bool err = false;
	func * fnc = NULL;
	vec * icoeff = NULL;
	grid * grd = NULL;
	char * name = NULL;
	REAL undef_value = FLT_MAX;

	REAL * coeff_begin = NULL;
	REAL * coeff_end = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("func")) {
			
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

				if ( df->isWord(REAL_NAME) ) {
					// read char name
					if (!df->readWord()) goto exit;
					
					if ( df->isWord("undef_value") ) {
						if ( !df->readReal(undef_value) ) goto exit;
						goto cont;
					}

					if (!df->skipReal(false)) goto exit;
					goto cont;
				}
				
				if ( df->isWord("array") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord(REAL_NAME) ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("coeff") ) {
							df->readRealArray(coeff_begin, coeff_end);
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
		
		icoeff = new vec(coeff_begin, coeff_end);
		
		if ( !icoeff ) {
			writelog(SURFIT_ERROR,"func_load : empty coeff");
			err = true;
		}
		
		if ( !grd ) {
			writelog(SURFIT_ERROR,"func_load : empty geometry");
			err = true;
		}
		
		if (err) {
			delete icoeff;
			delete grd;
			free(name);
			return false;
		}
		
		fnc = new func(icoeff, grd, name);
		fnc->undef_value = undef_value;
		free(name);
		
		if (!funcname) {
			return fnc;
		} else {
			if (fnc->getName()) {
				if (strcmp(fnc->getName(),funcname) == 0) {
					return fnc;
				}
			}
			delete fnc;
			fnc = NULL;
		}
		
	}
	
	return fnc;

exit:

	if (!funcname)
		writelog(SURFIT_ERROR, "func_load : this file have no func");
	else 
		writelog(SURFIT_ERROR, "func_load : this file have no func named %s", funcname);
	return NULL;

};

func * _func_load(const char * filename, const char * funcname, int mode) {

	datafile * df = new datafile(filename, DF_MODE_READ, mode); // read

	func * res = _func_load_df(df, funcname);

	if (!res)
		goto exit;

	delete df;
	return res;

exit:

	delete res;
	delete df;
	return NULL;
};
	

bool _func_save(func * fnc, const char * filename, const char * funcname) {
	
	bool res = true;

	datafile *df = new datafile(filename, DF_MODE_WRITE, get_rw_mode()); // write
	if (!df->condition()) {
		delete df;
		return false;
	}

	fnc->setName(funcname);

	res = _func_save_df(fnc, df);

	bool op = df->writeEof();				res = ( op && res );
	
	delete df;
	return res;
};

bool _func_save_df(func * fnc, datafile * df) {

	if (!fnc->getName()) 
		writelog(SURFIT_MESSAGE,"saving func with no name to file %s",df->get_filename());
	else 
		writelog(SURFIT_MESSAGE,"saving func \"%s\" to file %s",fnc->getName(),df->get_filename());
		
	bool res = true;
	bool op;
	
	op = fnc->writeTags(df);           res = ( op && res );
	
	return res;
};

func * _func_load_grd(const char * filename, const char * funcname) 
{
	writelog(SURFIT_MESSAGE, "loading surface from Surfer GRD-ASCII format file %s",filename);

	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(SURFIT_ERROR, "func_load_grd : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	int nx, ny;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	REAL * values = NULL;
	grid * grd = NULL;
	func * res = NULL;
	vec * data = NULL;

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

	values = (REAL*)malloc(sizeof(REAL)*nx*ny);
	REAL value;

	for(iy=0; iy<ny; iy++) {
		for(ix=0; ix<nx; ix++) {
			
			if (fscanf(file, "%s", buf) != 1)
				goto exit;
	
			value = atof(buf);
			if ((value >= minz) && (value <= maxz))
				*(values + ix + iy*nx) = value;
			else 
				*(values + ix + iy*nx) = undef_value;
		}
	}

	if (fscanf(file, "%s", buf) == 1)
		goto exit;

	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = new grid(minx, maxx, stepX,
                   miny, maxy, stepY);

	data = new vec(values, values + nx*ny);

	res = new func(data, grd);

	fclose(file);

	res->setName(funcname);

	return res;

exit:
	writelog(SURFIT_ERROR, "func_load_grd : Wrong file format %s", filename);
	
	delete res;
	delete data;
	delete grd;
	free(values);
	fclose(file);
	return NULL;
};

bool _func_save_grd(func * fnc, const char * filename) {

	if (!filename)
		return false;

	if (!fnc) {
		writelog(SURFIT_ERROR,"func_save_grd : no func loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(SURFIT_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (fnc->getName())
		writelog(SURFIT_MESSAGE,"Saving func %s to file %s (grd-ASCII)", fnc->getName(), filename);
	else 
		writelog(SURFIT_MESSAGE,"Saving func (noname) to file %s (grd-ASCII)", filename);

	fprintf(f,"DSAA\n");
	int nx = fnc->getCountX();
	int ny = fnc->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", fnc->grd->startX, fnc->grd->endX);
	fprintf(f,"%lf %lf\n", fnc->grd->startY, fnc->grd->endY);

	REAL minZ, maxZ;
	fnc->getMinMaxZ(minZ, maxZ);
	fprintf(f,"%lf %lf\n", minZ, maxZ);

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
    
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = (*(fnc->coeff))( ix + nx*iy );
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

bool _func_save_xyz(func * fnc, const char * filename) {

	if (!filename)
		return false;

	if (!fnc) {
		writelog(SURFIT_ERROR,"func_save_xyz : no func loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(SURFIT_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	if (fnc->getName())
		writelog(SURFIT_MESSAGE,"Saving func %s to file %s (xyz-ASCII)", fnc->getName(), filename);
	else 
		writelog(SURFIT_MESSAGE,"Saving func (noname) to file %s (xyz-ASCII)", filename);

	int nx = fnc->getCountX();
	int ny = fnc->getCountY();

	int iy, ix;
	int cnt = 0;
	REAL val;
	REAL x_coord, y_coord;
	
    
	for(iy=0; iy<ny; iy++)	{
		for(ix=0; ix<nx; ix++)	{
			fnc->getCoordNode(ix, iy, x_coord, y_coord);
			val = (*(fnc->coeff))( ix + nx*iy );
			fprintf(f,"%lf %lf %lf \n", x_coord, y_coord, val);
			
		}
	}

	fclose(f);

	return true;
};

bool _func_save_bmp(func * fnc, const char * filename) {

	if (!filename)
		return false;
	
	typedef struct _BITMAPFILEHEADER {  // Offset   Size
		short   bfType;                 //      0      2
		long    bfSize;                 //      2      4
		short   bfReserved1;            //      6      2
		short   bfReserved2;            //      8      2
		long    bfOffBits;              //     10      4
	} BITMAPFILEHEADER;                 // Total size: 14

	typedef struct _BITMAPINFOHEADER {  // Offset   Size
		long    biSize;                 //      0      4
		long    biWidth;                //      4      4
		long    biHeight;               //      8      4
		short   biPlanes;               //     12      2
		short   biBitCount;             //     14      2
		long    biCompression;          //     16      4
		long    biSizeImage;            //     20      4
		long    biXPelsPerMeter;        //     24      4
		long    biYPelsPerMeter;        //     28      4
		long    biClrUsed;              //     32      4
		long    biClrImportant;         //     36      4
	} BITMAPINFOHEADER;                 // Total size: 40
	
	
	BITMAPFILEHEADER        bmfh;
	BITMAPINFOHEADER        bmih;


	FILE * f;
	char byte;
	long k;
	long x, y;

    // BITMAPFILEHEADER
	bmfh.bfType = 0x4D42;         // 'BM'
	bmfh.bfReserved1 = 0;         // Reserved, always 0
	bmfh.bfReserved2 = 0;         // Reserved, always 0
	// bfOffBits = Byte offset from BITMAPFILEHEADER to the actual bitmap data
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
                   
	bmfh.bfSize = bmfh.bfOffBits; // File size, will be written below

	// BITMAPINFOHEADER
	bmih.biSize = sizeof(BITMAPINFOHEADER);       // Size of BITMAPINFOHEADER
	bmih.biWidth = fnc->getCountX();
	bmih.biHeight = fnc->getCountY();
	bmih.biPlanes = 1;				// Number of planes for the target device
	bmih.biBitCount = 24;			// Number of bits per pixel (1, 4, 8, 24)

	bmih.biSizeImage = fnc->getCountX()*fnc->getCountY();  // Size of image in bytes
	bmih.biCompression = 0;
    bmih.biSizeImage *= 3;              // 3 bytes needed for each pixel
    
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = 0;			          // Number of color indexes in color
                                          // table actually used by the bitmap
	bmih.biClrImportant = 0;		      // All colors are important

	f = fopen(filename, "w+b");
	if (!f) {
		writelog(SURFIT_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}
  
	// Write BITMAPFILEHEADER and BITMAPINFOHEADER to file
	fwrite(&(bmfh.bfType), sizeof(short), 1, f);
	fwrite(&(bmfh.bfSize), sizeof(long), 1, f);
	fwrite(&(bmfh.bfReserved1), sizeof(short), 1, f);
	fwrite(&(bmfh.bfReserved2), sizeof(short), 1, f);
	fwrite(&(bmfh.bfOffBits), sizeof(long), 1, f);
	fflush(f);

	fwrite(&(bmih.biSize), sizeof(long), 1, f);
	fwrite(&(bmih.biWidth), sizeof(long), 1, f);
	fwrite(&(bmih.biHeight), sizeof(long), 1, f);
	fwrite(&(bmih.biPlanes), sizeof(short), 1, f);
	fwrite(&(bmih.biBitCount), sizeof(short), 1, f);
	fwrite(&(bmih.biCompression), sizeof(long), 1, f);
	fwrite(&(bmih.biSizeImage), sizeof(long), 1, f);
	fwrite(&(bmih.biXPelsPerMeter), sizeof(long), 1, f);
	fwrite(&(bmih.biYPelsPerMeter), sizeof(long), 1, f);
	fwrite(&(bmih.biClrUsed), sizeof(long), 1, f);
	fwrite(&(bmih.biClrImportant), sizeof(long), 1, f);
	fflush(f);

	//BMPBufferFlip(fnc->getCountX(), fnc->getCountY(), biBuffer);
	
	k = 0;
	byte = 0;
	long size = 0;
	int r,g,b;
	REAL z;
	char data;

	if (surfit_color_scale->is_default()) {
		REAL minz, maxz, step;
		fnc->getMinMaxZ(minz, maxz);
		step = stepFunc(minz, maxz, 100);
		minz = floor(minz/step)*step;
		maxz = floor(maxz/step)*step;
		surfit_color_scale->set(minz, maxz, step, DEFAULT_COLORS);
	}
	
	for (y = 0; y < fnc->getCountY(); y++) {
		for (x = 0; x < fnc->getCountX(); x++) {
			z = (*(fnc->coeff))(x + y*fnc->getCountX());

			surfit_color_scale->get_value(z, r, g, b);

			data = char(g);
			fwrite(&data, sizeof(char), 1, f);

			data = char(r);
			fwrite(&data, sizeof(char), 1, f);

			data = char(b);
			fwrite(&data, sizeof(char), 1, f);

			bmfh.bfSize+=3;
		}

		size = fnc->getCountX();
		data = char(0);
		while ((size % 4) != 0) {
			fwrite(&data, sizeof(char), 1, f);
			bmfh.bfSize++;
			size++;
		}
	}

	fseek(f, 0, SEEK_SET);

	fwrite(&(bmfh.bfType), sizeof(short), 1, f);
	fwrite(&(bmfh.bfSize), sizeof(long), 1, f);
	fwrite(&(bmfh.bfReserved1), sizeof(short), 1, f);
	fwrite(&(bmfh.bfReserved2), sizeof(short), 1, f);
	fwrite(&(bmfh.bfOffBits), sizeof(long), 1, f);
	fflush(f);

	fwrite(&(bmih.biSize), sizeof(long), 1, f);
	fwrite(&(bmih.biWidth), sizeof(long), 1, f);
	fwrite(&(bmih.biHeight), sizeof(long), 1, f);
	fwrite(&(bmih.biPlanes), sizeof(short), 1, f);
	fwrite(&(bmih.biBitCount), sizeof(short), 1, f);
	fwrite(&(bmih.biCompression), sizeof(long), 1, f);
	fwrite(&(bmih.biSizeImage), sizeof(long), 1, f);
	fwrite(&(bmih.biXPelsPerMeter), sizeof(long), 1, f);
	fwrite(&(bmih.biYPelsPerMeter), sizeof(long), 1, f);
	fwrite(&(bmih.biClrUsed), sizeof(long), 1, f);
	fwrite(&(bmih.biClrImportant), sizeof(long), 1, f);
	fflush(f);

	fclose(f);

	return true;


};


task * _func_to_task(const func * fnc) {
	
	REAL * Z_begin = (REAL*)malloc(fnc->coeff->size() * sizeof(REAL));
	
	if (!fnc->coeff) {
		writelog(SURFIT_ERROR,"convert_func_to_task : wrong func - no coeffs");
		return NULL;
	}

	Z_begin = (REAL*) memcpy(Z_begin, fnc->coeff->begin(), fnc->coeff->size() * sizeof(REAL));
	if (Z_begin == NULL) {
		writelog(SURFIT_ERROR,"Not enought memory to convert func to task");
		return NULL;
	}

	REAL * Z_end = Z_begin + fnc->coeff->size();

	REAL * X_begin = (REAL*)malloc(fnc->coeff->size() * sizeof(REAL));
	if (X_begin == NULL) {
		writelog(SURFIT_ERROR,"Not enought memory to convert func to task");
		free(Z_begin);
		return NULL;
	}
	REAL * X_end = X_begin + fnc->coeff->size();
	
	REAL * Y_begin = (REAL*)malloc(fnc->coeff->size() * sizeof(REAL));
	if (Y_begin == NULL) {
		writelog(SURFIT_ERROR,"Not enought memory to convert func to task");
		free(Z_begin);
		free(X_begin);
		return NULL;
	}
	REAL * Y_end = Y_begin + fnc->coeff->size();

	REAL * X_ptr = X_begin;
	REAL * Y_ptr = Y_begin;

	int i,j;
	for (j = 0; j < fnc->getCountY(); j++) {
		for (i = 0; i < fnc->getCountX(); i++) {
			fnc->getCoordNode(i,j,*X_ptr,*Y_ptr);
			X_ptr++;
			Y_ptr++;
		}
	}

	return new task(X_begin, X_end,
			Y_begin, Y_end,
			Z_begin, Z_end,
			fnc->getName());
};

//
//
// wavelets section
//
//

bool _func_decomp(func * fnc) {
	if (!fnc)
		return false;
	
	return fnc->decompose();
};

bool _func_auto_decomp(func * fnc, REAL eps) {
	if (!fnc)
		return false;

	return fnc->auto_decompose(eps);
};

bool _func_add_noise(func * fnc, REAL std) {
	if (!fnc)
		return false;

	return fnc->add_noise(std);
};

bool _func_recons(func * fnc) {
	if (!fnc)
		return false;

	return fnc->reconstruct();
};

bool _func_full_recons(func * fnc) {
	if (!fnc)
		return false;

	return fnc->full_reconstruct();
};


func * _func_project(func * fnc, grid * grd) {

	int size_x = grd->getCountX();
	int size_y = grd->getCountY();

	vec * coeff = new vec(size_x*size_y,0,0);  // do not fill this vector
	
	int func_size = fnc->coeff->size();
	int func_sizeX = fnc->getCountX();
	int func_sizeY = fnc->getCountY();

	if (fnc->getName())
		writelog(SURFIT_MESSAGE,"Projecting func \"%s\" (%d x %d) => (%d x %d)",fnc->getName(), func_sizeX, func_sizeY, size_x, size_y);
	else 
		writelog(SURFIT_MESSAGE,"Projecting func (%d x %d) => (%d x %d)", func_sizeX, func_sizeY, size_x, size_y);

	{

		REAL x, y;
		int I0, J0, I1, J1;
		REAL value;
		int i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = fnc->grd->stepX;
		REAL hY = fnc->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);
				
				grid * g = fnc->grd;
				I0 = (int)floor( (x - g->startX)/g->stepX );
				J0 = (int)floor( (y - g->startY)/g->stepY );

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), func_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), func_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), func_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), func_sizeY-1);

				fnc->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(fnc->coeff))(I0 + func_sizeX*J0);
				z1 = (*(fnc->coeff))(I1 + func_sizeX*J0);
				z2 = (*(fnc->coeff))(I1 + func_sizeX*J1);
				z3 = (*(fnc->coeff))(I0 + func_sizeX*J1);
				
				if (
					(z0 == fnc->undef_value) ||
					(z1 == fnc->undef_value) ||
					(z2 == fnc->undef_value) ||
					(z3 == fnc->undef_value) 
					) 
				{
					
					REAL sum = REAL(0);
					int cnt = 0;
					
					if (z0 != fnc->undef_value) {
						sum += z0;
						cnt++;
					}
					if (z1 != fnc->undef_value) {
						sum += z1;
						cnt++;
					}
					if (z2 != fnc->undef_value) {
						sum += z2;
						cnt++;
					}
					if (z3 != fnc->undef_value) {
						sum += z3;
						cnt++;
					}
					
					if (cnt == 0) {
						(*coeff)(i + j*size_x) = fnc->undef_value;
						continue;
					}

					REAL mean_z = sum/REAL(cnt);
					if (z0 == fnc->undef_value)
						z0 = mean_z;
					if (z1 == fnc->undef_value)
						z1 = mean_z;
					if (z2 == fnc->undef_value)
						z2 = mean_z;
					if (z3 == fnc->undef_value)
						z3 = mean_z;
					
				}
				
				delta_x = x - x0;
				delta_y = y - y0;
				
				// первый шаг линейной интерпол€ции
				REAL z11 = (z2-z1)*delta_y/hY+z1;
				REAL z22 = (z3-z0)*delta_y/hY+z0;
				
				// второй шаг линейной интерпол€ции
				REAL res = (z11-z22)*delta_x/hX+z22;
								
				(*coeff)(i + j*size_x) = res;
				
								
			}
		}
	}
	
	grid * new_grd = new grid(grd);
	func * res = new func(coeff, new_grd, fnc->getName());
	res->undef_value = fnc->undef_value;
	return res;
};

func * _func_project(func * fnc, grid * grd, grid_line * fault_grd_line) {

	if (!fault_grd_line)
		return _func_project(fnc, grd);

	int size_x = grd->getCountX();
	int size_y = grd->getCountY();

	vec * coeff = new vec(size_x*size_y,0,0);  // do not fill this vector
	
	int func_size = fnc->coeff->size();
	int func_sizeX = fnc->getCountX();
	int func_sizeY = fnc->getCountY();

	if (fnc->getName())
		writelog(SURFIT_MESSAGE,"Projecting func \"%s\" (%d x %d) => (%d x %d)",fnc->getName(), func_sizeX, func_sizeY, size_x, size_y);
	else 
		writelog(SURFIT_MESSAGE,"Projecting func (%d x %d) => (%d x %d)", func_sizeX, func_sizeY, size_x, size_y);

	{

		REAL x, y;
		int I0, J0, I1, J1;
		REAL value;
		int i,j;
		REAL z0, z1, z2, z3;
		REAL x0, y0;
		REAL delta_x, delta_y;
		REAL hX = fnc->grd->stepX;
		REAL hY = fnc->grd->stepY;
		
		for (j = 0; j < size_y; j++) {
			for (i = 0; i < size_x; i++) {
				value = 0;
				grd->getCoordNode(i, j, x, y);

				x -= grd->stepX/REAL(2);
				y -= grd->stepY/REAL(2);
				
				grid * g = fnc->grd;
				I0 = (int)floor( (x - g->startX)/g->stepX );
				J0 = (int)floor( (y - g->startY)/g->stepY );

				I1 = I0+1;
				J1 = J0+1;

				I0 = MIN(MAX( 0, I0 ), func_sizeX-1);
				I1 = MIN(MAX( 0, I1 ), func_sizeX-1);
				J0 = MIN(MAX( 0, J0 ), func_sizeY-1);
				J1 = MIN(MAX( 0, J1 ), func_sizeY-1);

				fnc->getCoordNode(I0, J0, x0, y0);
				
				z0 = (*(fnc->coeff))(I0 + func_sizeX*J0);
				z1 = (*(fnc->coeff))(I1 + func_sizeX*J0);
				z2 = (*(fnc->coeff))(I1 + func_sizeX*J1);
				z3 = (*(fnc->coeff))(I0 + func_sizeX*J1);
				
				if (
					(z0 == fnc->undef_value) &&
					(z1 == fnc->undef_value) &&
					(z2 == fnc->undef_value) &&
					(z3 == fnc->undef_value) 
				   )
				{
					(*coeff)(i + j*size_x) = fnc->undef_value;
				} else {
					
					if (
						(z0 == fnc->undef_value) ||
						(z1 == fnc->undef_value) ||
						(z2 == fnc->undef_value) ||
						(z3 == fnc->undef_value) 
						) 
					{
						
						REAL sum = REAL(0);
						int cnt = 0;
								
						if (z0 != fnc->undef_value) {
							sum += z0;
							cnt++;
						}
						if (z1 != fnc->undef_value) {
							sum += z1;
							cnt++;
						}
						if (z2 != fnc->undef_value) {
							sum += z2;
							cnt++;
						}
						if (z3 != fnc->undef_value) {
							sum += z3;
							cnt++;
						}

						REAL mean_z = sum/REAL(cnt);
						if (z0 == fnc->undef_value)
							z0 = mean_z;
						if (z1 == fnc->undef_value)
							z1 = mean_z;
						if (z2 == fnc->undef_value)
							z2 = mean_z;
						if (z3 == fnc->undef_value)
							z3 = mean_z;

					}
					
					delta_x = x - x0;
					delta_y = y - y0;

					if ( check_for_pair(fault_grd_line,
						                I1 + J0*func_sizeX, 
						                I1 + J1*func_sizeX) )
					{
						if (delta_y < fnc->grd->stepY/REAL(2))
							z1 = z2;
						else
							z2 = z1;
					}

					if ( check_for_pair(fault_grd_line,
						                I0 + J0*func_sizeX, 
						                I0 + J1*func_sizeX) )
					{
						if (delta_y < fnc->grd->stepY/REAL(2))
							z0 = z3;
						else
							z3 = z0;
					}

					// first step of linear interpolation
					REAL z11 = (z2-z1)*delta_y/hY+z1,
						 z22 = (z3-z0)*delta_y/hY+z0;

					if ( check_for_pair(fault_grd_line,
						                I0 + J0*func_sizeX,
										I1 + J0*func_sizeX)
						 ||
						 check_for_pair(fault_grd_line,
						                I0 + J1*func_sizeX,
										I1 + J1*func_sizeX)
										) 
					{
						if (delta_x < fnc->grd->stepX/REAL(2))
							(*coeff)(i + j*size_x) = z22;
						else
							(*coeff)(i + j*size_x) = z11;
					} else {
						
						// second step of linear interpolation
						REAL Res = (z11-z22)*delta_x/hX+z22;
						(*coeff)(i + j*size_x) = Res;
					}
				}
			}
		}
	}
	
	grid * new_grd = new grid(grd);
	func * res = new func(coeff, new_grd, fnc->getName());
	res->undef_value = fnc->undef_value;
	return res;
};

void _func_info(func * fnc) {
	if (!fnc)
		return;
	if (fnc->getName()) 
		writelog(SURFIT_MESSAGE,"func (%s) : size=(%d x %d)", fnc->getName(), fnc->getCountX(), fnc->getCountY());
	else 
		writelog(SURFIT_MESSAGE,"func noname : size=(%d x %d)", fnc->getCountX(), fnc->getCountY());
};

bool _func_resid(func * fnc, task * tsk, const char * filename) {
	if (!fnc)
		return false;
	if (!tsk)
		return false;

	writelog(SURFIT_MESSAGE, "Calcualting residuals...");

	FILE * f = fopen(filename, "w");

	if (!f) {
		writelog(SURFIT_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	int task_size = tsk->size();
	int cnt;
	REAL res;
	REAL x,y,z;

	REAL maxres = -FLT_MAX;

	for (cnt = 0; cnt < task_size; cnt++) {
		x = *(tsk->X_begin + cnt);
		y = *(tsk->Y_begin + cnt);
		z = *(tsk->Z_begin + cnt);
		res = fnc->getValue(x,y) - z;
		maxres = (REAL)MAX(fabs(res),maxres);
		fprintf(f,"%lf \t %lf \t %lf %lf\n",x,y,z,res);
	}
	
	fclose(f);
	writelog(SURFIT_MESSAGE,"max residual : %lf", maxres);

	return true;

};

REAL _func_D1(func * fnc) {

	int i,j;
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();

	REAL * ptr = fnc->coeff->begin();

	REAL v1, v2;

	REAL dx = 0;
	int dx_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			if ((v1 != fnc->undef_value) && (v2 != fnc->undef_value)) {
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
			if ((v1 != fnc->undef_value) && (v2 != fnc->undef_value)) {
				dy += (v2-v1)*(v2-v1);
				dy_cnt++;
			}
		}
	}

	dy /= REAL(dy_cnt);

	REAL h_x_2 = (fnc->grd->stepX)*(fnc->grd->stepX);
	REAL h_y_2 = (fnc->grd->stepY)*(fnc->grd->stepY);

	REAL res = dx/h_x_2 + dy/h_y_2;

	return res;

};

REAL _func_D2(func * fnc) {

	int i,j;
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();

	REAL * ptr = fnc->coeff->begin();

	REAL v1, v2, v3, v4;

	REAL dx2 = 0;
	int dx2_cnt = 0;
	for (i = 0; i < NN-3; i++) {
		for (j = 0; j < MM-1; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + (i+2) + j*NN);
			if ((v1 != fnc->undef_value) && 
				(v2 != fnc->undef_value) && 
				(v3 != fnc->undef_value)) {
				dx2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dx2_cnt++;
			}
		}
	}

	REAL dxdy = 0;
	int dxdy_cnt = 0;
	for (i = 0; i < NN-2; i++) {
		for (j = 0; j < MM-2; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + (i+1) + j*NN);
			v3 = *(ptr + i + (j+1)*NN);
			v4 = *(ptr + (i+1) + (j+1)*NN);
			if ((v1 != fnc->undef_value) && 
				(v2 != fnc->undef_value) && 
				(v3 != fnc->undef_value) && 
				(v4 != fnc->undef_value) ) {
				dxdy += (v4-v3-v2+v1)*(v4-v3-v2+v1);
				dxdy_cnt++;
			}
		}
	}

	REAL dy2 = 0;
	int dy2_cnt = 0;
	for (i = 0; i < NN-1; i++) {
		for (j = 0; j < MM-3; j++) {
			v1 = *(ptr + i + j*NN);
			v2 = *(ptr + i + (j+1)*NN);
			v3 = *(ptr + i + (j+2)*NN);
			if ((v1 != fnc->undef_value) && 
				(v2 != fnc->undef_value) && 
				(v3 != fnc->undef_value)) {
				dy2 += (v3-2*v2+v1)*(v3-2*v2+v1);
				dy2_cnt++;
			}
		}
	}

	REAL h_x_2 = (fnc->grd->stepX)*(fnc->grd->stepX);
	REAL h_y_2 = (fnc->grd->stepY)*(fnc->grd->stepY);
	writelog(SURFIT_DEBUG,"h_x_2 = %lf    h_y_2 = %lf",h_x_2, h_y_2);
	writelog(SURFIT_DEBUG,"dx2_cnt = %d dy2_cnt = %d dxdy_cnt = %d",dx2_cnt, dy2_cnt, dxdy_cnt);
	writelog(SURFIT_DEBUG,"dx2  = %lf",dx2);
	writelog(SURFIT_DEBUG,"dy2  = %lf",dy2);
	writelog(SURFIT_DEBUG,"dxdy = %lf",dxdy);

	dx2 /= REAL(dx2_cnt);
	dxdy /= REAL(dxdy_cnt);
	dy2 /= REAL(dy2_cnt);

	REAL res = dx2/(h_x_2*h_x_2) + 2*dxdy/(h_x_2*h_y_2) + dy2/(h_y_2*h_y_2);

	return res;
};

func * _get_surfit_func() {
	return surfit_func;
};

void _set_surfit_func(func * fnc) {
	delete surfit_func;
	surfit_func = fnc;
};

void _add_surfit_funcs(func * fnc) {
	if (!fnc)
		return;
	surfit_funcs->push_back(fnc);
};

func * _func_gradient(func * fnc) {
	
	int NN = fnc->getCountX();
	int MM = fnc->getCountY();

	bool first_x, second_x;
	bool first_y, second_y;

	vec * coeff = new vec(NN*MM);

	int i, j, pos, pos1;
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
			REAL pos_val = (*(fnc->coeff))(pos);
			if (pos_val == fnc->undef_value) {
				(*(coeff))(pos) = fnc->undef_value;
				continue;
			}
			REAL pos1_val;

			val = REAL(0);

			if (first_x) {
				pos1 = (i+1) + j*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_x) {
				pos1 = (i-1) + j*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			if (first_y) {
				pos1 = (i) + (j+1)*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos_val - pos1_val;
			}

			if (second_y) {
				pos1 = i + (j-1)*NN;
				pos1_val = (*(fnc->coeff))(pos1);
				if (pos1_val == fnc->undef_value) {
					(*(coeff))(pos) = fnc->undef_value;
					continue;
				}
				val += pos1_val - pos_val;
			}

			(*(coeff))(pos) = val;
			
		}
	}

	grid * grd = new grid(fnc->grd);
	func * res = new func(coeff, grd, fnc->getName());
	return res;

};

wfunc * _func_to_wfunc(func * fnc, REAL weight) {
	if (!fnc)
		return false;
	wfunc * res = new wfunc(new vec(*(fnc->coeff)), new grid(fnc->grd), weight, fnc->getName());
	return res;
};

}; // namespace surfit;



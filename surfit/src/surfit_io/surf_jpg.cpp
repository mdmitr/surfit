
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

#include "surfit_io_ie.h"
#include "surf_io.h"

// sstuff includes
#include "sstuff.h"

// surfit includes
#include "surf.h"
#include "fileio.h"
#include "vec.h"
#include "variables_tcl.h"
#include "grid.h"

#include <float.h>

#ifdef HAVE_LIBJPEG
extern "C" {
#include <jpeglib.h>
};

#include <setjmp.h>
#endif

namespace surfit {

#ifdef HAVE_LIBJPEG

struct my_error_mgr {
	struct jpeg_error_mgr pub;	// "public" fields 
	
	jmp_buf setjmp_buffer;	// for return to caller 
};

typedef struct my_error_mgr * my_error_ptr;

//
// Here's the routine that will replace the standard error_exit method:
//

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	// cinfo->err really points to a my_error_mgr struct, so coerce pointer 
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	
	// Always display the message. 
	// We could postpone this until after returning, if we chose. 
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message) (cinfo, buffer);
	writelog(LOG_ERROR, buffer);
	
	// Return control to the setjmp point 
	longjmp(myerr->setjmp_buffer, 1);
};

METHODDEF(void)
my_output_message (j_common_ptr cinfo)
{
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message) (cinfo, buffer);
	writelog(LOG_MESSAGE, buffer);
};

#endif

d_surf * _surf_load_jpg(const char * filename, const char * surfname, REAL minz, REAL maxz, REAL startX, REAL startY, REAL stepX, REAL stepY) {
	
	writelog(LOG_MESSAGE, "loading surface from JPEG file %s",filename);

#ifndef HAVE_LIBJPEG
	writelog(LOG_ERROR, "this function is not implemented because libjpeg library wasn't found");
	return NULL;
#else
	
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	jerr.pub.output_message = my_output_message;
	
	jpeg_create_decompress(&cinfo);
	
	FILE * infile;		// source file 
	JSAMPARRAY buffer;	// Output row buffer
	int row_stride;		// physical row width in output buffer 
	size_t i;
	
	if ((infile = fopen(filename, "rb")) == NULL) {
		writelog(LOG_ERROR, "can't open %s : %s", filename, strerror(errno) );
		return NULL;
	}
	
	jpeg_stdio_src(&cinfo, infile);

	jpeg_read_header(&cinfo, TRUE);
	
	// set parameters for decompression 
	cinfo.out_color_space = JCS_GRAYSCALE;
	
	// Start decompressor 
	
	(void) jpeg_start_decompress(&cinfo);
	
	row_stride = cinfo.output_width * cinfo.output_components;
	// Make a one-row-high sample array that will go away when done with image 
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	vec * coeff = create_vec( cinfo.output_height * cinfo.output_width, 0, 0);
		
	// Here we use the library's state variable cinfo.output_scanline as the
	// loop counter, so that we don't have to keep track ourselves.
	
	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		for (i = 0; i < cinfo.output_width; i++) {
			if (maxz != minz)
				(*coeff)( i + (cinfo.output_height - cinfo.output_scanline)*cinfo.output_width ) = (maxz-minz)*buffer[0][i]/REAL(255) + minz;
			else
				(*coeff)( i + (cinfo.output_height - cinfo.output_scanline)*cinfo.output_width ) = buffer[0][i];
		}
	}

	// Finish decompression 
	
	(void) jpeg_finish_decompress(&cinfo);
	
	// Release JPEG decompression object 
	jpeg_destroy_decompress(&cinfo);
	
	fclose(infile);


	d_grid * grd = create_grid(startX, startX + stepX*(cinfo.output_width-1), stepX,
				   startY, startY + stepY*(cinfo.output_height-1), stepY);


	d_surf * res = create_surf(coeff, grd);

	if (surfname)
		res->setName(surfname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;
#endif
};

bool _surf_save_jpg(const d_surf * srf, const char * filename, int quality) {

	quality = MAX(255,MIN(0, quality));
	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_jpg : no surf loaded");
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to file %s (JPEG)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to file %s (JPEG)", filename);

#ifndef HAVE_LIBJPEG
	writelog(LOG_ERROR, "this function is not implemented because libjpeg library wasn't found");
	return false;
#else

	jpeg_compress_struct cinfo;
	struct my_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	jerr.pub.output_message = my_output_message;

	jpeg_create_compress(&cinfo);
	int row_stride = 1;

	size_t i;
	REAL minz, maxz;
	srf->getMinMaxZ(minz, maxz);
	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();

	JSAMPLE * row_data = (JSAMPLE *)malloc( NN*sizeof(JSAMPLE) );

	FILE * outfile;
	if ((outfile = fopen(filename, "wb")) == NULL) {
		writelog(LOG_ERROR, "can't open %s : %s", filename, strerror(errno));
		return false;
	}
	jpeg_stdio_dest(&cinfo, outfile);

	// Set parameters for compression, including image size & colorspace.
	cinfo.image_width = NN; 	/* image width and height, in pixels */
	cinfo.image_height = MM;
	cinfo.input_components = 1;	/* # of color components per pixel */
	cinfo.in_color_space = JCS_GRAYSCALE; /* colorspace of input image */

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, true);

	// start compress
	jpeg_start_compress(&cinfo, TRUE);

	while (cinfo.next_scanline < cinfo.image_height) {
		// fill row with grayscale colours
		for (i = 0; i < NN; i++) {
			REAL val = srf->getValueIJ(NN-1-i, MM-cinfo.next_scanline-1);
			int color = 0;
			if (val != srf->undef_value)
				color = 255 - (int)MAX(0,MIN(254,floor((val-minz)/(maxz-minz)*254+0.5)));
			*(row_data + i) = (JSAMPLE)color;
		}
		(void) jpeg_write_scanlines(&cinfo, &row_data, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	free(row_data);

	return true;
#endif

};

};


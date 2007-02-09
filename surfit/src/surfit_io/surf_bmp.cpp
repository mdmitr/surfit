
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

#include "EasyBmp/EasyBMP.h"

namespace surfit {

d_surf * _surf_load_bmp(const char * filename, const char * surfname, REAL minz, REAL maxz, REAL startX, REAL startY, REAL stepX, REAL stepY) {
	
	writelog(LOG_MESSAGE, "loading surface from BMP file %s",filename);

	BMP bmp;
	if (bmp.ReadFromFile(filename) == false) {
		writelog(LOG_ERROR,"Error loading surface from bitmap!");
		return NULL;
	}

	size_t NN = bmp.TellWidth();
	size_t MM = bmp.TellHeight();

	extvec * coeff = create_extvec( NN*MM, 0, 0, 0);

	size_t i,j;
	double gray_color;
	double alpha;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			gray_color = bmp(i,j)->Red * 0.299 +
				     bmp(i,j)->Green * 0.587 +
				     bmp(i,j)->Blue * 0.114;
			alpha = bmp(i,j)->Alpha;
			if (alpha == 255)
				(*coeff)(i + (MM-1-j)*NN) = undef_value;
			else {
				if (minz != maxz)
					(*coeff)(i + (MM-1-j)*NN) = (maxz-minz)*gray_color/REAL(255) + minz;
				else
					(*coeff)(i + (MM-1-j)*NN) = gray_color;
			}
		}
	}

	d_grid * grd = create_grid(startX, startX + stepX*(NN-1), stepX,
				   startY, startY + stepY*(MM-1), stepY);


	d_surf * res = create_surf(coeff, grd);

	if (surfname)
		res->setName(surfname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;

};

bool _surf_save_bmp(const d_surf * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_png : no surf loaded");
		return false;
	}

	if (srf->getName())
		writelog(LOG_MESSAGE,"Saving surf %s to file %s (BMP)", srf->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"Saving surf (noname) to file %s (BMP)", filename);

	size_t NN = srf->getCountX();
	size_t MM = srf->getCountY();
	
	BMP res;
	res.SetSize(NN,MM);
	res.SetBitDepth(24);
	REAL minz, maxz;
	srf->getMinMaxZ(minz, maxz);

	size_t i, j;
	double gray_color;
	for (j = 0; j < MM; j++) {
		for (i = 0; i < NN; i++) {
			REAL value = srf->getValueIJ(i,MM-j-1);
			if (value == srf->undef_value) {
				res(i,j)->Red = 0;
				res(i,j)->Green = 0;
				res(i,j)->Blue = 0;
				res(i,j)->Alpha = 0;
			} else {
				gray_color = MAX(0,MIN(255,floor((value - minz)/(maxz-minz)*255 + 0.5)));
				res(i,j)->Red = (ebmpBYTE)gray_color;
				res(i,j)->Green = (ebmpBYTE)gray_color;
				res(i,j)->Blue = (ebmpBYTE)gray_color;
				res(i,j)->Alpha = 255;
			}

		}
	}
	

	res.WriteToFile(filename);

	return true;

};

};


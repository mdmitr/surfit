
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

#ifdef HAVE_GL_WORKS

#include "draw_object.h"

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include "windows.h"
#endif
#include <GL/gl.h>

namespace surfit {

draw_object::draw_object(const char *name, const char *type, const char *filename, int listNo,
			 REAL iminx, REAL imaxx, 
			 REAL iminy, REAL imaxy, 
			 REAL iminz, REAL imaxz) {
	object_name = NULL;
	if (name)
	    object_name = strdup(name);
	
	object_type = NULL;
	if (type)
	    object_type = strdup(type);
	    
	object_filename = NULL;
	if (filename)
    	    object_filename = strdup(filename);

	minx = iminx;
	maxx = imaxx;
	miny = iminy;
	maxy = imaxy;
	minz = iminz;
	maxz = imaxz;

	listNumber = listNo;
};

draw_object::~draw_object() {
	free(object_name);
	free(object_type);
	free(object_filename);
	if (glIsList(listNumber))
		glDeleteLists(listNumber,1);

};

void draw_object::callList() {
	if (glIsList(listNumber))
		glCallList(listNumber);
};

void draw_object::setListNumber(int number) {
	if (glIsList(number)) 
		listNumber = number;
};

int draw_object::getListNumber() const {
	return listNumber;
};

const char * draw_object::getName() const {
	return object_name;
};

const char * draw_object::getType() const {
	return object_type;
};

const char * draw_object::getFileName() const {
	return object_filename;
};

void create_draw_object(const char *name, 
			const char *type, 
			const char *filename, 
			int listNo,
			REAL iminx, 
			REAL imaxx, 
			REAL iminy, 
			REAL imaxy, 
			REAL iminz, 
			REAL imaxz) 
{
	draw_object * obj = new draw_object(name, type, filename,
		listNo, iminx, imaxx, iminy, imaxy, iminz, imaxz);

	draw_vector.push_back(obj);
};

}; // namespace surfit;

#endif




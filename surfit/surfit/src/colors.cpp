
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
#include "colors.h"

#include <string.h>

namespace surfit {

int bg_color_red;
int bg_color_green;
int bg_color_blue;
int bg_color_alpha;

#ifdef HAVE_GL_WORKS

bool set_colors(const char * color_name, 
		int & color_red, int & color_green, int & color_blue, int & color_alpha) {

	char * color = (char*) malloc(strlen(color_name)+1);

	strcpy(color,color_name);

	if (strcmp(color,"white")==0) {
		color_red =   255;
		color_green = 255;
		color_blue =  255;
		free(color);
		return true;
	}
		
	if (strcmp(color,"cyan")==0) {
		color_red =   0;
		color_green = 255;
		color_blue =  255;
		free(color);
		return true;
	}
		
	if (strcmp(color,"magenta")==0) {
		color_red =   255;
		color_green = 0;
		color_blue =  255;
		free(color);
		return true;
	}
	
	if (strcmp(color,"yellow")==0) {
		color_red =   255;
		color_green = 255;
		color_blue =  0;
		free(color);
		return true;
	}

	if (strcmp(color,"lblue")==0) {
		color_red = 0;
		color_green = 0;
		color_blue = 255;
		free(color);
		return true;
	}
	
	if (strcmp(color,"blue")==0) {
		color_red = 0;
		color_green = 0;
		color_blue = 128;
		free(color);
		return true;
	}

	if (strcmp(color,"lgreen")==0) {
		color_red =   0;
		color_green = 255;
		color_blue =  0;
		free(color);
		return true;
	}

	if (strcmp(color,"green")==0) {
		color_red =   0;
		color_green = 128;
		color_blue =  0;
		free(color);
		return true;
	}

	if (strcmp(color,"red")==0) {
		color_red =   255;
		color_green = 0;
		color_blue =  0;
		free(color);
		return true;
	}
	
	if (strcmp(color,"gray")==0) {
		color_red =   192;
		color_green = 192;
		color_blue =  192;
		free(color);
		return true;
	}
	
	if (strcmp(color,"black")==0) {
		color_red =   0;
		color_green = 0;
		color_blue =  0;
		free(color);
		return true;
	}


	delete color;
	return false;
};


void bg_color(const char * color_name) {
	set_colors(color_name, 
		   bg_color_red, 
		   bg_color_green, 
		   bg_color_blue, 
		   bg_color_alpha);
};

int get_bg_color_red()		{ return bg_color_red; };
int get_bg_color_green()	{ return bg_color_green; };
int get_bg_color_blue()		{ return bg_color_blue; };
int get_bg_color_alpha()	{ return bg_color_alpha; };

#endif

}; // namespace surfit



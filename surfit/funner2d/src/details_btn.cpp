
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

#include "details_btn.h"
#include <stdio.h>
#include <string.h>

#include <FL/Fl_Widget.H>

details_btn::details_btn(int x, int y, int w, int h, int idetail_number) 
: Fl_Light_Button(x,y,w,h) 
{
	selection_color(FL_GREEN);
	align(FL_ALIGN_CENTER);
	type(FL_RADIO_BUTTON);
	detail_number = idetail_number;
	if (detail_number == 0) {
		label("approximation");
	} else {
		char name[128];
		sprintf(name,"detail %d",detail_number);
		label(strdup(name));
	};
}

details_btn::~details_btn() 
{
}

int details_btn::get_detail_number() const {
	return detail_number;
}



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

#include <FL/Fl.H>
#include "funner2d_mainwnd.h"
#include "gl_view.h"

int main(int argc, char **argv) {

	funner2d_wind * w = NULL;
	if (argc > 1)
		w = new funner2d_wind(argv[0], argv[1]);
	else 
		w = new funner2d_wind(argv[0]);
	
	w->show(1, argv);
	int res = Fl::run();

	delete w;
	return res;
};


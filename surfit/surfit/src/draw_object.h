
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

#ifdef HAVE_GL_WORKS

#ifndef __surfit_gl__draw_object__
#define __surfit_gl__draw_object__

#include <vector>

using namespace std;

namespace surfit {

class draw_object;

extern SURFIT_EXPORT vector<draw_object*> draw_vector;

/*! \class draw_object
    \brief object to draw
*/
class SURFIT_EXPORT draw_object {
public:

	//! constructor
	draw_object(const char *name, const char *type, const char *filename, int listNo,
		    REAL iminx, REAL imaxx, 
		    REAL iminy, REAL imaxy, 
		    REAL iminz, REAL imaxz);

	//! destructor
	~draw_object();

	//! calls glCallList(listNumber)
	void callList();

	//! sets listNumber
	void setListNumber(int number);

	//! returns listNumber
	int getListNumber() const;

	//! returns object name
	const char * getName() const;

	//! returns object type
	const char * getType() const;

	//! returns object filename
	const char * getFileName() const;

	//! minimum X-coordinate for object
	REAL minx;
	//! maximum X-coordinate for object
	REAL maxx;
	//! minimum Y-coordinate for object
	REAL miny;
	//! maximum Y-coordinate for object
	REAL maxy;
	//! minimum Z-coordinate for object
	REAL minz;
	//! maximum Z-coordinate for object
	REAL maxz;

protected:

	//! name of the object
	char * object_name;
	//! type of the object
	char * object_type;
	//! filename fo the object
	char * object_filename;
	//! openGL list number 
	int listNumber;

};

SURFIT_EXPORT 
void create_draw_object(const char *name, 
			const char *type, 
			const char *filename, 
			int listNo,
			REAL iminx, REAL imaxx, 
			REAL iminy, REAL imaxy, 
			REAL iminz, REAL imaxz);

}; // namespace surfit;

#endif

#endif


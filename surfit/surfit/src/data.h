
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

#ifndef __surfit_data_included__
#define __surfit_data_included__

namespace surfit {

/*! \class data
    \brief parent class for all kinds of data, using by surfit

  Please follow link 
  \htmlonly
  <a href="../../html/cmofs.html">CMOFS</a>
  \endhtmlonly 
  for detailed description of the method.

*/
class SURFIT_EXPORT data {
public:

	//! constructor
	data();

	//! destructor
	virtual ~data();
	
	//! sets priority for this kind of data (priority number specifies position in functionals sequence)
	virtual void set_priority(int prior);

	//! returns priority number
	virtual int get_priority() const;

	//! sets object name to newname 
	void setName(const char * newname);

	//! returns object name 
	const char * getName() const;

	//! if object have bounds, then fill them!
	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const = 0;

	//! if object have vertical bounds, then fill them!
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const = 0;

protected:

	//! priority number specifies position in functionals sequence
	int priority;
	//! object name
	char * name;

};

}; // namespace surfit;

#endif


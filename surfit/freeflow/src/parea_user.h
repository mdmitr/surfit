
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

#ifndef __flow_parea_user_included__
#define __flow_parea_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class parea;

/*! \ingroup flow_data_variables
    \var flow_parea
    \brief \ref area with a "production" constant value, distributed on the area
*/
extern FLOW_EXPORT parea * flow_parea;

/*! \ingroup flow_variables_collections
    \var std::vector<area *>  * flow_pareas;
    \brief collection of \ref parea objects (see \ref flow_parea)
*/
extern FLOW_EXPORT std::vector<parea *>  * flow_pareas;

/*! \class parea_user
    \brief class for data usage in solving algorithm
*/
class FLOW_EXPORT parea_user : public user {
public:

	//! constructor
	parea_user();

	//! destructor
	~parea_user();
	
	virtual int max_priority();
	virtual void init();
	virtual void prepare();
	virtual void begin();
	virtual void stage1(int priority);
	virtual void stage2(int priority);
	virtual void stage3(int priority);
	virtual void stage4(int priority);
	virtual void stage5(int priority);
	virtual void finish();
	virtual void release();

};

}; // namespace surfit;

#endif


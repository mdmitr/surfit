
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

#ifndef __flow_pcntr_user_included__
#define __flow_pcntr_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class pcntr;

/*! \ingroup flow_data_variables
    \var flow_pcntr
    \brief line with "production" values (\ref pcntr)
*/
extern FLOW_EXPORT pcntr * flow_pcntr;

/*! \ingroup flow_variables_collections
    \var std::vector<cntr *> * flow_pcntrs;
    \brief collection of \ref pcntr objects (see \ref flow_pcntr)
*/
extern FLOW_EXPORT std::vector<pcntr *> * flow_pcntrs;


/*! \class pcntr_user
    \brief class for data usage in solving algorithm
*/
class FLOW_EXPORT pcntr_user : public user {
public:

	//! constructor
	pcntr_user();

	//! destructor
	~pcntr_user();
	
	int max_priority();
	void init();
	void prepare();
	void begin();
	void stage1(int priority);
	void stage2(int priority);
	void stage3(int priority);
	void stage4(int priority);
	void stage5(int priority);
	void finish();
	void release();

};

}; // namespace surfit;

#endif


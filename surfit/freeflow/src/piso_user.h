
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

#ifndef __flow_piso_user_included__
#define __flow_piso_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class piso;

/*! \ingroup flow_data_variables
    \var flow_piso
    \brief line with "production" values (\ref piso)
*/
extern FLOW_EXPORT piso * flow_piso;

/*! \ingroup flow_variables_collections
    \var std::vector<iso *> * flow_pisos;
    \brief collection of \ref piso objects (see \ref flow_piso)
*/
extern FLOW_EXPORT std::vector<piso *> * flow_pisos;

/*! \class piso_user
    \brief class for data usage in solving algorithm
*/
class FLOW_EXPORT piso_user : public user {
public:

	piso_user();
	~piso_user();
	
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


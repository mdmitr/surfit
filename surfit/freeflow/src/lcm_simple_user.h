
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

#ifndef __flow_lcm_simple_user_included__
#define __flow_lcm_simple_user_included__

#include "user.h"

namespace surfit {

class lcm_simple_user;

/*! \ingroup flow_data_variables
    \var flow_lcm_simple
    \brief law of conservation of mass for homogeneous formation 
    (constants for formation permeability, thick and liquid viscosity) 
    and stationary filtration.
*/
extern FLOW_EXPORT lcm_simple * flow_lcm_simple;

/*! \class lcm_simple_user
    \brief interface class for making equations from \ref lcm_simple_user
*/
class FLOW_EXPORT lcm_simple_user : public user, public modifier1 {
public:

	//! constructor
	lcm_simple_user();

	//! destructor
	~lcm_simple_user();
	
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

	virtual vec * get_weights() const;
	virtual intvec * get_weights_cnt() const;
	virtual void remove_weights();
	virtual void remove_weights_cnt();

};

}; // namespace surfit;

#endif


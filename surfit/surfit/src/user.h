
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

#ifndef __surfit_user_included__
#define __surfit_user_included__

namespace surfit {

class vec;
class intvec;

/*! \class binman
    \brief parent class for all garbages
*/
class SURFIT_EXPORT binman {
public:
	binman() {};
	virtual ~binman();
};

/*! \class modifier1
    \brief enables to modify functional matrix with some diagonal matrix
*/
class SURFIT_EXPORT modifier1 {
public:
	//! returns numerators for diagonal elements
	virtual vec * get_weights() const = 0;
	//! returns denumerators for diagonal elements
	virtual intvec * get_weights_cnt() const = 0;
	//! frees memory fo numerators
	virtual void remove_weights() = 0;
	//! frees memory fo denumerators
	virtual void remove_weights_cnt() = 0;
};

/*! \class user
    \brief interface class for making equations from different \ref data
*/
class SURFIT_EXPORT user {
public:

	//! constructor
	user(const char * iname);

	//! destructor
	~user();
	
	//! sets object name to newname 
	void setName(const char * newname);

	//! returns object name 
	const char * getName() const;

	//! interface for user. Must print information about data and return max_priority
	virtual int max_priority() = 0;

	//! inits some variables
	virtual void init() = 0;

	//! interface for user. Makes some prepares for user minimizing
	virtual void prepare() = 0;

	//! The very first stage.
	virtual void begin() = 0;

	//! interface for user. Makes first stage.
	virtual void stage1(int priority) = 0;
	//! interface for user. Makes second stage.
	virtual void stage2(int priority) = 0;
	//! interface for user. Makes third stage.
	virtual void stage3(int priority) = 0;
	//! interface for user. Makes fourth stage.
	virtual void stage4(int priority) = 0;
	//! interface for user. Makes fifth stage.
	virtual void stage5(int priority) = 0;
	//! interface for user. Makes some finish operations.
	virtual void finish() = 0;

	//! interface for user. Frees the memory
	virtual void release() = 0;

protected:

	//! object name
	char * name;

};

}; // namespace surfit;

#endif


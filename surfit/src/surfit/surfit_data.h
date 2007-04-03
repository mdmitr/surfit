
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "fileio.h"
#include "interp.h"

#include <string.h>
#include <vector>

#include <typeinfo>

namespace surfit {

/*! \class data
    \brief parent class for all kinds of data, using by surfit
*/
class SURFIT_EXPORT data {
protected:
	//! constructor
	data(const char * itype);
	//! destructor
	virtual ~data();
	
public:
	//! sets object name to newname 
	void setName(const char * newname);

	//! returns object name 
	const char * getName() const;

	//! return unique identificator
	int getId() const;

	//! sets object type to newtype
	void setType(const char * newtypename);

	//! returns object type
	const char * getType() const;

	//! if object have bounds, then fills them
	virtual bool bounds(REAL & minx, REAL & maxx, REAL & miny, REAL & maxy) const = 0;

	//! if object have vertical bounds, then fills them
	virtual bool getMinMaxZ(REAL & minz, REAL & maxz) const = 0;

	//! removes data object and all depend functionals 
	virtual void release();
	//! removes data object from memory
	virtual void release_private();

protected:

	//! object name
	char * name;

	//! object type
	char * type;

	//! object id
	int id;

};

/*! \class binman
    \brief parent class for all garbages
*/
class SURFIT_EXPORT binman {
public:
	binman() {};
	virtual ~binman() {};
};

template <class T, class iter>
T * get_element(const char * pos, iter begin_T, iter end_T) {

	char buf[1024];
	int size = end_T-begin_T;
	iter it;
	if (size == 0)
		goto bad_element;
	if (pos == NULL)
		goto bad_element;
	if ( strlen(pos) == 1 ) { // probably number
		switch (*pos) {
		case '0' : 
			{
				if (size <= 0)
					goto bad_element;
				return *(begin_T);
			}
		case '1' :
			{
				if (size <= 1)
					goto bad_element;
				return *(begin_T+1);
			}
		case '2' :
			{
				if (size <= 2)
					goto bad_element;
				return *(begin_T+2);
			}
		case '3' :
			{
				if (size <= 3)
					goto bad_element;
				return *(begin_T+3);
			}
		case '4' :
			{
				if (size <= 4)
					goto bad_element;
				return *(begin_T+4);
			}
		case '5' :
			{
				if (size <= 5)
					goto bad_element;
				return *(begin_T+5);
			}
		case '6' :
			{
				if (size <= 6)
					goto bad_element;
				return *(begin_T+6);
			}
		case '7' :
			{
				if (size <= 7)
					goto bad_element;
				return *(begin_T+7);
			}
		case '8' :
			{
				if (size <= 8)
					goto bad_element;
				return *(begin_T+8);
			}
		case '9' :
			{
				if (size <= 9)
					goto bad_element;
				return *(begin_T+9);
			}
			
		}
	}
	if ( strlen(pos) > 1 ) { // probably number
		int number = atoi(pos);
		if (number != 0) {
			sprintf(buf,"%d", number);
			if (strlen(buf) == strlen(pos)) {
				if ((number < size) && (number >= 0))
					return *(begin_T+number);
				goto bad_element;
			}
		}
	}
	
	// pos is a name
	for (it = begin_T; it != end_T; it++) {
		if (*it) {
			if ( (*it)->getName() ) {
				if ( StringMatch( pos, (*it)->getName() ) ) 
					return *it;
			}
		}
	}
	
bad_element:

	writelog(LOG_ERROR,"%s (%s) : bad element requested", typeid( T ).name(),pos);
	return NULL;
};

template <class T, class iter>
iter get_iterator(const char * pos, iter begin_T, iter end_T) {
	
	char buf[1024];
	int size = end_T-begin_T;
	iter it;
	if (size == 0)
		goto bad_iterator;
	if (pos == NULL)
		goto bad_iterator;
	if ( strlen(pos) == 1 ) { // probably number
		switch (*pos) {
		case '0' : 
			{
				if (size <= 0)
					goto bad_iterator;
				return (begin_T);
			}
		case '1' :
			{
				if (size <= 1)
					goto bad_iterator;
				return (begin_T+1);
			}
		case '2' :
			{
				if (size <= 2)
					goto bad_iterator;
				return (begin_T+2);
			}
		case '3' :
			{
				if (size <= 3)
					goto bad_iterator;
				return (begin_T+3);
			}
		case '4' :
			{
				if (size <= 4)
					goto bad_iterator;
				return (begin_T+4);
			}
		case '5' :
			{
				if (size <= 5)
					goto bad_iterator;
				return (begin_T+5);
			}
		case '6' :
			{
				if (size <= 6)
					goto bad_iterator;
				return (begin_T+6);
			}
		case '7' :
			{
				if (size <= 7)
					goto bad_iterator;
				return (begin_T+7);
			}
		case '8' :
			{
				if (size <= 8)
					goto bad_iterator;
				return (begin_T+8);
			}
		case '9' :
			{
				if (size <= 9)
					goto bad_iterator;
				return (begin_T+9);
			}
			
		}
	}
	if ( strlen(pos) > 1 ) { // probably number
		int number = atoi(pos);
		if (number != 0) {
			sprintf(buf,"%d", number);
			if (strlen(buf) == strlen(pos)) {
				if ((number < size) && (number >= 0))
					return (begin_T+number);
				goto bad_iterator;
			}
		}
	}
	
	// pos is a name
	for (it = begin_T; it != end_T; it++) {
		if (*it) {
			if ( (*it)->getName() ) {
				if ( StringMatch( pos, (*it)->getName() )  )
					return it;
			}
		}
	}
	
bad_iterator:

	writelog(LOG_ERROR,"%s : bad element requested", typeid( T ).name());
	return end_T;
};

}; // namespace surfit;

#endif


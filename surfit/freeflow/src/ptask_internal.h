
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

#ifndef __surfit__ptask_internal__
#define __surfit__ptask_internal__

#include <vector>

namespace surfit {

class vec;
class grid;
class datafile;
class ptask;

////////////////////////////////////////////////
////////////////////////////////////////////////
//                ptask io                   //
////////////////////////////////////////////////
////////////////////////////////////////////////

///////////////
// load

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn ptask * _ptask_read(const char * filename, const char * ptaskname, int columns, int col1, int col2, int col3, const char * mask, int grow_by);
    \brief reads ptask from formatted text file
    \return pointer to ptask class
    \param filename filename
    \param ptaskname ptaskname
    \param columns columns in text file
    \param col1 column number in text file for X coordinates
    \param col2 column number in text file for Y coordinates
    \param col3 column number in text file for Z coordinates
    \param mask mask for scanf
    \param grow_by vector's grow factor
*/
ptask * _ptask_read(const char * filename, const char * ptaskname, int columns, int col1, int col2, int col3, const char * mask, int grow_by);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn ptask * _ptask_load(const char * filename, const char * ptaskname, int mode);
    \brief reads ptask from ROFF file (see \ref datafile for details)
    \return pointer to ptask class
    \param filename filename
    \param ptaskname name
    \param mode rw_mode (0 = bin, 1 = asc)
*/
ptask * _ptask_load(const char * filename, const char * ptaskname, int mode);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn ptask * _ptask_load_df(datafile * df, const char * ptaskname);
    \brief reads ptask from \ref datafile
*/
ptask * _ptask_load_df(datafile * df, const char * ptaskname);

//////////////
// save

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn bool _ptask_write(ptask * ptsk, const char * filename, const char * mask);
    \brief saves ptask to formatted text file
    \param ptsk pointer to \ref ptask
    \param filename filename
    \param mask mask for printf
*/
bool _ptask_write(ptask * ptsk, const char * filename, const char * mask);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn bool _ptask_save(ptask * ptsk, const char * filename, int mode);
    \brief saves ptask to ROFF file (see \ref datafile for details)
    \param filename filename
    \param ptsk pointer to \ref ptask
    \param mode \ref rw_mode (0 = bin, 1 = asc)
*/
bool _ptask_save(ptask * ptsk, const char * filename, int mode);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn bool _ptask_save_df(ptask * ptsk, datafile * df);
    \brief saves \ref ptask to \ref datafile
*/
bool _ptask_save_df(ptask * ptsk, datafile * df);

//////////////
// stuff

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn bool _ptask_check();
    \brief for internal \ref flow_ptask checking. Writes message to log.
*/
bool _ptask_check();

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn void _sort_ptask(ptask * ptsk, std::vector<unsigned int> * nums, REAL **& sortx_begin, REAL **& sortx_end, REAL **& sorty_begin, REAL **& sorty_end);
    \brief performs \ref ptask sorting
*/
void _sort_ptask(ptask * ptsk, 
		 std::vector<unsigned int> * nums,
		 REAL **& sortx_begin, 
		 REAL **& sortx_end, 
		 REAL **& sorty_begin, 
		 REAL **& sorty_end);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn void _ptask_info(ptask * ptsk);
    \brief prints info about \ref ptask into log-file
*/
void _ptask_info(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn void _ptask_transform(ptask * ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes geometrical transform on \ref flow_ptask (shifting and scaling)
*/
void _ptask_transform(ptask * ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn void _inverse_ptask_transform(ptask * ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);
    \brief makes inverse to \ref _ptask_transform operation
*/
void _inverse_ptask_transform(ptask * ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn ptask * _get_flow_ptask();
    \brief returns \ref flow_ptask
*/
ptask * _get_flow_ptask();

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn void _set_flow_ptask(ptask * ptsk);
    \brief sets \ref flow_ptask
*/
void _set_flow_ptask(ptask * ptsk);

FLOW_EXPORT
/*! \ingroup internal_ptask
    \fn void void _add_flow_ptasks(ptask * ptsk);
    \brief adds ptsk to \ref flow_ptasks
*/
void _add_flow_ptasks(ptask * ptsk);
    
}; // namespace surfit;

#endif


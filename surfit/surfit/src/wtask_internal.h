
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

#ifndef __surfit__wtask_internal__
#define __surfit__wtask_internal__

#include <vector>

namespace surfit {

class vec;
class grid;
class datafile;
class wtask;

////////////////////////////////////////////////
////////////////////////////////////////////////
//                wtask io                   //
////////////////////////////////////////////////
////////////////////////////////////////////////

///////////////
// load

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn wtask * _wtask_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, int col4, const char * mask, int grow_by);
    \brief reads task from formatted text file
    \return pointer to task class
    \param filename filename
    \param taskname taskname
    \param columns columns in text file
    \param col1 column number in text file for X coordinates
    \param col2 column number in text file for Y coordinates
    \param col3 column number in text file for Z coordinates
    \param col4 column number in text file for W - weights
    \param mask mask for scanf
    \param grow_by vector's grow factor
*/
wtask * _wtask_read(const char * filename, const char * taskname, int columns, int col1, int col2, int col3, int col4, const char * mask, int grow_by);

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn wtask * _wtask_load(const char * filename, const char * taskname, int mode);
    \brief reads \ref wtask from ROFF file (see \ref datafile for details)
    \return pointer to task class
    \param filename filename
    \param taskname name
    \param mode rw_mode (0 = bin, 1 = asc)
*/
wtask * _wtask_load(const char * filename, const char * taskname, int mode);

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn wtask * _wtask_load_df(datafile * df, const char * taskname);
    \brief reads \ref wtask from \ref datafile
*/
wtask * _wtask_load_df(datafile * df, const char * taskname);

//////////////
// save

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn bool _wtask_write(wtask * wtsk, const char * filename, const char * mask);
    \brief saves \ref wtask to formatted text file
    \param wtsk pointer to wtask
    \param filename filename
    \param mask mask for printf
*/
bool _wtask_write(wtask * wtsk, const char * filename, const char * mask);

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn bool _wtask_save(wtask * wtsk, const char * filename, int mode);
    \brief saves \ref wtask to ROFF file (see \ref datafile for details)
    \param filename filename
    \param wtsk pointer to wtask
    \param mode rw_mode (0 = bin, 1 = asc)
*/
bool _wtask_save(wtask * wtsk, const char * filename, int mode);

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn bool _wtask_save_df(wtask * wtsk, datafile * df);
    \brief saves \ref wtask to \ref datafile
*/
bool _wtask_save_df(wtask * wtsk, datafile * df);

//////////////
// stuff

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn bool _wtask_check();
    \brief checks for \ref surfit_wtask existance
*/
bool _wtask_check();

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn void _wtask_info(wtask * wtsk);
    \brief prints info about \ref wtask
*/
void _wtask_info(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn task * _get_surfit_wtask();
    \brief returns \ref surfit_wtask
*/
wtask * _get_surfit_wtask();

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn task * _get_surfit_wtask();
    \brief sets \ref surfit_wtask
*/
void _set_surfit_wtask(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn task * _get_surfit_wtask();
    \brief adds wtsk to \ref surfit_wtasks
*/
void _add_surfit_wtasks(wtask * wtsk);

SURFIT_EXPORT
/*! \ingroup internal_wtask
    \fn wtask * _collect_all_wtasks();
    \brief combines all wtasks into one \ref wtask
*/
wtask * _collect_all_wtasks();

}; // namespace surfit;

#endif


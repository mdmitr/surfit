
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

#ifndef __flow_lcm_simple_internal_included__
#define __flow_lcm_simple_internal_included__

namespace surfit {

class datafile;
class lcm_simple;

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn lcm_simple * _lcm_simple_read(const char * filename, const char * lcm_simple_name);
    \brief reads \ref lcm_simple from text file
*/
lcm_simple * _lcm_simple_read(const char * filename, const char * lcm_simple_name);

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn lcm_simple * _lcm_simple_load(const char * filename, const char * lcm_simple_name, int mode);
    \brief reads \ref lcm_simple from ROFF file (see \ref datafile for details)
*/
lcm_simple * _lcm_simple_load(const char * filename, const char * lcm_simple_name, int mode);

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn lcm_simple * _lcm_simple_load_df(datafile * df, const char * lcm_simple_name);
    \brief reads \ref lcm_simple from \ref datafile
*/
lcm_simple * _lcm_simple_load_df(datafile * df, const char * lcm_simple_name);

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn bool _lcm_simple_write(lcm_simple * lcm, const char * filename);
    \brief writes \ref lcm_simple to text file
*/
bool _lcm_simple_write(lcm_simple * lcm, const char * filename);

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn bool _lcm_simple_save(lcm_simple * lcm, const char * filename, int mode);
    \brief saves \ref lcm_simple to ROFF file (see \ref datafile for details)
*/
bool _lcm_simple_save(lcm_simple * lcm, const char * filename, int mode);

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn bool _lcm_simple_save_df(lcm_simple * lcm, datafile * df);
    \brief saves \ref lcm_simple to \ref datafile
*/
bool _lcm_simple_save_df(lcm_simple * lcm, datafile * df);

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn bool _lcm_simple_check();
    \brief checks for \ref flow_lcm_simple existance
*/
bool _lcm_simple_check();

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn int _lcm_simple_info(lcm_simple * lcm);
    \brief prints some info about \ref lcm_simple "lcm"
*/
int _lcm_simple_info(lcm_simple * lcm);

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn lcm_simple * _get_flow_lcm_simple();
    \brief returns pointer to \ref flow_lcm_simple
*/
lcm_simple * _get_flow_lcm_simple();

FLOW_EXPORT
/*! \ingroup internal_lcm_simple
    \fn void _set_flow_lcm_simple(lcm_simple * lcm);
    \brief sets pointer of \ref flow_lcm_simple
*/
void _set_flow_lcm_simple(lcm_simple * lcm);

}; // namespace surfit;

#endif


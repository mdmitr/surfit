
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

#ifndef __flow_lcm_simple_tcl_included__
#define __flow_lcm_simple_tcl_included__

namespace surfit {

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn void lcm_simple_set(REAL permeability = 1, REAL viscosity = 1, REAL multiplier = 1);
    \brief sets parameters for \ref flow_lcm_simple
*/
void lcm_simple_set(REAL permeability = 1, REAL viscosity = 1, REAL multiplier = 1);

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn bool lcm_simple_unload();
    \brief unloads \ref flow_lcm_simple from memory
*/
bool lcm_simple_unload();

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn bool lcm_simple_read(const char * filename, const char * lcm_simple_name);
    \brief reads \ref flow_lcm_simple from text file
*/
bool lcm_simple_read(const char * filename, const char * lcm_simple_name);

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn bool lcm_simple_load(const char * filename, const char * lcm_simple_name = NULL);
    \brief reads \ref flow_lcm_simple from ROFF file (see \ref datafile for details)
*/
bool lcm_simple_load(const char * filename, const char * lcm_simple_name = NULL);

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn bool lcm_simple_write(const char * filename);
    \brief writes \ref flow_lcm_simple to text file
*/
bool lcm_simple_write(const char * filename);

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn bool lcm_simple_save(const char * filename, const char * lcm_simple_name = NULL);
    \brief saves \ref flow_lcm_simple to ROFF file (see \ref datafile for details)
*/
bool lcm_simple_save(const char * filename, const char * lcm_simple_name = NULL);

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn bool lcm_simple_check();
    \brief checks for \ref flow_lcm_simple existance
*/
bool lcm_simple_check();

FLOW_EXPORT
/*! \ingroup tcl_lcm_simple
    \fn int lcm_simple_info();
    \brief prints parameters of \ref flow_lcm_simple 
*/
int lcm_simple_info();

}; // namespace surfit;

#endif


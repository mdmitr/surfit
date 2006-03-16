
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

#ifndef __surfit_freeflow_included__
#define __surfit_freeflow_included__

/*!
\defgroup freeflow_internal C/C++ functions and variables reference
*/

/*! 
\defgroup internal_pfunc func
\ingroup freeflow_internal
*/

/*! 
\defgroup internal_ptask ptask
\ingroup freeflow_internal
*/

/*! 
\defgroup internal_pcurv curves
\ingroup freeflow_internal
*/

	/*! 
	\defgroup internal_parea parea
	\ingroup internal_pcurv
	*/

	/*! 
	\defgroup internal_piso piso
	\ingroup internal_pcurv
	*/
	
	/*! 
	\defgroup internal_pcntr pcntr
	\ingroup internal_pcurv
	*/

/*! 
\defgroup internal_lcm_simple lcm_simple
\ingroup freeflow_internal
*/

//////
//
// Tcl functions and variables
//
//////

/*! 
\defgroup flow_tcl Tcl commands and variables reference
*/

/*!
\defgroup flow_variables freeflow variables
\ingroup flow_tcl
*/

  /*!
  \defgroup flow_data_variables freeflow data variables
  \ingroup flow_variables
  */

  /*!
  \defgroup flow_variables_collections collections of freeflow variables
  \ingroup flow_data_variables
  */

/*! 
\defgroup tcl_pfunc operations with functions (func)
\ingroup flow_tcl
*/

/*! 
\defgroup tcl_ptask scattered production points (ptask)
\ingroup flow_tcl
*/

  /*!
  \defgroup tcl_ptask_save_load saving and loading
  \ingroup tcl_ptask
  */

  /*!
  \defgroup tcl_ptask_math mathematical operations 
  \ingroup tcl_ptask
  */

  /*!
  \defgroup tcl_ptask_conv converting to other objects
  \ingroup tcl_ptask
  */

  /*!
  \defgroup tcl_ptask_other other operations
  \ingroup tcl_ptask
  */

  /*!
  \defgroup tcl_ptasks operations with task collections
  \ingroup tcl_ptask
  */

  /*!
  \defgroup tcl_ptask_gl OpenGL drawing
  \ingroup tcl_ptask
  */

/*!
\defgroup tcl_pcurves curves
\ingroup flow_tcl
*/

/*!
\defgroup tcl_parea production area (parea)
\ingroup tcl_pcurves
*/

  /*!
  \defgroup tcl_parea_save_load saving and loading 
  \ingroup tcl_parea
  */

  /*!
  \defgroup tcl_parea_conv converting to other objects
  \ingroup tcl_parea
  */

  /*!
  \defgroup tcl_parea_other other operations
  \ingroup tcl_parea
  */

  /*!
  \defgroup tcl_pareas operations with parea collections
  \ingroup tcl_parea
  */

  /*!
  \defgroup tcl_parea_gl OpenGL drawing
  \ingroup tcl_parea
  */

/*!
\defgroup tcl_piso constant production line (piso)
\ingroup tcl_pcurves
*/

  /*!
  \defgroup tcl_piso_save_load saving and loading 
  \ingroup tcl_piso
  */

  /*!
  \defgroup tcl_piso_conv converting to other objects
  \ingroup tcl_piso
  */

  /*!
  \defgroup tcl_piso_other other operations
  \ingroup tcl_piso
  */

  /*!
  \defgroup tcl_pisos operations with piso collections
  \ingroup tcl_piso
  */

  /*!
  \defgroup tcl_piso_gl OpenGL drawing
  \ingroup tcl_piso
  */

/*!
\defgroup tcl_pcntr variable production line (pcntr)
\ingroup tcl_pcurves
*/

  /*!
  \defgroup tcl_pcntr_save_load saving and loading 
  \ingroup tcl_pcntr
  */

  /*!
  \defgroup tcl_pcntr_math mathematical operations
  \ingroup tcl_pcntr
  */

  /*!
  \defgroup tcl_pcntr_conv converting to other objects
  \ingroup tcl_pcntr
  */

  /*!
  \defgroup tcl_pcntr_other other operations
  \ingroup tcl_pcntr
  */

  /*!
  \defgroup tcl_pcntrs operations with pcntr collections
  \ingroup tcl_pcntr
  */

  /*!
  \defgroup tcl_pcntr_gl OpenGL drawing
  \ingroup tcl_pcntr
  */

/*!
\defgroup tcl_lcm_simple simple law of conservation of mass (lcm_simple)
\ingroup flow_tcl
*/


#endif


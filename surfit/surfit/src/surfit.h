
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

#ifndef __surfit__included__
#define __surfit__included__

struct Tcl_Interp;

namespace surfit {

SURFIT_EXPORT
bool init_surfit_lib(Tcl_Interp * interp);

}; // namespace surfit;

//////
//
//  Internal functions and variables
//
//////

/*!
\defgroup internal C/C++ functions and variables reference
*/

/*! 
\defgroup internal_grid grid
\ingroup internal
*/

  /*! 
  \defgroup internal_func func
  \ingroup internal_grid
  */

    /*!
    \defgroup int_func_wavan wavelets section
    \ingroup internal_func
    */


  /*! 
  \defgroup internal_wfunc wfunc
  \ingroup internal_grid
  */
    
  /*! 
  \defgroup internal_trend trend
  \ingroup internal_grid
  */

  /*!
  \defgroup internal_defarea defarea
  \ingroup internal_grid
  */

/*!
\defgroup internal_points points
\ingroup internal
*/

  /*! 
  \defgroup internal_task task
  \ingroup internal_points
  */

  /*! 
  \defgroup internal_wtask wtask
  \ingroup internal_points
  */


/*! 
\defgroup internal_curv curv
\ingroup internal
*/

  /*!
  \defgroup internal_iso iso
  \ingroup internal_curv
  */

    /*!
    \defgroup internal_wiso wiso
    \ingroup internal_iso
    */

  /*!
  \defgroup internal_flt flt
  \ingroup internal_curv
  */

  /*!
  \defgroup internal_area area
  \ingroup internal_curv
  */

    /*!
    \defgroup internal_warea warea
    \ingroup internal_area
    */

  /*!
  \defgroup internal_cntr cntr
  \ingroup internal_curv
  */

    /*!
    \defgroup internal_wcntr wcntr
    \ingroup internal_cntr
    */

  /*!
  \defgroup internal_grid_line grid_line
  \ingroup internal_curv
  */

/*!
\defgroup internal_misc miscellaneous 
\ingroup internal
*/























//////
//
// Tcl functions and variables
//
//////

/*! 
\defgroup tcl Tcl commands and variables reference
*/

/*!
\defgroup surfit_variables surfit variables
\ingroup tcl
*/

  /*!
  \defgroup surfit_data_variables surfit data variables
  \ingroup surfit_variables
  */

    /*!
    \defgroup surfit_variables_collections collections of surfit variables
    \ingroup surfit_data_variables
    */

  /*!
  \defgroup surfit_gl_variables surfit variables for OpenGL drawing
  \ingroup surfit_variables
  */

/*! 
\defgroup tcl_grid equidistant grid (grid)
\ingroup tcl

You can see on of the following examples:

\li \ref map_area.tcl   
\li \ref map_cntr.tcl   
\li \ref map_defarea.tcl
\li \ref map_flt.tcl    
\li \ref map_func.tcl   
\li \ref map_iso.tcl    
\li \ref map_task.tcl   
\li \ref map_trend.tcl  
\li \ref map_warea.tcl  
\li \ref map_wcntr.tcl  
\li \ref map_wfunc.tcl  
\li \ref map_wiso.tcl   
\li \ref map_wtask.tcl  
*/

  /*!
  \defgroup tcl_grid_save_load saving and loading 
  \ingroup tcl_grid
  */

  /*!
  \defgroup tcl_grid_create constructing grid
  \ingroup tcl_grid
  */

  /*!
  \defgroup tcl_grid_other other operations
  \ingroup tcl_grid
  */

  /*!
  \defgroup tcl_grid_gl OpenGL drawing
  \ingroup tcl_grid
  */


/*! 
\defgroup tcl_opoints ordered points
\ingroup tcl
*/

/*! 
\defgroup tcl_func function for interpolation (func)
\ingroup tcl_opoints

\par Example:
\li \ref map_func.tcl
*/

  /*!
  \defgroup tcl_func_save_load saving and loading 
  \ingroup tcl_func
  */

  /*!
  \defgroup tcl_func_math mathematical operations
  \ingroup tcl_func
  */

  /*!
  \defgroup tcl_func_wavan wavelet analysis
  \ingroup tcl_func
  */

  /*!
  \defgroup tcl_func_conv converting to other objects
  \ingroup tcl_func
  */

  /*!
  \defgroup tcl_func_other other operations
  \ingroup tcl_func
  */

  /*!
  \defgroup tcl_funcs operations with func collections
  \ingroup tcl_func
  */

  /*!
  \defgroup tcl_func_gl OpenGL drawing
  \ingroup tcl_func
  */


/*! 
\defgroup tcl_wfunc function for approximation (wfunc)
\ingroup tcl_opoints

\par Example:
\li \ref map_wfunc.tcl
*/

  /*!
  \defgroup tcl_wfunc_save_load saving and loading 
  \ingroup tcl_wfunc
  */

  /*!
  \defgroup tcl_wfunc_math mathematical operations 
  \ingroup tcl_wfunc
  */

  /*!
  \defgroup tcl_wfunc_wavan wavelet analysis 
  \ingroup tcl_wfunc
  */

  /*!
  \defgroup tcl_wfunc_conv converting to other objects
  \ingroup tcl_wfunc
  */

  /*!
  \defgroup tcl_wfunc_other other operations
  \ingroup tcl_wfunc
  */

  /*!
  \defgroup tcl_wfuncs operations with wfunc collections
  \ingroup tcl_wfunc
  */

  /*!
  \defgroup tcl_wfunc_gl OpenGL drawing
  \ingroup tcl_wfunc
  */


/*! 
\defgroup tcl_trend trend function (trend)
\ingroup tcl_opoints

\par Example:
\li \ref map_trend.tcl
*/

  /*!
  \defgroup tcl_trend_save_load saving and loading 
  \ingroup tcl_trend
  */

  /*!
  \defgroup tcl_trend_math mathematical operations 
  \ingroup tcl_trend
  */

  /*!
  \defgroup tcl_trend_wavan wavelet analysis 
  \ingroup tcl_trend
  */

  /*!
  \defgroup tcl_trend_conv converting to other objects
  \ingroup tcl_trend
  */

  /*!
  \defgroup tcl_trend_other other operations
  \ingroup tcl_trend
  */

  /*!
  \defgroup tcl_trends operations with trend collections
  \ingroup tcl_trend
  */

  /*!
  \defgroup tcl_trend_gl OpenGL drawing
  \ingroup tcl_trend
  */


/*! 
\defgroup tcl_defarea definition area (defarea)
\ingroup tcl_opoints
*/

  /*!
  \defgroup tcl_defarea_save_load saving and loading 
  \ingroup tcl_defarea
  */

  /*!
  \defgroup tcl_defarea_math mathematical operations 
  \ingroup tcl_defarea
  */

  /*!
  \defgroup tcl_defarea_conv converting to other objects
  \ingroup tcl_defarea
  */

  /*!
  \defgroup tcl_defarea_other other operations
  \ingroup tcl_defarea
  */

  /*!
  \defgroup tcl_defareas operations with defarea collections
  \ingroup tcl_defarea
  */

  /*!
  \defgroup tcl_defarea_gl OpenGL drawing
  \ingroup tcl_defarea
  */

/*! 
\defgroup tcl_points scattered points
\ingroup tcl
*/

/*! 
\defgroup tcl_task scattered data-points for interpolation (task)
\ingroup tcl_points

  \par Example:
  \li \ref map_task.tcl  

*/

  /*!
  \defgroup tcl_task_save_load saving and loading
  \ingroup tcl_task
  */

  /*!
  \defgroup tcl_task_math mathematical operations 
  \ingroup tcl_task
  */

  /*!
  \defgroup tcl_task_conv converting to other objects
  \ingroup tcl_task
  */

  /*!
  \defgroup tcl_task_other other operations
  \ingroup tcl_task
  */

  /*!
  \defgroup tcl_tasks operations with task collections
  \ingroup tcl_task
  */

  /*!
  \defgroup tcl_task_gl OpenGL drawing
  \ingroup tcl_task
  */

/*! 
\defgroup tcl_wtask scattered data-points for approximation (wtask)
\ingroup tcl_points

  \par Example:
  \li \ref map_wtask.tcl  

*/

  /*!
  \defgroup tcl_wtask_save_load saving and loading
  \ingroup tcl_wtask
  */

  /*!
  \defgroup tcl_wtask_math mathematical operations 
  \ingroup tcl_wtask
  */

  /*!
  \defgroup tcl_wtask_conv converting to other objects
  \ingroup tcl_wtask
  */

  /*!
  \defgroup tcl_wtask_other other operations
  \ingroup tcl_wtask
  */

  /*!
  \defgroup tcl_wtasks operations with wtask collections
  \ingroup tcl_wtask
  */

  /*!
  \defgroup tcl_wtask_gl OpenGL drawing
  \ingroup tcl_wtask
  */

/*!
\defgroup tcl_curves curves
\ingroup tcl
*/

/*!
\defgroup tcl_curv curve (curv)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_curv_save_load saving and loading 
  \ingroup tcl_curv
  */

  /*!
  \defgroup tcl_curv_conv converting to other objects
  \ingroup tcl_curv
  */

  /*!
  \defgroup tcl_curv_other other operations
  \ingroup tcl_curv
  */

  /*!
  \defgroup tcl_curvs operations with curv collections
  \ingroup tcl_curv
  */

  /*!
  \defgroup tcl_curv_gl OpenGL drawing
  \ingroup tcl_curv
  */

/*!
\defgroup tcl_iso isoline for interpolation (iso)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_iso_save_load saving and loading 
  \ingroup tcl_iso
  */

  /*!
  \defgroup tcl_iso_conv converting to other objects
  \ingroup tcl_iso
  */

  /*!
  \defgroup tcl_iso_other other operations
  \ingroup tcl_iso
  */

  /*!
  \defgroup tcl_isos operations with iso collections
  \ingroup tcl_iso
  */

  /*!
  \defgroup tcl_iso_gl OpenGL drawing
  \ingroup tcl_iso
  */

/*!
\defgroup tcl_wiso isoline for approximation (wiso)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_wiso_save_load saving and loading 
  \ingroup tcl_wiso
  */

  /*!
  \defgroup tcl_wiso_conv converting to other objects
  \ingroup tcl_wiso
  */

  /*!
  \defgroup tcl_wiso_other other operations
  \ingroup tcl_wiso
  */

  /*!
  \defgroup tcl_wisos operations with wiso collections
  \ingroup tcl_wiso
  */

  /*!
  \defgroup tcl_wiso_gl OpenGL drawing
  \ingroup tcl_wiso
  */

/*!
\defgroup tcl_flt tectonical fault line (flt)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_flt_save_load saving and loading 
  \ingroup tcl_flt
  */

  /*!
  \defgroup tcl_flt_conv converting to other objects
  \ingroup tcl_flt
  */

  /*!
  \defgroup tcl_flt_other other operations
  \ingroup tcl_flt
  */

  /*!
  \defgroup tcl_flts operations with flt collections
  \ingroup tcl_flt
  */

  /*!
  \defgroup tcl_flt_gl OpenGL drawing
  \ingroup tcl_flt
  */

/*!
\defgroup tcl_area area for interpolation (area)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_area_save_load saving and loading 
  \ingroup tcl_area
  */

  /*!
  \defgroup tcl_area_conv converting to other objects
  \ingroup tcl_area
  */

  /*!
  \defgroup tcl_area_other other operations
  \ingroup tcl_area
  */

  /*!
  \defgroup tcl_areas operations with area collections
  \ingroup tcl_area
  */

  /*!
  \defgroup tcl_area_gl OpenGL drawing
  \ingroup tcl_area
  */

/*!
\defgroup tcl_warea area for approximation (warea)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_warea_save_load saving and loading 
  \ingroup tcl_warea
  */

  /*!
  \defgroup tcl_warea_conv converting to other objects
  \ingroup tcl_warea
  */

  /*!
  \defgroup tcl_warea_other other operations
  \ingroup tcl_warea
  */

  /*!
  \defgroup tcl_wareas operations with warea collections
  \ingroup tcl_warea
  */

  /*!
  \defgroup tcl_warea_gl OpenGL drawing
  \ingroup tcl_warea
  */

/*!
\defgroup tcl_cntr contour for interpolation (cntr)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_cntr_save_load saving and loading 
  \ingroup tcl_cntr
  */

  /*!
  \defgroup tcl_cntr_math mathematical operations
  \ingroup tcl_cntr
  */

  /*!
  \defgroup tcl_cntr_conv converting to other objects
  \ingroup tcl_cntr
  */

  /*!
  \defgroup tcl_cntr_other other operations
  \ingroup tcl_cntr
  */

  /*!
  \defgroup tcl_cntrs operations with cntr collections
  \ingroup tcl_cntr
  */

  /*!
  \defgroup tcl_cntr_gl OpenGL drawing
  \ingroup tcl_cntr
  */

/*!
\defgroup tcl_wcntr contour for approximation (wcntr)
\ingroup tcl_curves
*/

  /*!
  \defgroup tcl_wcntr_save_load saving and loading 
  \ingroup tcl_wcntr
  */

  /*!
  \defgroup tcl_wcntr_math mathematical operations
  \ingroup tcl_wcntr
  */

  /*!
  \defgroup tcl_wcntr_conv converting to other objects
  \ingroup tcl_wcntr
  */

  /*!
  \defgroup tcl_wcntr_other other operations
  \ingroup tcl_wcntr
  */

  /*!
  \defgroup tcl_wcntrs operations with wcntr collections
  \ingroup tcl_wcntr
  */

  /*!
  \defgroup tcl_wcntr_gl OpenGL drawing
  \ingroup tcl_wcntr
  */

/*!
\defgroup tcl_grid_line grid based line (grid_line)
\ingroup tcl_curves
*/

/*!
\defgroup tcl_whole data for whole domain
\ingroup tcl
*/

/*!
\defgroup tcl_completer completer
\ingroup tcl_whole
*/

/*! 
\defgroup tcl_fill_with fill_with
\ingroup tcl_whole
*/

/*!
\defgroup tcl_dynamic dynamically loadable data
\ingroup tcl
*/

/*!
\defgroup tcl_log log file operations
\ingroup tcl
*/

/*!
\defgroup tcl_file ROFF file operations
\ingroup tcl
*/

#endif



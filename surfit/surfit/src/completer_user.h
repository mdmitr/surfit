
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

#ifndef __surfit_completer_user_included__
#define __surfit_completer_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class completer;

/*! \ingroup surfit_data_variables
    \var surfit_completer
    \brief describes the surface behavior in the areas of low data density.
    
Implements so-called "completer" functional. 
This functional describes the surface behavior in the areas of 
low data density.
  
This functional can be written with formula:

\f[ 
 A_{i,j} = 
 \mathbf{D_1} \frac{h_y}{h_x} \left[ 
 (u_{i+1,j}-u_{i,j})^2 + (u_{i,j} - u_{i-1,j})^2
 \right] + 
 \mathbf{D_1} \frac{h_x}{h_y} \left[ 
 (u_{i,j+1}-u_{i,j})^2 + (u_{i,j-1} - u_{i,j})^2
 \right] +
\f]
\f[ 
 +  \mathbf{D_2} \frac{h_y^2}{h_x^2}
 \left[
 (u_{i+2,j} - 2u_{i+1,j} + u_{i,j})^2  +
 (u_{i+1,j} - 2u_{i,j} + u_{i-1,j})^2  +
 (u_{i,j} - 2u_{i-1,j} + u_{i-2,j})^2 
 \right] +
\f]
\f[ 
 +  2 \mathbf{D_2} \left(
 \left[
 (u_{i+1,j+1} - u_{i,j+1} - u_{i+1,j} + u_{i,j})
 \right] +
 \left[
 (u_{i,j+1} - u_{i-1,j+1} - u_{i,j} + u_{i-1,j})
 \right] \right) +
\f]
\f[ 
 +  \mathbf{D_2} \frac{h_x^2}{h_y^2}
 \left[
 (u_{i,j+2} - 2u_{i,j+1} + u_{i,j})^2  +
 (u_{i,j+1} - 2u_{i,j} + u_{i,j-1})^2  +
 (u_{i,j} - 2u_{i,j-1} + u_{i,j-2})^2 
 \right] +
\f]
\f[ 
 +  2 \mathbf{D_2} \left(
 \left[
 (u_{i+1,j+1} - u_{i+1,j} - u_{i,j+1} + u_{i,j})
 \right] +
 \left[
 (u_{i+1,j} - u_{i+1,j-1} - u_{i,j} + u_{i,j-1})
 \right] \right) = \min.
\f]
Functional \f$ A_{i,j} = \min \f$ writes for each "unsolved" cell \f$ u_{i,j} \f$ with respect of
grid boundaries. 

"Completer" functional can be modified using following classes:
\li \ref surfit_wfunc and \ref surfit_wfuncs
\li \ref surfit_wtask and \ref surfit_wtasks
\li \ref surfit_wiso and \ref surfit_wisos
\li \ref surfit_wcntr and \ref surfit_wcntrs
\li \ref surfit_warea and \ref surfit_wareas
\li \ref surfit_flt and \ref surfit_flts

Here is simple example of "completer" D1 and D2 variables influence:

\image html surface_and_points.jpg "function reconstructed by scattered data points with completer_set 0 1"

\image html surface_and_points2.jpg "function reconstructed by scattered data points with completer_set 1 5"

\image html surface_and_points3.jpg "function reconstructed by scattered data points with completer_set 1 0"

\par Other examples: 
\li \ref map_area.tcl
\li \ref map_cntr.tcl
\li \ref map_flt.tcl
\li \ref map_iso.tcl
\li \ref map_task.tcl
\li \ref map_warea.tcl
\li \ref map_wcntr.tcl
\li \ref map_wfunc.tcl
\li \ref map_wiso.tcl 
\li \ref map_wtask.tcl


\sa 
\li \ref completer
\li \ref tcl_completer "Tcl commands"
*/
extern SURFIT_EXPORT completer * surfit_completer;

class vec;
class intvec;
class bitvec;
class func;
class oper;
class grid;

SURFIT_EXPORT
int calcVecV(int size, 
	     vec * X,
	     oper * T, 
	     vec *& res,
	     int NN, int MM,
	     bitvec * mask_solved,
	     bitvec * mask_undefined,
	     int use_x_from = -1, int use_x_to = -1,
	     int use_y_from = -1, int use_y_to = -1,
	     func * trend = NULL);

SURFIT_EXPORT
void use_flood_areas(REAL D1, REAL D2,
		     std::vector<short int> * flood_areas,
		     int flood_areas_cnt,
		     grid * grd,
		     modifier1 * usr);

SURFIT_EXPORT
void set_solved(bitvec * mask_solved, bitvec * mask_undefined);

/*! \class completer_user
    \brief class for making equations from \ref completer. 
    Equations can be modified with diagonal matrix via \ref modifier1
*/
class SURFIT_EXPORT completer_user : public user, public modifier1 {
public:

	//! constructor
	completer_user();

	//! destructor
	~completer_user();

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



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

#ifndef __surfit_trend_user_included__
#define __surfit_trend_user_included__

#include "user.h"
#include <vector>

namespace surfit {

class trend;

/*! \ingroup surfit_data_variables
    \var surfit_trend
    \brief trend surface

Trend surface. We describe trend the same as function (\ref func), but trend
have two additional parameters D1 and D2. trend defines the result surface behavior at the areas of 
low information density.

By loading \ref trend object to surfit memory we write the follow functionals to the sequence:

\f[ 
 A_{i,j} = 
 \mathbf{D_1} \frac{h_y}{h_x} \left[ 
 \left( (u_{i+1,j}-u_{i,j}) - (t_{i+1,j}-t_{i,j}) \right)^2 + \left( (u_{i,j} - u_{i-1,j})-(t_{i,j} - t_{i-1,j}) \right)^2
 \right] + 
\f]
\f[
 \mathbf{D_1} \frac{h_x}{h_y} \left[ 
 \left( (u_{i,j+1}-u_{i,j})-(t_{i,j+1}-t_{i,j}) \right)^2 + \left( (u_{i,j-1} - u_{i,j}) -  (t_{i,j-1} - t_{i,j})\right)^2
 \right] +
\f]
\f[ 
 +  \mathbf{D_2} \frac{h_y^2}{h_x^2}
 \left[
 \left( (u_{i+2,j} - 2u_{i+1,j} + u_{i,j}) - (t_{i+2,j} - 2t_{i+1,j} + t_{i,j}) \right)^2  + \right.
\f]
\f[
 \left( (u_{i+1,j} - 2u_{i,j} + u_{i-1,j}) - (t_{i+1,j} - 2t_{i,j} + t_{i-1,j}) \right)^2  +
\f]
\f[
 \left.
 \left( (u_{i,j} - 2u_{i-1,j} + u_{i-2,j}) - (t_{i,j} - 2t_{i-1,j} + t_{i-2,j}) \right)^2 
 \right] +
\f]
\f[ 
 +  2 \mathbf{D_2} \left(
 \left[
 \left( (u_{i+1,j+1} - u_{i,j+1} - u_{i+1,j} + u_{i,j}) - (t_{i+1,j+1} - t_{i,j+1} - t_{i+1,j} + t_{i,j}) \right)
 \right] + \right.
\f]
\f[
 \left.
 \left[
 \left( (u_{i,j+1} - u_{i-1,j+1} - u_{i,j} + u_{i-1,j}) - (t_{i,j+1} - t_{i-1,j+1} - t_{i,j} + t_{i-1,j}) \right)
 \right] \right) +
\f]
\f[ 
 +  \mathbf{D_2} \frac{h_x^2}{h_y^2}
 \left[
 \left( (u_{i,j+2} - 2u_{i,j+1} + u_{i,j}) - (t_{i,j+2} - 2t_{i,j+1} + t_{i,j}) \right)^2  +
 \right.
\f]
\f[
 \left( (u_{i,j+1} - 2u_{i,j} + u_{i,j-1}) - (t_{i,j+1} - 2t_{i,j} + t_{i,j-1}) \right)^2  +
\f]
\f[
 \left.
 \left( (u_{i,j} - 2u_{i,j-1} + u_{i,j-2}) - (t_{i,j} - 2t_{i,j-1} + t_{i,j-2}) \right)^2 
 \right] +
\f]
\f[ 
 +  2 \mathbf{D_2} \left(
 \left[
 \left( (u_{i+1,j+1} - u_{i+1,j} - u_{i,j+1} + u_{i,j}) - (t_{i+1,j+1} - t_{i+1,j} - t_{i,j+1} + t_{i,j}) \right)
 \right] +
 \right.
\f]
\f[
 \left.
 \left[
 \left( (u_{i+1,j} - u_{i+1,j-1} - u_{i,j} + u_{i,j-1}) - (t_{i+1,j} - t_{i+1,j-1} - t_{i,j} + t_{i,j-1}) \right)
 \right] \right) = \min.
\f]


About functional sequence and surfit method of function reconstruction see \ref data.

\par Example : 
\li \ref map_trend.tcl "Interpolation of scattered data points with trend and fault"

\sa 
\li \ref surfit_trends
\li \ref trend
\li \ref tcl_trend "Tcl commands"

*/
extern SURFIT_EXPORT trend * surfit_trend;

/*! \ingroup surfit_variables_collections
    \var surfit_trends
    collection of \ref trend objects
*/
extern SURFIT_EXPORT std::vector<trend *> * surfit_trends;

/*! \class trend_user
    \brief class for making equations from \ref trend. 
    Equations can be modified with diagonal matrix via \ref modifier1
*/
class SURFIT_EXPORT trend_user : public user, public modifier1 {
public:

	//! constructor
	trend_user();

	//! destructor
	~trend_user();
	
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


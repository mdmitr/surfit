
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

#include "flow_ie.h"

#ifdef HAVE_GL_WORKS

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include "windows.h"
#endif

#include "fileio.h"
#include "vec.h"
#include "curv.h"
#include "piso.h"
#include "piso_internal.h"
#include "parea.h"
#include "parea_internal.h"
#include "pcntr.h"
#include "pcntr_internal.h"
#include "variables_tcl.h"

#include "curv_show.h"
#include "draw.h"
#include "draw_object.h"
#include "colors.h"
#include "projector.h"

#include <GL/gl.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

// delete this include!!!
#include "iso_show.h"
#include "area_show.h"
#include "cntr_show.h"

namespace surfit {


}; // namespace surfit;

#endif 




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


%module freeflow
%{
#include "flow_colors.h"
#include "ptask_show.h"
#include "parea_show.h"
#include "piso_show.h"
#include "pcntr_show.h"
%}

namespace surfit {

extern int ptask_color_red;
extern int ptask_color_green;
extern int ptask_color_blue;
extern int ptask_color_alpha;
extern int draw_ptask;

extern int parea_color_red;
extern int parea_color_green;
extern int parea_color_blue;
extern int parea_color_alpha;
extern int draw_parea;

extern int piso_color_red;
extern int piso_color_green;
extern int piso_color_blue;
extern int piso_color_alpha;
extern int draw_piso;

extern int pcntr_color_red;
extern int pcntr_color_green;
extern int pcntr_color_blue;
extern int pcntr_color_alpha;
extern int draw_pcntr;

%exception {
%#ifdef HAVE_GL_WORKS
        try {
                $action
        }
        catch(...) {
                return TCL_ERROR;
        }
%#else
        return TCL_ERROR;
%#endif
};

void ptask_color(const char * color_name);
void ptask_show(const char * filename = NULL, const char * ptaskname = NULL);

void parea_color(const char * color_name);
void parea_show(const char * filename = NULL, const char * pareaname = NULL);

void piso_color(const char * color_name);
void piso_show(const char * filename = NULL, const char * pisoname = NULL);

void pcntr_color(const char * color_name);
void pcntr_show(const char * filename = NULL, const char * pcntrname = NULL);

};


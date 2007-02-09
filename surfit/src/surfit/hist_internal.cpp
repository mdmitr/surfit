
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

#include "surfit_ie.h"

#include "fileio.h"
#include "datafile.h"
#include "vec.h"
#include "read_txt.h"

#include "hist.h"
#include "hist_internal.h"

namespace surfit {

void _hist_info(const d_hist * histline) {
	if (!histline) {
		writelog(LOG_WARNING, "_hist_info : NULL pointer given");
		return;
	}
	if (histline->getName()) {
		writelog(LOG_MESSAGE,"hist (%s)",histline->getName());
	} else {
		writelog(LOG_MESSAGE,"hist noname");	
	}
};

void _add_surfit_hists(d_hist * hst) {
	if (!hst)
		return;
	surfit_hists->push_back(hst);
};

bool _surf_histeq(d_surf * srf)
{
	return false;
};

}; // namespace surfit;


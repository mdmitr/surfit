
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
#include "sstuff.h"

#include "hist.h"
#include "hist_internal.h"
#include "surf.h"

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

bool _surf_histeq(d_surf * srf, const d_hist * hist)
{
	// create cummulative histogram
	vec * cum = create_vec(hist->hst->size(),0,0); // don't fill

	size_t i;
	size_t surf_size = 0;
	for (i = 0; i < srf->getCountX()*srf->getCountY(); i++) {
		if (srf->getValue(i) == srf->undef_value)
			continue;
		surf_size++;
	}

	REAL sum = 0;
	for (i = 0; i < cum->size(); i++) {
		sum += (*(hist->hst))(i);
		(*cum)(i) = sum;///REAL(surf_size);
	}

	cum->release();
	return false;
};

bool _hist_write(const d_hist * hist, const char * filename) {
	if (!hist) {
		writelog(LOG_WARNING, "NULL pointer to hist.");
		return false;
	};
	if (hist->size() == 0) {
		writelog(LOG_WARNING, "Empty histogram for saving!");
		return false;
	}

	writelog(LOG_MESSAGE,"writing histogram \"%s\" to file %s",
		hist->getName()?hist->getName():"noname", filename);

	return one_columns_write(filename, "%g\n", hist->hst);
};

d_hist * _hist_read(const char * filename, REAL minz, REAL maxz, const char * histname, int col1, const char * delimiter, int skip_lines, int grow_by) {

	if (histname)
		writelog(LOG_MESSAGE,"reading histogram \"%s\" from file %s", histname, filename);
	else 
		writelog(LOG_MESSAGE,"reading histogram from file %s", filename);

	vec * vcol1 = NULL;
	d_hist * res = NULL;

	if (!one_columns_read(filename, col1, 
			      skip_lines, delimiter, grow_by, vcol1))
		return NULL;
		
	res = create_hist(minz, maxz, vcol1, histname);

	if (histname == NULL) {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}
	
	return res;
};

}; // namespace surfit;


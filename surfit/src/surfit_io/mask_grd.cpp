
/*------------------------------------------------------------------------------
 *	$Id: $
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
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

#include "surfit_io_ie.h"
#include "mask.h"
#include "bitvec.h"

#include <errno.h>

namespace surfit {

bool mask_save_grd(const char * filename, const char * pos) 
{
	d_mask * msk = get_element<d_mask>(pos, surfit_masks->begin(), surfit_masks->end());
	if (!msk)
		return false;

	if (!filename)
		return false;

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	writelog(LOG_MESSAGE,"Saving mask %s to file %s (grd-ASCII)", msk->getName(), filename);

	fprintf(f,"DSAA\n");
	int nx = msk->getCountX();
	int ny = msk->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", msk->getMinX(), msk->getMaxX());
	fprintf(f,"%lf %lf\n", msk->getMinY(), msk->getMaxY());
	fprintf(f,"0 1\n");

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = msk->coeff->get( ix + nx*iy );
			fprintf(f,"%lf ", val);
			if (ncnt>9) { 
				fprintf(f,"\n");
				ncnt = 0;
			}
			ncnt++;
		}
		fprintf(f,"\n");
	}

	fclose(f);

	return true;
};

}; // namespace surfit;


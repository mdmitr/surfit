
/*------------------------------------------------------------------------------
 *	$Id: cntr_bln.cpp 823 2006-07-12 10:15:53Z mishadm $
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
#include "surf_io.h"

// sstuff includes
#include "sstuff.h"

// surfit includes
#include "cntr.h"
#include "fileio.h"
#include "vec.h"
#include "variables_tcl.h"
#include "grid.h"

namespace surfit {

d_cntr * _cntr_load_bln(FILE * file, int & orient)
{
	char buf[1024];
	int r = 0;
	int cnt = 0;

	int num_points = 0;
	char * name = NULL;
	char * token = NULL;
	char seps[] = ", \t";
	vec * X = create_vec();
	vec * Y = create_vec();
	vec * Z = create_vec();
	d_cntr * res = NULL;
	const char * pos1 = NULL;
	const char * pos2 = NULL;

	if (fgets(buf, 1024, file) == NULL)
		goto bad_file;
	

	cnt = -1;
	token = strtok( buf, seps );
	while (token != NULL) {
		if (strlen(token) > 0)
			cnt++;
		if (cnt == 0)
			num_points = atoi(token);
		if (cnt == 1)
			orient = atoi(token);
		if (cnt == 2) {
			pos1 = strchr(token,'"');
			if (pos1) {
				pos1++;
				pos2 = strchr(pos1,'"');
				if (pos2) {
					pos2--;
					if (name)
						free(name);
					name = (char *)malloc( sizeof(char)*(pos2-pos1+2) );
					strncpy(name, pos1, pos2-pos1+1);
					name[pos2-pos1+1] = '\0';
				}
			}
			
		}
		token = strtok( NULL, seps );
	}

	for (cnt = 0; cnt < num_points; cnt++) {
		if (fgets(buf, 1024, file) == NULL)
			goto bad_file;

		int i = -1;
		token = strtok( buf, seps );
		while (token != NULL) {
			if (strlen(token) > 0)
				i++;
			if (i == 0) {
				REAL val = atof(token);
				X->push_back(val);
			}
			if (i == 1) {
				REAL val = atof(token);
				Y->push_back(val);
			}
			if (i == 2) {
				REAL val = atof(token);
				Z->push_back(val);
			}
			token = strtok( NULL, seps );
		}
	};

	if ((X->size() != Y->size()) || (X->size() != Z->size()))
		goto bad_file;

	res = create_cntr(X, Y, Z, name);
	if (name)
		free(name);
	return res;


bad_file:
	free(name);
	if (X)
		X->release();
	if (Y)
		Y->release();
	if (Z)
		Z->release();
	return NULL;
};

bool _cntr_save_bln(const d_cntr * crv, FILE * file, int orient) {

	int size = crv->size();
	
	if (size == 0)
		return false;

	int i;

	if (crv->getName()) {
		if ( fprintf(file, "%d,%d \"%s\"\n",size, orient, crv->getName()) <= 0 )
			goto bad_save_bln;
	} else {
		if ( fprintf(file, "%d,%d\n",size, orient) <= 0 )
			goto bad_save_bln;
	}

	for (i = 0; i < size; i++) {
		if ( fprintf(file, "%lf,%lf,%lf\n", (*(crv->X))(i), (*(crv->Y))(i), (*(crv->Z))(i)) <= 0)
			goto bad_save_bln;
	}

	return true;

bad_save_bln:
	return false;
};


};


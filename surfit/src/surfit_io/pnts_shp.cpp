
/*------------------------------------------------------------------------------
 *	$Id$
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
#include "pnts_io.h"

// sstuff includes
#include "sstuff.h"

// surfit includes
#include "points.h"
#include "fileio.h"
#include "vec.h"
#include "strvec.h"

#include <float.h>

#include "shapelib/shapefil.h"

namespace surfit {

bool _pnts_save_shp(const d_points * pnts, const char * filename) {

	if (!pnts) {
		writelog(LOG_WARNING, "NULL pointer to points.");
		return false;
	};

	DBFHandle hDBF;
	SHPHandle hSHP;
	
	hSHP = SHPOpen( filename, "rb+" );
	hDBF = DBFOpen( filename, "rb+" );


	if (hSHP == NULL || hDBF == NULL) {

		if (hSHP)
			SHPClose( hSHP );
		if (hDBF)
			DBFClose( hDBF );


		hSHP = SHPCreate( filename, SHPT_POINT );
		
		if( hSHP == NULL ) {
			writelog(LOG_ERROR, "Unable to create:%s", filename );
			return false;
		}
		
		hDBF = DBFCreate( filename );
		
	}

	int shpType;
	SHPGetInfo(hSHP, NULL, &shpType, NULL, NULL);

	if (shpType != SHPT_POINT) {
		writelog(LOG_ERROR, "%s : Wrong shape type!", filename);
		SHPClose( hSHP );
		DBFClose( hDBF );
		return false;
	}

	int name_field = DBFGetFieldIndex( hDBF, "NAME" );
	int val_field = DBFGetFieldIndex( hDBF, "VALUE" );

	if (name_field == -1) {
		if( DBFAddField( hDBF, "NAME", FTString, 50, 0 ) == -1 )
		{
			writelog(LOG_ERROR, "DBFAddField(%s,FTString) failed.", "NAME");
			SHPClose( hSHP );
			DBFClose( hDBF );
			return false;
		}
		name_field = DBFGetFieldIndex( hDBF, "NAME" );
	}

	if (val_field == -1) {
		if( DBFAddField( hDBF, "VALUE", FTDouble, 50, 0 ) == -1 )
		{
			writelog(LOG_ERROR, "DBFAddField(%s,FTString) failed.", "VALUE");
			SHPClose( hSHP );
			DBFClose( hDBF );
			return false;
		}
		val_field = DBFGetFieldIndex( hDBF, "VALUE" );
	}

	char buf[1024];
	size_t i;
	for (i = 0; i < pnts->size(); i++) {

		double x = (*(pnts->X))(i);
		double y = (*(pnts->Y))(i);
		
		SHPObject * psObject = SHPCreateObject(SHPT_POINT,
			-1, 0, NULL, NULL, 1, 
			&x, &y, NULL, NULL);
		
		SHPComputeExtents(psObject);
		
		int pos = SHPWriteObject(hSHP, -1, psObject);
		
		SHPDestroyObject(psObject);
		
		if (pnts->names)
			DBFWriteStringAttribute(hDBF, pos, name_field, (*(pnts->names))(i) );
		else {
			sprintf(buf,"%d",i);
			DBFWriteStringAttribute(hDBF, pos, name_field, buf );
		}

		REAL val = (*(pnts->Z))(i);

		DBFWriteDoubleAttribute(hDBF, pos, val_field, val);
	}

	SHPClose( hSHP );
	DBFClose( hDBF );

	return true;
};

d_points * _pnts_load_shp(const char * filename, const char * pntsname, const char * param) {

	SHPHandle hSHP;
	DBFHandle hDBF;
	
	hSHP = SHPOpen(filename, "rb");
	if( hSHP == NULL ) {
		writelog(LOG_ERROR, "Unable to open:%s", filename );
		return NULL;
	}

	int shpType;
	int Entities;
	SHPGetInfo(hSHP, &Entities, &shpType, NULL, NULL);

	if (shpType != SHPT_POINT) {
		SHPClose( hSHP );
		writelog(LOG_ERROR, "%s : Wrong shape type!", filename);
		return NULL;
	}

	hDBF = DBFOpen(filename, "rb");
	if( hDBF == NULL ) {
		SHPClose(hSHP);
		writelog(LOG_ERROR, "Unable to open DBF for %s", filename );
		return NULL;
	}

	int val_field = DBFGetFieldIndex( hDBF, param );
	
	if (val_field == -1) 
		writelog(LOG_WARNING, "Cannot find parameter \"%s\" in DBF file", param);
		
	int dbf_records = DBFGetRecordCount( hDBF );

	Entities = MIN(dbf_records, Entities);

	vec * X = create_vec(Entities, 0, 0);
	vec * Y = create_vec(Entities, 0, 0);
	
	int i;
	for (i = 0; i < Entities; i++) {
		SHPObject * shpObject = SHPReadObject( hSHP, i );
		(*X)(i) = *(shpObject->padfX);
		(*Y)(i) = *(shpObject->padfY);
		SHPDestroyObject(shpObject);
	}

	vec * Z = create_vec(Entities, 0, 0);
	for (i = 0; i < Entities; i++) {
		if (val_field != -1)
			(*Z)(i) = DBFReadDoubleAttribute( hDBF, i, val_field );
		else
			(*Z)(i) = 0;
	}

	DBFClose( hDBF );
	SHPClose( hSHP );

	d_points * res = create_points(X, Y, Z, pntsname);
	return res;

};

}; // namespace surfit


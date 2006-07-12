
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
#include "surf_io.h"

// sstuff includes
#include "sstuff.h"

// surfit includes
#include "cntr.h"
#include "cntr_io.h"
#include "area.h"
#include "fileio.h"
#include "vec.h"
#include "variables_tcl.h"
#include "grid.h"

#include "shapelib/shapefil.h"

namespace surfit {

bool _cntr_save_shp(const d_cntr * contour, const char * filename)
{

	if (!contour->getName())
		writelog(LOG_MESSAGE,"saving contour to ERSI shape file %s", filename);
	else
		writelog(LOG_MESSAGE,"saving contour \"%s\" to ERSI shape file %s", contour->getName(), filename);

	if (!contour) {
		writelog(LOG_WARNING, "NULL pointer to curv.");
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


		hSHP = SHPCreate( filename, SHPT_POLYGONZ );
		
		if( hSHP == NULL ) {
			writelog(LOG_ERROR, "Unable to create:%s", filename );
			return false;
		}
		
		hDBF = DBFCreate( filename );
	}

	int shpType;
	SHPGetInfo(hSHP, NULL, &shpType, NULL, NULL);

	if (shpType != SHPT_POLYGONZ) {
		writelog(LOG_ERROR, "%s : Wrong shape type!", filename);
		SHPClose( hSHP );
		DBFClose( hDBF );
		return false;
	}

	int name_field = DBFGetFieldIndex( hDBF, "NAME" );

	if (name_field == -1) {
		if( DBFAddField( hDBF, "NAME", FTString, 50, 0 ) == -1 )
		{
			writelog(LOG_ERROR, "DBFAddField(%s,FTString) failed.", "NAME");
			SHPClose( hSHP );
			DBFClose( hDBF );
			return false;
		}
		name_field = DBFGetFieldIndex( hDBF, "NAME" );
	};

	SHPObject * psObject = SHPCreateObject(SHPT_POLYGONZ,
			-1, 0, NULL, NULL, contour->size(), 
			contour->X->begin(), contour->Y->begin(), contour->Z->begin(), NULL);

	SHPComputeExtents(psObject);
		
	int pos = SHPWriteObject(hSHP, -1, psObject);
		
	SHPDestroyObject(psObject);

	if (contour->getName())
		DBFWriteStringAttribute(hDBF, pos, name_field, contour->getName() );

	SHPClose( hSHP );
	DBFClose( hDBF );

	return true;
};

d_cntr * _cntr_load_shp(const char * filename, const char * cntrname) {

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

	if (shpType != SHPT_POLYGONZ) {
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

	int name_field = DBFGetFieldIndex( hDBF, "NAME" );
	
	if (name_field == -1) {
		SHPClose( hSHP );
		DBFClose( hDBF );
		writelog(LOG_ERROR, "Cannot find parameter \"%s\" in DBF file", "NAME");
		return NULL;
	};

	int dbf_records = DBFGetRecordCount( hDBF );

	Entities = MIN(dbf_records, Entities);

	int i;
	for (i = 0; i < Entities; i++) {
		const char * name = DBFReadStringAttribute( hDBF, i, name_field );
		if (strcmp(cntrname, name) == 0)
			break;
	}

	if (i == Entities) {
		SHPClose( hSHP );
		DBFClose( hDBF );
		writelog(LOG_ERROR, "Cannot find cntre named \"%s\"", cntrname);
		return NULL;
	}

	SHPObject * shpObject = SHPReadObject( hSHP, i );

	if (shpObject->nParts != -1) {
		SHPDestroyObject(shpObject);
		DBFClose( hDBF );
		SHPClose( hSHP );
		writelog(LOG_ERROR, "surfit supports only contours with mParts == 1");
		return NULL;
	}

	vec * X = create_vec(shpObject->nVertices,0,0);
	vec * Y = create_vec(shpObject->nVertices,0,0);
	vec * Z = create_vec(shpObject->nVertices,0,0);

	for (i = 0; i < shpObject->nVertices; i++) {
		(*X)(i) = *(shpObject->padfX + i);
		(*Y)(i) = *(shpObject->padfY + i);
		(*Z)(i) = *(shpObject->padfZ + i);
	}
	
	SHPDestroyObject(shpObject);

	DBFClose( hDBF );
	SHPClose( hSHP );

	d_cntr * res = create_cntr(X, Y, Z, cntrname);
	
	return res;

};

bool _cntrs_load_shp(const char * filename) {

	SHPHandle hSHP;
	DBFHandle hDBF;
	
	hSHP = SHPOpen(filename, "rb");
	if( hSHP == NULL ) {
		writelog(LOG_ERROR, "Unable to open:%s", filename );
		return false;
	}

	int shpType;
	int Entities;
	SHPGetInfo(hSHP, &Entities, &shpType, NULL, NULL);

	if (shpType != SHPT_POLYGONZ) {
		SHPClose( hSHP );
		writelog(LOG_ERROR, "%s : Wrong shape type!", filename);
		return false;
	}

	hDBF = DBFOpen(filename, "rb");
	if( hDBF == NULL ) {
		SHPClose(hSHP);
		writelog(LOG_ERROR, "Unable to open DBF for %s", filename );
		return false;
	}

	int name_field = DBFGetFieldIndex( hDBF, "NAME" );
	int dbf_records = DBFGetRecordCount( hDBF );

	Entities = MIN(dbf_records, Entities);

	int i, j;
	for (i = 0; i < Entities; i++) {
		SHPObject * shpObject = SHPReadObject( hSHP, i );

		if (shpObject->nParts > 1) {
			SHPDestroyObject(shpObject);
			continue;
		}
			
		vec * X = create_vec(shpObject->nVertices,0,0);
		vec * Y = create_vec(shpObject->nVertices,0,0);
		vec * Z = create_vec(shpObject->nVertices,0,0);

		const char * name = NULL;
		if (name_field != -1)
			name = DBFReadStringAttribute( hDBF, i, name_field );
		
		for (j = 0; j < shpObject->nVertices; j++) {
			(*X)(j) = *(shpObject->padfX + j);
			(*Y)(j) = *(shpObject->padfY + j);
			(*Z)(j) = *(shpObject->padfZ + j);
		}
		
		d_cntr * res = create_cntr(X, Y, Z, name);

		surfit_cntrs->push_back(res);
	}

	DBFClose( hDBF );
	SHPClose( hSHP );

	return true;

};

};


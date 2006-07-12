
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
#include "boolvec.h"
#include "vec.h"

// surfit includes
#include "curv.h"
#include "curv_io.h"
#include "area.h"
#include "fileio.h"
#include "variables_tcl.h"
#include "grid.h"

#include "shapelib/shapefil.h"

namespace surfit {

bool _area_save_shp(const d_area * area, const char * filename) {
	if (!area) {
		writelog(LOG_WARNING, "NULL pointer to area.");
		return false;
	};

	if (!area->getName())
		writelog(LOG_MESSAGE,"saving area to ERSI shape file %s", filename);
	else
		writelog(LOG_MESSAGE,"saving area \"%s\" to ERSI shape file %s", area->getName(), filename);

	DBFHandle hDBF;
	SHPHandle hSHP;
	
	hSHP = SHPOpen( filename, "rb+" );
	hDBF = DBFOpen( filename, "rb+" );

	if (hSHP == NULL || hDBF == NULL) {

		if (hSHP)
			SHPClose( hSHP );
		if (hDBF)
			DBFClose( hDBF );


		hSHP = SHPCreate( filename, SHPT_POLYGON );
		
		if( hSHP == NULL ) {
			writelog(LOG_ERROR, "Unable to create:%s", filename );
			return false;
		}
		
		hDBF = DBFCreate( filename );
	}

	int shpType;
	SHPGetInfo(hSHP, NULL, &shpType, NULL, NULL);

	if (shpType != SHPT_POLYGON) {
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

	int nParts = area->size();
	
	int * PartStart = (int*)malloc( nParts * sizeof(int) );
	int * PartType = (int*)malloc( nParts * sizeof(int) );

	size_t size = 0;
	int i;
	for (i = 0; i < nParts; i++) {
		const d_curv * crv = area->get_curv(i);
		size += crv->size();
	}

	vec * X = create_vec(size, 0, 0);
	vec * Y = create_vec(size, 0, 0);

	size_t pos = 0;
	for (i = 0; i < nParts; i++) {
		*(PartStart+i) = pos;
		const d_curv * crv = area->get_curv(i);
		bool inside = area->get_curv_orient(i);
		if (inside)
			*(PartType) = SHPP_INNERRING;
		else
			*(PartType) = SHPP_OUTERRING;
		
		size_t j;
		for (j = 0; j < crv->size(); j++) {
			(*X)(pos) = (*(crv->X))(j);
			(*Y)(pos) = (*(crv->Y))(j);
			pos++;
		}
	}

	SHPObject * psObject = SHPCreateObject(SHPT_POLYGON,
			-1, nParts, PartStart, PartType, X->size(), 
			X->begin(), Y->begin(), NULL, NULL);

	SHPComputeExtents(psObject);
		
	pos = SHPWriteObject(hSHP, -1, psObject);
		
	SHPDestroyObject(psObject);

	free(PartStart);
	free(PartType);

	X->release();
	Y->release();

	if (area->getName())
		DBFWriteStringAttribute(hDBF, pos, name_field, area->getName() );

	SHPClose( hSHP );
	DBFClose( hDBF );	

	return true;

};

d_area * shape2area(SHPObject * shpObject, const char * areaname) {
	std::vector<d_curv *> * curvs = new std::vector<d_curv *>();
	boolvec * orients = create_boolvec();

	int nVertices = shpObject->nVertices;
	int nParts = shpObject->nParts;
	int i,j;
	
	if (nParts == 1) {
		vec * X = create_vec(nVertices, 0, 0);
		vec * Y = create_vec(nVertices, 0, 0);
		
		for (j = 0; j < nVertices; j++) {
			(*X)(j) = *(shpObject->padfX + j);
			(*Y)(j) = *(shpObject->padfY + j);
		}
		d_curv * crv = create_curv(X, Y);
		curvs->push_back(crv);
		orients->push_back(true);
	} else {
		for (i = 0; i < nParts; i++) {
			int from = *(shpObject->panPartStart + i);
			int to = nVertices;
			if (i < nParts-1)
				to = *(shpObject->panPartStart + i+1);
			int size = to-from;
			if (size == 0)
				continue;
			vec * X = create_vec(size, 0, 0);
			vec * Y = create_vec(size, 0, 0);
			int j;
			for (j = 0; j < size; j++) {
				(*X)(j) = *(shpObject->padfX + j + from);
				(*Y)(j) = *(shpObject->padfY + j + from);
			}
			int type = *(shpObject->panPartType + i);
			bool orient = true;
			if (type == SHPP_OUTERRING)
				orient = false;

			d_curv * crv = create_curv(X, Y);
			curvs->push_back(crv);
			orients->push_back(orient);
		}
	}

	d_area * res = create_area(curvs, orients, areaname);

	return res;
};

d_area * _area_load_shp(const char * filename, const char * areaname) {

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

	if (shpType != SHPT_POLYGON) {
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
		if (strcmp(areaname, name) == 0)
			break;
	}

	if (i == Entities) {
		SHPClose( hSHP );
		DBFClose( hDBF );
		writelog(LOG_ERROR, "Cannot find area named \"%s\"", areaname);
		return NULL;
	}
	
	SHPObject * shpObject = SHPReadObject( hSHP, i );

	d_area * res = shape2area(shpObject, areaname);

	SHPDestroyObject(shpObject);

	DBFClose( hDBF );
	SHPClose( hSHP );

	return res;
};

bool _areas_load_shp(const char * filename) {

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

	if (shpType != SHPT_POLYGON) {
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

	int i;
	for (i = 0; i < Entities; i++) {
		const char * name = NULL;
		if (name_field != -1)
			name = DBFReadStringAttribute( hDBF, i, name_field );
		
		SHPObject * shpObject = SHPReadObject( hSHP, i );
		
		d_area * res = shape2area(shpObject, name);

		surfit_areas->push_back(res);
		
		SHPDestroyObject(shpObject);
	}

	DBFClose( hDBF );
	SHPClose( hSHP );

	return true;

};

};


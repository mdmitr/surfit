
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
#include "interp.h"

// surfit includes
#include "cntr.h"
#include "cntr_io.h"
#include "area.h"
#include "fileio.h"
#include "vec.h"
#include "variables_tcl.h"
#include "grid.h"

#include <float.h>
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

	REAL minz, maxz;
	contour->getMinMaxZ(minz, maxz);

	bool use_arcz = (maxz != minz);

	DBFHandle hDBF;
	SHPHandle hSHP;
	
	hSHP = SHPOpen( filename, "rb+" );
	hDBF = DBFOpen( filename, "rb+" );

	if (hSHP == NULL || hDBF == NULL) {

		if (hSHP)
			SHPClose( hSHP );
		if (hDBF)
			DBFClose( hDBF );


		if (use_arcz)
			hSHP = SHPCreate( filename, SHPT_ARCZ );
		else
			hSHP = SHPCreate( filename, SHPT_ARC );
		
		if( hSHP == NULL ) {
			writelog(LOG_ERROR, "Unable to create:%s", filename );
			return false;
		}
		
		hDBF = DBFCreate( filename );
	}

	int shpType;
	SHPGetInfo(hSHP, NULL, &shpType, NULL, NULL);
	
	if (use_arcz) {
		if (shpType != SHPT_ARCZ) {
			writelog(LOG_ERROR, "%s : Wrong shape type!", filename);
			SHPClose( hSHP );
			DBFClose( hDBF );
			return false;
		} 
	} else {
		if (shpType != SHPT_ARC) {
			writelog(LOG_ERROR, "%s : Wrong shape type!", filename);
			SHPClose( hSHP );
			DBFClose( hDBF );
			return false;
		}
	}

	int name_field = DBFGetFieldIndex( hDBF, "NAME" );
	int z_field = INT_MAX;
	if (use_arcz == false)
		z_field = DBFGetFieldIndex( hDBF, "Z" );

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

	if (z_field == -1) {
		if( DBFAddField( hDBF, "Z", FTDouble, 25, 5 ) == -1 )
		{
			writelog(LOG_ERROR, "DBFAddField(%s,FTDouble) failed.", "Z");
			SHPClose( hSHP );
			DBFClose( hDBF );
			return false;
		}
		z_field = DBFGetFieldIndex( hDBF, "Z" );
	};

	std::vector<REAL> data_x(contour->size());
	std::vector<REAL> data_y(contour->size());
	std::vector<REAL> data_z(contour->size());
	std::copy(contour->X->begin(), contour->X->end(), data_x.begin());
	std::copy(contour->Y->begin(), contour->Y->end(), data_y.begin());
	std::copy(contour->Z->begin(), contour->Z->end(), data_z.begin());

	SHPObject * psObject = NULL;
	if (use_arcz) {
		psObject = SHPCreateObject(SHPT_ARCZ,
					   -1, 0, NULL, NULL, contour->size(), 
					   &*(data_x.begin()), &*(data_y.begin()), &*(data_z.begin()), NULL);
	} else {
		psObject = SHPCreateObject(SHPT_ARC,
					   -1, 0, NULL, NULL, contour->size(), 
					   &*(data_x.begin()), &*(data_y.begin()), NULL, NULL);
	}

	SHPComputeExtents(psObject);
		
	int pos = SHPWriteObject(hSHP, -1, psObject);
		
	SHPDestroyObject(psObject);

	if (contour->getName())
		DBFWriteStringAttribute(hDBF, pos, name_field, contour->getName() );
	if (use_arcz == false)
		DBFWriteDoubleAttribute(hDBF, pos, z_field, minz);

	SHPClose( hSHP );
	DBFClose( hDBF );

	return true;
	
};

bool _cntr_load_shp(const char * filename, const char * cntrname, const char * zfield) {

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

	if (zfield == NULL) 
	{
		if ((shpType != SHPT_POLYGONZ) && (shpType != SHPT_ARCZ)) {
			SHPClose( hSHP );
			writelog(LOG_ERROR, "%s : Wrong shape type! Expecting SHPT_POLYGONZ or SHPT_ARCZ", filename);
			return false;
		}
	} else {
		if ((shpType != SHPT_POLYGON) && (shpType != SHPT_ARC)) {
			SHPClose( hSHP );
			writelog(LOG_ERROR, "%s : Wrong shape type! Expecting SHPT_POLYGON or SHPT_ARC", filename);
			return false;
		}
	}

	hDBF = DBFOpen(filename, "rb");
	if( hDBF == NULL ) {
		SHPClose(hSHP);
		writelog(LOG_ERROR, "Unable to open DBF for %s", filename );
		return false;
	}

	int name_field = DBFGetFieldIndex( hDBF, "NAME" );
	if (name_field == -1)
		writelog(LOG_WARNING,"can't find field named \"NAME\"");
	int z_field = INT_MAX;
	if (zfield != NULL)
		z_field = DBFGetFieldIndex( hDBF, zfield );

	if (z_field == -1) {
		writelog(LOG_ERROR,"can't find field named \"%s\"", zfield);
		DBFClose( hDBF );
		SHPClose( hSHP );
		return false;
	}
	int dbf_records = DBFGetRecordCount( hDBF );

	Entities = MIN(dbf_records, Entities);

	int i, j;
	for (i = 0; i < Entities; i++) {
		SHPObject * shpObject = SHPReadObject( hSHP, i );

		if (shpObject->nParts > 1) {
			SHPDestroyObject(shpObject);
			continue;
		}

		REAL zval = FLT_MAX;
		if ((z_field != -1) && (z_field != INT_MAX))
			zval = DBFReadDoubleAttribute( hDBF, i, z_field );
			
		const char * name = NULL;
		if (name_field != -1) {
			name = DBFReadStringAttribute( hDBF, i, name_field );
			if (cntrname != NULL) {
				if ( StringMatch(cntrname, name) == false )
					continue;
			}
		}
		

		writelog(LOG_MESSAGE,"loading contour \"%s\" from ESRI shape file %s",
			name?name:"noname", filename);

		vec * X = create_vec(shpObject->nVertices,0,0);
		vec * Y = create_vec(shpObject->nVertices,0,0);
		vec * Z = create_vec(shpObject->nVertices,0,0);
		
		for (j = 0; j < shpObject->nVertices; j++) {
			(*X)(j) = *(shpObject->padfX + j);
			(*Y)(j) = *(shpObject->padfY + j);
			if (zval != FLT_MAX)
				(*Z)(j) = zval;
			else
				(*Z)(j) = *(shpObject->padfZ + j);
		}
		
		d_cntr * res = create_cntr(X, Y, Z, name);
		surfit_cntrs->push_back(res);
		SHPDestroyObject(shpObject);
	}

	DBFClose( hDBF );
	SHPClose( hSHP );

	return true;

};

};



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
#include "area_internal.h"
#include "area.h"
#include "curv.h"
#include "curv_internal.h"
#include "boolvec.h"
#include "datafile.h"
#include "curv_internal.h"

#include <errno.h>
#include <vector>

#include "shapelib/shapefil.h"

namespace surfit {

d_area * _area_read(const char * filename, const char * areaname,
		    int col1, int col2, int skip_lines,
		    int grow_by, const char * mask) 
{
	d_curv * crv = _curv_read(filename, areaname, col1, col2, skip_lines, grow_by, mask);
	if (crv == NULL)
		return NULL;

	d_area * res = create_area(crv, 1, areaname);
	return res;
};

d_area * _area_read_bln(const char * filename, const char * areaname) {
	
	d_area * area_res = NULL;
	std::vector<d_curv *> * area_data = new std::vector<d_curv *>;
	boolvec * orients = create_boolvec();

	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "loading from BLN: file error.");
		fclose(file);
		return false;
	}

	bool res = false;

	int orient = 1;
	d_curv * crv = _curv_read_bln(file, orient);
	while (crv != NULL) {
		res = true;
		crv->close();
		area_data->push_back(crv);
		orients->push_back(orient != 0);
		orient = 1;
		crv = _curv_read_bln(file, orient);
	}

	fclose(file);

	if (area_data->size() == 0)
		return area_res;

	area_res = create_area(area_data, orients, areaname);
	return area_res;
};

bool _area_write(const d_area * area, const char * filename, const char * mask) {
	if (!area)
		return false;
	if (area->size() != 1) {
		writelog(LOG_ERROR,"area consists > 1 curves!");
		return false;
	}
	return _curv_write( (*(area->curves))[0], filename, mask);
};

bool _area_write_bln(const d_area * area, const char * filename) {
	
	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "writing BLN: file error.");
		fclose(file);
		return false;
	}

	if (area->getName())
		writelog(LOG_MESSAGE,"writing area (%s) to bln file %s", area->getName(), filename);
	else 
		writelog(LOG_MESSAGE,"writing noname area to bln file %s", filename);

	bool res = true;

	int i;
	for (i = 0; i < area->size(); i++) {
		const d_curv * crv = area->get_curv(i);
		res = _curv_write_bln(crv, file, area->get_curv_orient(i));
		if (res == false)
			break;
	}
	fclose(file);

	return res;

};

bool _area_save(const d_area * area, const char * filename) {
	if (!area) {
		writelog(LOG_WARNING, "NULL pointer to area.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition())
		return false;

	bool res = _area_save_df(area, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _area_save_df(const d_area * area, datafile * df) {

	if (!area->getName())
		writelog(LOG_MESSAGE,"saving area to file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"saving area \"%s\" to file %s", area->getName(), df->get_filename());
	
	bool res = true;
	bool op;

	op = df->writeTag("area");					 res = (op && res);
	if (area->getName()) {
		op = df->writeString("name", area->getName());		 res = (op && res);
	}
	int i;
	for (i = 0; i < area->size(); i++) {
		const d_curv * crv = area->get_curv(i);
		op = _curv_save_df(crv, df);				 res = (op && res);
	}
	
	op = df->writeBoolArray("orients", area->orients); res = (op && res);

	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

d_area * _area_load_df(datafile * df, const char * areaname) {

	if (!areaname) 
		writelog(LOG_MESSAGE,"loading area with no name from file %s",df->get_filename());
	else 
		writelog(LOG_MESSAGE,"loading area \"%s\" from file %s",areaname,df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "area_load : wrong datafile format";

	bool err = false;
	d_area * area = NULL;
	std::vector<d_curv *> * area_data = new std::vector<d_curv *>;
	//boolvec * area_orients = new boolvec;
	boolvec * orients = NULL;
	char * name = NULL;
	
	bool loaded = false;
	
	while ( !loaded ) {
		
		if (df->findTag("area")) {
			
			df->skipTagName();
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						name = (char*)malloc(strlen(df->getWord())+1);
						strcpy(name,df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}

				if ( df->isWord("tag") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord("curv") ) {
						d_curv * crv = NULL;
						if ( !_curv_load_df_tag_readed(df, crv) ) goto exit;
						if (crv)
							area_data->push_back(crv);
						goto cont;
					}
					if (!df->skipToEndTag()) goto exit;
					goto cont;
				}

				if ( df->isWord("array") ) {
					if (!df->readWord()) goto exit;
					if ( df->isWord("bool") ) {
						if (!df->readWord()) goto exit;
						if ( df->isWord("orients") ) {
							df->readBoolArray(orients);
							goto cont;
						}
					}
					if ( !df->skipArray(false) ) goto exit;
				}
								
				if ( !df->skip(false) ) goto exit;
				goto cont;
cont:
				if ( !df->readWord() ) goto exit;
				continue;
			}
		} else {
			goto exit;
		}
				
		if (err) {
			free(name);
			return false;
		}
		
		area = create_area(area_data, orients, name);
		free(name);
		
		if (!areaname) {
			return area;
		} else {
			if (area->getName()) {
				if (strcmp(area->getName(),areaname) == 0) {
					return area;
				}
			}
			if (area)
				area->release();
			area = NULL;
			area_data = NULL;
			area_data = new std::vector<d_curv *>;
			orients = NULL;
		}
		
	}
	
	return area;

exit:

	if (!areaname)
		writelog(LOG_ERROR, "area_load : this file have no area");
	else 
		writelog(LOG_ERROR, "area_load : this file have no area named %s", areaname);
	return NULL;

};

d_area * _area_load(const char * filename, const char * areaname) {

	datafile * df = new datafile(filename, DF_MODE_READ);
	
	d_area * arealine = _area_load_df(df, areaname);

	if (!arealine)
		goto exit;

	delete df;
	return arealine;
	
exit:
	if (arealine)
		arealine->release(); 
	delete df;
	return NULL;

};

void _area_info(const d_area * arealine) {
	if (!arealine) {
		writelog(LOG_WARNING, "_area_info : NULL pointer given");
		return;
	}
	if (arealine->getName()) {
		writelog(LOG_MESSAGE,"area (%s)",arealine->getName());
	} else {
		writelog(LOG_MESSAGE,"area noname");	
	}
};

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

}; // namespace surfit;


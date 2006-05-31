
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

#include "cntr.h"
#include "cntr_internal.h"

#include "shapelib/shapefil.h"

namespace surfit {

d_cntr * _cntr_read(const char * filename, const char * cntrname,
		    int col1, int col2, int col3, int skip_lines,
		    int grow_by, const char * mask) 
{
	vec * vcol1;
	vec * vcol2;
	vec * vcol3;

	if (cntrname)
		writelog(LOG_MESSAGE,"reading contour \"%s\" from file %s", cntrname, filename);
	else 
		writelog(LOG_MESSAGE,"reading contour from file %s", filename);

	if (!three_columns_read(filename, col1, col2, col3, skip_lines, mask, grow_by,
		vcol1, vcol2, vcol3))
		return NULL;

	d_cntr * res = create_cntr(vcol1, vcol2, vcol3, cntrname);

	return res;
};

bool _cntr_write(const d_cntr * cntrline, const char * filename, const char * mask) {
	if (!cntrline)
		return false;
	return three_columns_write(filename, mask,
		                   cntrline->X, cntrline->Y, cntrline->Z);
};

bool _cntr_save(const d_cntr * contour, const char * filename) {
	if (!contour) {
		writelog(LOG_WARNING, "NULL pointer to cntr.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition())
		return false;

	bool res = _cntr_save_df(contour, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _cntr_save_df(const d_cntr * contour, datafile * df) {

	if (!contour->getName())
		writelog(LOG_MESSAGE,"saving cntr to file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"saving cntr \"%s\" to file %s", contour->getName(), df->get_filename());
	
	
	if (contour->size() == 0) {
		writelog(LOG_WARNING,"Empty contour");
		return false;
	}

	bool res = true;
	bool op;

	op = df->writeTag("cntr");				res = (op && res);
	if (contour->getName()) {
		op = df->writeString("name",contour->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", contour->X); res = (op && res);
	op = df->writeRealArray("y", contour->Y); res = (op && res);
	op = df->writeRealArray("z", contour->Z); res = (op && res);
	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

d_cntr * _cntr_load_df(datafile * df, const char * cntrname) {

	if (!cntrname)
		writelog(LOG_MESSAGE,"loading cntr from file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"loading cntr \"%s\" from file %s", cntrname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "cntr_load : wrong datafile format";

	d_cntr * cntrline = create_cntr(NULL, NULL, NULL);
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("cntr")) {
			
			df->skipTagName();
			
			vec * X = NULL;
			vec * Y = NULL;
			vec * Z = NULL;
			
			if (!df->readWord()) goto exit;
			
			while ( !df->isWord("endtag" ) ) {
				if ( df->isWord("array") ) {
					// read array type
					if (!df->readWord()) goto exit;
					
					if ( df->isWord(REAL_NAME) ) {
						
						// read name
						if (!df->readWord()) goto exit;
						
						if ( df->isWord("x") ) {
							if ( !df->readRealArray(X) ) goto exit;
							cntrline->X = X;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("y") ) {
							if ( !df->readRealArray(Y) ) goto exit;
							cntrline->Y = Y;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( df->isWord("z") ) {
							if ( !df->readRealArray(Z) ) goto exit;
							cntrline->Z = Z;
							if ( !df->readWord() ) goto exit;
							continue;
						}
						if ( !df->skipRealArray() ) goto exit;
						if ( !df->readWord() ) goto exit;		
						continue;
					}
					
					if ( !df->skipArray(false) ) goto exit;
				}
				if ( df->isWord("char") ) {
					// read char name
					if (!df->readWord()) goto exit;
					if ( df->isWord("name") ) {
						if ( !df->readWord() ) goto exit;
						cntrline->setName(df->getWord());
						if (!df->readWord()) goto exit;
						continue;
					}
				}
				
				if ( !df->skip(false) ) goto exit;
				if ( !df->readWord() ) goto exit;
				
			}
			
			// check condition here
			if (
				(cntrline->X != NULL) &&
				(cntrline->Y != NULL) &&
				(cntrline->Z != NULL) &&
				((cntrline->X->size()) == (cntrline->Y->size())) &&
				((cntrline->X->size()) == (cntrline->Z->size()))
		           ) 
			{
				if (!cntrname) {
					return cntrline;
				} else {
					if (cntrline->getName()) {
						if ( strcmp(cntrline->getName(),cntrname) == 0 ) {
							return cntrline;
						} else {
							if (cntrline)
								cntrline->release();
							cntrline = create_cntr(NULL, NULL, NULL);
						}
					}
				}
			}
		} else {
			if (!cntrname)
				writelog(LOG_ERROR, "cntr_load : this file have no cntrs");
			else
				writelog(LOG_ERROR, "cntr_load : this file have no cntr with name %s", cntrname);
			if (cntrline)
				cntrline->release();
			return NULL;
		}
	};

exit:
	if (cntrline)
		cntrline->release(); 
	writelog(LOG_ERROR, error);
	return NULL;

};

d_cntr * _cntr_load(const char * filename, const char * cntrname) {

	datafile * df = new datafile(filename, DF_MODE_READ);
	
	d_cntr * cntrline = _cntr_load_df(df, cntrname);

	if (!cntrline)
		goto exit;

	delete df;
	return cntrline;
	
exit:
	if (cntrline)
		cntrline->release(); 
	delete df;
	return NULL;

};

void _cntr_info(const d_cntr * cntrline) {
	if (!cntrline) {
		writelog(LOG_WARNING, "_cntr_info : NULL pointer given");
		return;
	}
	if (cntrline->getName()) {
		writelog(LOG_MESSAGE,"cntr (%s)",cntrline->getName());
	} else {
		writelog(LOG_MESSAGE,"cntr noname");	
	}
};

void _add_surfit_cntrs(d_cntr * contour) {
	if (!contour)
		return;
	surfit_cntrs->push_back(contour);
};

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

}; // namespace surfit;


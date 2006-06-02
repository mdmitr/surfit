
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

#include "sstuff.h"
#include "fileio.h"
#include "datafile.h"
#include "read_txt.h"
#include "vec.h"
#include "geom_alg.h"

#include "curv.h"
#include "curv_internal.h"
#include "grid.h"

#include "shapelib/shapefil.h"

namespace surfit {

d_curv * _curv_read(const char * filename, const char * curvname,
		    int col1, int col2, int skip_lines,
		    int grow_by, const char * mask) 
{
	vec * vcol1;
	vec * vcol2;

	if (curvname)
		writelog(LOG_MESSAGE,"reading curve \"%s\" from file %s", curvname, filename);
	else 
		writelog(LOG_MESSAGE,"reading curve from file %s", filename);

	if (!two_columns_read(filename, col1, col2, skip_lines, mask, grow_by,
			      vcol1, vcol2))
		return NULL;

	d_curv * res = create_curv(vcol1, vcol2, curvname);

	if (curvname == NULL) {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;
};

d_curv * _curv_read_bln(FILE * file, int & orient)
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
	d_curv * res = NULL;
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
			token = strtok( NULL, seps );
		}
	};

	if (X->size() != Y->size())
		goto bad_file;

	res = create_curv(X, Y, name);
	return res;


bad_file:
	free(name);
	if (X)
		X->release();
	if (Y)
		Y->release();
	return NULL;
};

bool _curv_write(const d_curv * curvline, const char * filename, const char * mask) {
	if (!curvline)
		return false;
	return two_columns_write(filename, mask,
				 curvline->X, curvline->Y);
};

bool _curv_write_bln(const d_curv * crv, FILE * file, int orient) {

	int size = crv->size();
	
	if (size == 0)
		return false;

	int i;

	if (crv->getName()) {
		if ( fprintf(file, "%d,%d \"%s\"\n",size, orient, crv->getName()) <= 0 )
			goto bad_write_bln;
	} else {
		if ( fprintf(file, "%d,%d\n",size, orient, crv->getName()) <= 0 )
			goto bad_write_bln;
	}

	for (i = 0; i < size; i++) {
		if ( fprintf(file, "%g,%g\n", (*(crv->X))(i), (*(crv->Y))(i)) <= 0)
			goto bad_write_bln;
	}

	return true;

bad_write_bln:
	return false;
};

bool _curv_save(const d_curv * contour, const char * filename) {
	if (!contour) {
		writelog(LOG_WARNING, "NULL pointer to curv.");
		return false;
	};

	datafile *df = new datafile(filename, DF_MODE_WRITE); // write
	if (!df->condition())
		return false;

	bool res = _curv_save_df(contour, df);

	bool op = df->writeEof(); res = (op && res);
	
	delete df;
	return res;
};

bool _curv_save_df(const d_curv * contour, datafile * df) {

	if (!contour->getName())
		writelog(LOG_MESSAGE,"saving curv to file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"saving curv \"%s\" to file %s", contour->getName(), df->get_filename());
	
	if (contour->size() == 0) {
		writelog(LOG_WARNING, "Empty contour");
		return false;
	};

	bool res = true;
	bool op;

	op = df->writeTag("curv");				res = (op && res);
	if (contour->getName()) {
		op = df->writeString("name",contour->getName());  res = (op && res);
	}
	op = df->writeRealArray("x", contour->X); res = (op && res);
	op = df->writeRealArray("y", contour->Y); res = (op && res);
	op = df->writeEndTag();						 res = (op && res);
		
	return res;
};

bool _curv_save_shp(const d_curv * contour, const char * filename) {

	
	if (!contour->getName())
		writelog(LOG_MESSAGE,"saving curv to ERSI shape file %s", filename);
	else
		writelog(LOG_MESSAGE,"saving curv \"%s\" to ERSI shape file %s", contour->getName(), filename);

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


		hSHP = SHPCreate( filename, SHPT_ARC );
		
		if( hSHP == NULL ) {
			writelog(LOG_ERROR, "Unable to create:%s", filename );
			return false;
		}
		
		hDBF = DBFCreate( filename );
	}

	int shpType;
	SHPGetInfo(hSHP, NULL, &shpType, NULL, NULL);

	if (shpType != SHPT_ARC) {
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

	SHPObject * psObject = SHPCreateObject(SHPT_ARC,
			-1, 0, NULL, NULL, contour->size(), 
			contour->X->begin(), contour->Y->begin(), NULL, NULL);

	SHPComputeExtents(psObject);
		
	int pos = SHPWriteObject(hSHP, -1, psObject);
		
	SHPDestroyObject(psObject);

	if (contour->getName())
		DBFWriteStringAttribute(hDBF, pos, name_field, contour->getName() );

	SHPClose( hSHP );
	DBFClose( hDBF );

	return true;
};

d_curv * _curv_load_shp(const char * filename, const char * curvname) {

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

	if (shpType != SHPT_ARC) {
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
		if (strcmp(curvname, name) == 0)
			break;
	}

	if (i == Entities) {
		SHPClose( hSHP );
		DBFClose( hDBF );
		writelog(LOG_ERROR, "Cannot find curve named \"%s\"", curvname);
		return NULL;
	}

	SHPObject * shpObject = SHPReadObject( hSHP, i );

	if (shpObject->nParts != -1) {
		SHPDestroyObject(shpObject);
		DBFClose( hDBF );
		SHPClose( hSHP );
		writelog(LOG_ERROR, "surfit supports only curves with mParts == 1");
		return NULL;
	}

	vec * X = create_vec(shpObject->nVertices,0,0);
	vec * Y = create_vec(shpObject->nVertices,0,0);

	for (i = 0; i < shpObject->nVertices; i++) {
		(*X)(i) = *(shpObject->padfX + i);
		(*Y)(i) = *(shpObject->padfY + i);
	}
	
	SHPDestroyObject(shpObject);

	DBFClose( hDBF );
	SHPClose( hSHP );

	d_curv * res = create_curv(X, Y, curvname);
	
	return res;

};

bool _curvs_load_shp(const char * filename) {

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

	if (shpType != SHPT_ARC) {
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

		if (shpObject->nParts != 1) {
			SHPDestroyObject(shpObject);
			continue;
		}
			
		vec * X = create_vec(shpObject->nVertices,0,0);
		vec * Y = create_vec(shpObject->nVertices,0,0);

		const char * name = NULL;
		if (name_field != -1)
			name = DBFReadStringAttribute( hDBF, i, name_field );
		
		for (j = 0; j < shpObject->nVertices; j++) {
			(*X)(j) = *(shpObject->padfX + j);
			(*Y)(j) = *(shpObject->padfY + j);
		}
		
		d_curv * res = create_curv(X, Y, name);

		surfit_curvs->push_back(res);
	}

	DBFClose( hDBF );
	SHPClose( hSHP );

	return true;
};

bool _curv_load_df_tag_readed(datafile * df, d_curv *& crv) {
	
	crv = create_curv(NULL, NULL);

	vec * X = NULL;
	vec * Y = NULL;
	char error[] = "curv_load : wrong datafile format";
	
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
					crv->X = X;
					if ( !df->readWord() ) goto exit;
					continue;
				}
				if ( df->isWord("y") ) {
					if ( !df->readRealArray(Y) ) goto exit;
					crv->Y = Y;
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
				crv->setName(df->getWord());
				if (!df->readWord()) goto exit;
				continue;
			}
		}
		
		if ( !df->skip(false) ) goto exit;
		if ( !df->readWord() ) goto exit;
		
	}
	
	// check condition here
	if (
		(crv->X != NULL) &&
		(crv->Y != NULL) &&
		((crv->X->size()) == (crv->Y->size()))
	   ) 
	{
		return true;
	} else {
		if (crv)
			crv->release();
		return false;
	}

exit:
	if (crv)
		crv->release(); 
	writelog(LOG_ERROR, error);
	return false;

};

d_curv * _curv_load_df(datafile * df, const char * curvname) {

	if (!curvname)
		writelog(LOG_MESSAGE,"loading curv from file %s", df->get_filename());
	else
		writelog(LOG_MESSAGE,"loading curv \"%s\" from file %s", curvname, df->get_filename());

	if (!df->condition()) {
		return NULL;
	}

	char error[] = "curv_load : wrong datafile format";

	d_curv * crv = NULL;
	
	bool loaded = false;
	
	while (!loaded) {
		
		if (df->findTag("curv")) {
			
			df->skipTagName();

			if (!_curv_load_df_tag_readed(df, crv)) {
				if (crv == NULL)
					crv->release();
				return NULL;
			};

			if (!curvname) {
				return crv;
			}
			
			if (!crv->getName()) {
				if (!curvname)
					return crv;
				if (strlen(curvname) == 0)
					return crv;
				
				if (crv)
					crv->release();
				crv = NULL;
				continue;
			};
			
			if ( strcmp(curvname,crv->getName()) == 0 ) {
				return crv;
			}
			
			if (crv)
				crv->release();
			crv = NULL;
			
		} else {
			if (!curvname)
				writelog(LOG_ERROR, "curv_load : this file have no curv");
			else
				writelog(LOG_ERROR, "curv_load : this file have no curv with name %s", curvname);
			if (crv)
				crv->release();
			return NULL;
		}
			
	};

	if (crv)
		crv->release();
	return NULL;
};

d_curv * _curv_load(const char * filename, const char * curvname) {

	datafile * df = new datafile(filename, DF_MODE_READ);
	
	d_curv * curvline = _curv_load_df(df, curvname);

	if (!curvline)
		goto exit;

	delete df;
	return curvline;
	
exit:
	if (curvline)
		curvline->release(); 
	delete df;
	return NULL;

};

void _curv_info(const d_curv * curvline) {
	if (!curvline) {
		writelog(LOG_WARNING, "_curv_info : NULL pointer given");
		return;
	}
	if (curvline->getName()) {
		writelog(LOG_MESSAGE,"curv (%s)",curvline->getName());
	} else {
		writelog(LOG_MESSAGE,"curv noname");	
	}
};

void _add_surfit_curvs(d_curv * contour) {
	if (!contour)
		return;
	surfit_curvs->push_back(contour);
};

d_curv * _curv_intersect_grid(const d_curv * crv, const d_grid * grd)
{
	size_t n = crv->size()-1;
	size_t i, m = 0;
	size_t npm = 0;	
	
	REAL c_x, c_y;

	vec * X = create_vec(n+10);
	vec * Y = create_vec(n+10);
	
	REAL lt_x, lt_y;
	REAL lb_x, lb_y;
	REAL rt_x, rt_y;
	REAL rb_x, rb_y;
	
	bool sec;

	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();
	
	// ?? ????????
	lt_x = grd->getCoordNodeX(0) - grd->stepX/REAL(2);
	lt_y = grd->getCoordNodeY(0) - grd->stepY/REAL(2);
	lb_x = lt_x;
	lb_y = grd->getCoordNodeY(MM+1) - grd->stepY/REAL(2);

	rt_x = grd->getCoordNodeX(NN+1) - grd->stepX/REAL(2);
	rt_y = lt_y;
	rb_x = rt_x;
	rb_y = lb_y;

	REAL left = lt_x;
	REAL right = rt_x;
	REAL top = lt_y;
	REAL bottom = lb_y;

	for( i = 0; i < n; i++ )
	{ 
		REAL pi_x, pi_y, pi1_x, pi1_y; 
		pi_x  = (*(crv->X))(i);
		pi_y  = (*(crv->Y))(i);
		pi1_x = (*(crv->X))(i+1);
		pi1_y = (*(crv->Y))(i+1);
		
		// ??? ?????? ????????
		if( pi_x >= left && pi_x <= right && pi_y >= top && pi_y <= bottom )
		{ 
			(*X)(m) = pi_x;
			(*Y)(m) = pi_y;
			m++;
			if( pi1_x < left )
			{ 
				if( intersect(lt_x, lt_y, lb_x, lb_y, 
					      pi_x, pi_y, pi1_x, pi1_y, 
					      c_x, c_y) )
				{ 
					(*X)(m) = c_x; (*Y)(m) = c_y; m++;
					continue;
				}
			}
			if( pi1_x > right )
			{ 
				if( intersect(rt_x, rt_y, rb_x, rb_y,
					      pi_x, pi_y, pi1_x, pi1_y, 
					      c_x, c_y) )
				{ 
					(*X)(m) = c_x; (*Y)(m) = c_y; m++;
					continue;
				}
			}
			if( pi1_y < top )
			{ 
				if( intersect(lt_x, lt_y, rt_x, rt_y, 
					      pi_x, pi_y, pi1_x, pi1_y, 
					      c_x, c_y) )
				{ 
					(*X)(m) = c_x; (*Y)(m) = c_y;  m++;
					continue;
				}
			}
			if( pi1_y > bottom )
			{ 
				if( intersect(lb_x, lb_y, rb_x, rb_y, 
					      pi_x, pi_y, pi1_x, pi1_y, 
					      c_x, c_y) )
				{ 
					(*X)(m) = c_x; (*Y)(m) = c_y;  m++;
					continue;
				}
			}
		}
		// ??? ?????????????
		else
		{ 
			if( pi_x <= left && pi_y <= top )
			{ 
				(*X)(m) = lt_x; (*Y)(m) = lt_y; m++;
			}
			if( pi_x >= right && pi_y <= top )
			{ 
				(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
			}
			if( pi_x <= left && pi_y >= bottom )
			{ 
				(*X)(m) = lb_x; (*Y)(m) = lb_y; m++; 
			}
			if( pi_x >= right && pi_y >= bottom )
			{ 
				(*X)(m) = rb_x; (*Y)(m) = rb_y; m++;
			}
			
			// ??? ?????? ????????
			if( pi1_x >= left && pi1_x <= right && pi1_y >= top && pi1_y <= bottom )
			{ 
				if( pi_x < left )
				{ 
					if( intersect(lt_x, lt_y, lb_x, lb_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						continue;
					}
				}
				if( pi_x > right )
				{ 
					if( intersect(rt_x, rt_y, rb_x, rb_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						continue;
					}
				}
				if( pi_y < top )
				{ 
					if( intersect(lt_x, lt_y, rt_x, rt_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						continue;
					}
				}
				if( pi_y > bottom )
				{ 
					if( intersect(lb_x, lb_y, rb_x, rb_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						continue;
					}
				}
			}
			else
				// ??? ?????????????
			{ 
				sec = false;
				// ??
				if( pi_x < left && pi1_x > left )
				{ 
					// ??
					if( intersect(lt_x, lt_y, lb_x, lb_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						sec = true;
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						if( intersect(lt_x, lt_y, rt_x, rt_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(lb_x, lb_y, rb_x, rb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(rt_x, rt_y, rb_x, rb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
					}
					// ??
					if( sec || pi_y < top )
						if( intersect(lt_x, lt_y, rt_x, rt_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							if( intersect(rt_x, rt_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
							if( intersect(lb_x, lb_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
						}
						// ??
						if( sec || pi_y > bottom )
							if( intersect(lb_x, lb_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								if( intersect(rt_x, rt_y, rb_x, rb_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y; m++;
									continue;
								}
								if( intersect(lt_x, lt_y, rt_x, rt_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y; m++;
									continue;
								}
							}
							// ? ?????
							if( pi_y >= top && pi_y <= bottom )
							{ 
								if( pi1_y <= top )
								{ 
									(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
								}
								if( pi1_y >= bottom )
								{ 
									(*X)(m) = lb_x; (*Y)(m) = lb_y; m++; 
								}
								continue;
							}
							if( pi_y < top && pi1_y > bottom && pi1_x >= left && pi1_x <= right )
							{ 
								(*X)(m) = lb_x; (*Y)(m) = lb_y; m++; 
							}
							if( pi_y > bottom && pi1_y < top && pi1_x >= left && pi1_x <= right )
							{ 
								(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
							}
							if( pi1_x > right )
							{ 
								if( pi1_y >= top && pi1_y <= bottom )
								{ 
									if( pi_y < pi1_y )
									{ 
										(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
									}
									else
									{ 
										(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
									}
								}
								else
								{ 
									if( pi_y < top && pi1_y < top )  continue;
									if( pi_y > bottom && pi1_y > bottom )  continue;
									REAL dp_x[5];
									REAL dp_y[5];
									dp_x[0] = pi_x;  dp_y[0] = pi_y;  dp_x[4] = pi_x; dp_y[4] = pi_y;
									dp_x[1] = pi_x;  dp_y[1] = 0;
									dp_x[2] = pi1_x; dp_y[2] = 0;
									dp_x[3] = pi1_x; dp_y[3] = pi1_y;
									if( in_region(dp_x, dp_y, 4, (right+left)/REAL(2), (top+bottom)/REAL(2)) )
									{ 
										(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
									}
									else
									{ 
										(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
									}
								}
							}
							continue;
				}
				// ??
				if( pi_x > right && pi1_x < right )
				{ 
					// ??
					if( intersect(rt_x, rt_y, rb_x, rb_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						sec = true;
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						if( intersect(lt_x, lt_y, rt_x, rt_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(lb_x, lb_y, rb_x, rb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(lt_x, lt_y, lb_x, lb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
					}
					// ??
					if( sec || pi_y < top )
						if( intersect(lt_x, lt_y, rt_x, rt_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							if( intersect(lt_x, lt_y, lb_x, lb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
							if( intersect(lb_x, lb_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
						}
						// ??
						if( sec || pi_y > bottom )
							if( intersect(lb_x, lb_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								if( intersect(lt_x, lt_y, lb_x, lb_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y;  m++;
									continue;
								}
								if( intersect(lt_x, lt_y, rt_x, rt_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y; m++;
									continue;
								}
							}
							// ? ?????
							if( pi_y >= top && pi_y <= bottom )
							{ 
								if( pi1_y <= top )
								{ 
									(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
								}
								if( pi1_y >= bottom )
								{ 
									(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
								}
								continue;
							}
							if( pi_y < top && pi1_y > bottom && pi1_x >= left && pi1_x <= right )
							{ 
								(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
							}
							if( pi_y > bottom && pi1_y < top && pi1_x >= left && pi1_x <= right )
							{ 
								(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
							}
							if( pi1_x < left )
							{ 
								if( pi1_y >= top && pi1_y <= bottom )
								{ 
									if( pi_y < pi1_y )
									{ 
										(*X)(m) = lt_x; (*Y)(m) = lt_y;  m++; 
									}
									else			
									{ 
										(*X)(m) = lb_x; (*Y)(m) = lb_y;  m++; 
									}
								}
								else
								{ 
									if( pi_y < top && pi1_y < top )  continue;
									if( pi_y > bottom && pi1_y > bottom )  continue;
									REAL dp_x[5];
									REAL dp_y[5];
									dp_x[0] = pi_x;  dp_y[0] = pi_y; dp_x[4] = pi_x; dp_y[4] = pi_y;
									dp_x[1] = pi_x;  dp_y[1] = 0;
									dp_x[2] = pi1_x; dp_y[2] = 0;
									dp_x[3] = pi1_x; dp_y[3] = pi1_y;
									if( in_region(dp_x, dp_y, 4, (right+left)/REAL(2), (top+bottom)/REAL(2)) )
									{ 
										(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
									}
									else
									{ 
										(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
									}
								}
							}
							continue;
				}
				// ??
				if( pi_y < top && pi1_y > top )
				{ 
					// ??
					if( intersect(lt_x, lt_y, rt_x, rt_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						sec = true;
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						if( intersect(lt_x, lt_y, lb_x, lb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(rt_x, rt_y, rb_x, rb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(lb_x, lb_y, rb_x, rb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
					}
					// ??
					if( sec || pi_x < left )
						if( intersect(lt_x, lt_y, lb_x, lb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							if( intersect(lb_x, lb_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
							if( intersect(rt_x, rt_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
						}
						// ??
						if( sec || pi_x < right )
							if( intersect(rt_x, rt_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								if( intersect(lb_x, lb_y, rb_x, rb_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y; m++;
									continue;
								}
								if( intersect(lt_x, lt_y, lb_x, lb_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y; m++;
									continue;
								}
							}
							// ? ?????
							if( pi_x >= left && pi_x <= right )
							{ 
								if( pi1_x <= left )
								{ 
									(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
								}
								if( pi1_x >= right )
								{ 
									(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
								}
								continue;
							}
							if( pi_x < left && pi1_x > right && pi1_y >= top && pi1_y <= bottom )
							{ 
								(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
							}
							if( pi_x > right && pi1_x < left && pi1_y >= top && pi1_y <= bottom )
							{ 
								(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
							}
							if( pi1_y > bottom )
							{ 
								if( pi1_x >= left && pi1_x <= right )
								{ 
									if( pi_x < pi1_x )
									{ 
										(*X)(m) = lb_x; (*Y)(m) = lb_y; m++;
									}
									else
									{ 
										(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
									}
								}
								else
								{ 
									if( pi_x < left && pi1_x < left )  continue;
									if( pi_x > right && pi1_x > right )  continue;
									REAL dp_x[5];
									REAL dp_y[5];
									dp_x[0] = pi_x;  dp_y[0] = pi_y; dp_x[4] = pi_x; dp_y[4] = pi_y;
									dp_x[1] = pi_x;  dp_y[1] = 0;
									dp_x[2] = pi1_x; dp_y[2] = 0;
									dp_x[3] = pi1_x; dp_y[3] = pi1_y;
									if( in_region(dp_x, dp_y, 4, (right+left)/REAL(2), (top+bottom)/REAL(2)) )
									{ 
										(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
									}
									else
									{ 
										(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
									}
								}
							}
							continue;
				}
				// ??
				if( pi_y > bottom && pi1_y < bottom )
				{ 
					// ??
					if( intersect(lb_x, lb_y, rb_x, rb_y, 
						      pi_x, pi_y, pi1_x, pi1_y, 
						      c_x, c_y) )
					{ 
						sec = true;
						(*X)(m) = c_x; (*Y)(m) = c_y; m++;
						if( intersect(lt_x, lt_y, lb_x, lb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(rt_x, rt_y, rb_x, rb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
						if( intersect(lt_x, lt_y, rt_x, rt_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							continue;
						}
					}
					// ??
					if( sec || pi_x < left )
						if( intersect(lt_x, lt_y, lb_x, lb_y, 
							      pi_x, pi_y, pi1_x, pi1_y, 
							      c_x, c_y) )
						{ 
							(*X)(m) = c_x; (*Y)(m) = c_y; m++;
							if( intersect(lt_x, lt_y, rt_x, rt_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
							if( intersect(rt_x, rt_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								continue;
							}
						}
						// ??
						if( sec || pi_x < right )
							if( intersect(rt_x, rt_y, rb_x, rb_y, 
								      pi_x, pi_y, pi1_x, pi1_y, 
								      c_x, c_y) )
							{ 
								(*X)(m) = c_x; (*Y)(m) = c_y; m++;
								if( intersect(lt_x, lt_y, rt_x, rt_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y; m++;
									continue;
								}
								if( intersect(lt_x, lt_y, lb_y, lb_y, 
									      pi_x, pi_y, pi1_x, pi1_y, 
									      c_x, c_y) )
								{ 
									(*X)(m) = c_x; (*Y)(m) = c_y; m++;
									continue;
								}
							}
							// ? ?????
							if( pi_x >= left && pi_x <= right )
							{ 
								if( pi1_x <= left )
								{ 
									(*X)(m) = lb_x; (*Y)(m) = lb_y; m++; 
								}
								if( pi1_x >= right )
								{ 
									(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
								}
								continue;
							}
							if( pi_x < left && pi1_x > right && pi1_y >= top && pi1_y <= bottom )
							{ 
								(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
							}
							if( pi_x > right && pi1_x < left && pi1_y >= top && pi1_y <= bottom )
							{ 
								(*X)(m) = lb_x; (*Y)(m) = lb_y; m++; 
							}
							if( pi1_y < top )
							{ 
								if( pi1_x >= left && pi1_x <= right )
								{ 
									if( pi_x < pi1_x )
									{ 
										(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
									}
									else
									{ 
										(*X)(m) = rt_x; (*Y)(m) = rt_y; m++; 
									}
								}
								else
								{ 
									if( pi_x < left && pi1_x < left )  continue;
									if( pi_x > right && pi1_x > right )  continue;
									REAL dp_x[5];
									REAL dp_y[5];
									dp_x[0] = pi_x;  dp_y[0] = pi_y;  dp_x[4] = pi_x; dp_y[4] = pi_y;
									dp_x[1] = pi_x;  dp_y[1] = 0;
									dp_x[2] = pi1_x; dp_y[2] = 0;
									dp_x[3] = pi1_x; dp_y[3] = pi1_y;
									if( in_region(dp_x,  dp_y, 4, (right+left)/REAL(2), (top+bottom)/REAL(2)) )
									{ 
										(*X)(m) = rb_x; (*Y)(m) = rb_y; m++; 
									}
									else
									{ 
										(*X)(m) = lt_x; (*Y)(m) = lt_y; m++; 
									}
								}
							}
							continue;
				}
			}
		}
	} // i
	npm = 0;
	
	vec * XX = create_vec();
	vec * YY = create_vec();
	for( i = 0; i < m; i++ )
	{ 
		if( i ) 
		{
			REAL p_x, p_y;
			p_x = (*XX)(npm-1);
			p_y = (*YY)(npm-1);
			if( (*X)(i) == p_x && (*Y)(i) == p_y ) 
				continue;
		}
		XX->push_back( (*X)(i) );
		YY->push_back( (*Y)(i) );
		npm++;
	}

	if (crv->is_closed() && npm > 0) {
		XX->push_back( (*XX)(0) );
		YY->push_back( (*YY)(0) );
	}
	if( npm < 3 ) 
		npm = 0;
	if (X)
		X->release();
	if (Y)
		Y->release();

	if (npm == 0) {
		if (XX)
			XX->release();
		if (YY)
			YY->release();
		return NULL;
	} else {
		d_curv * res = create_curv(XX, YY, crv->getName());
		return res;
	}
	return NULL;
};


}; // namespace surfit;


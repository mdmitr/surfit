
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

bool _curv_write(const d_curv * curvline, const char * filename, const char * mask) {
	if (!curvline)
		return false;
	return two_columns_write(filename, mask,
				 curvline->X, curvline->Y);
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
				if (crv != NULL)
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
	writelog(LOG_MESSAGE,"curv (%s)",curvline->getName());
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

	REAL stepX2 = grd->stepX/REAL(2);
	REAL stepY2 = grd->stepY/REAL(2);
	
	lt_x = grd->getCoordNodeX(0) - stepX2;
	lt_y = grd->getCoordNodeY(0) - stepY2;
	lb_x = lt_x;
	lb_y = grd->getCoordNodeY(MM) - stepY2;

	rt_x = grd->getCoordNodeX(NN) - stepX2;
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
			{ 
				sec = false;
				if( pi_x < left && pi1_x > left )
				{ 
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
				if( pi_x > right && pi1_x < right )
				{ 
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
				if( pi_y < top && pi1_y > top )
				{ 
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
				if( pi_y > bottom && pi1_y < bottom )
				{ 
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



/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "ie.h"
#include <errno.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "read_txt.h"
#include "fileio.h"
#include "vec.h"


namespace surfit {

bool two_columns_read(const char * filename, 
                      int columns, 
                      int col1, int col2, 
                      const char *mask, int grow_by,
                      REAL *& col1_begin, REAL *& col1_end,
                      REAL *& col2_begin, REAL *& col2_end) 
{
	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "loading from two-column file: file error.");
		fclose(file);
		return false;
	}

	vec *res1 = new vec;
	res1->set_grow(grow_by);
	vec *res2 = new vec;
	res2->set_grow(grow_by);

	vec *arr = new vec(columns);
	REAL *begin = arr->begin();
	REAL *end = arr->end();
	
	int counter = 0;
	int scan_res = 0;

	char buf[256];

	while (!feof(file) ) {
		begin = arr->begin();
		while (begin != end) {
			if (feof(file)) {
				if (begin == arr->begin())
					break;
				writelog(SURFIT_ERROR, "loading from two-column file: format error.");
				delete res1;
				delete res2;
				delete arr;
				fclose(file);
				return false;
			}
			scan_res = fscanf(file,"%s",buf);
			if (scan_res == -1) 
				break;
			if (scan_res != 1) {
				writelog(SURFIT_ERROR, "loading from two-column file: format error.");
				delete res1;
				delete res2;
				delete arr;
				fclose(file);
				return false;
			};
			*begin = REAL(atof(buf));
			begin++;
		}
		if (scan_res == -1) 
			break;
		res1->push_back(*(arr->begin()+col1-1));
		res2->push_back(*(arr->begin()+col2-1));
	}

	delete arr;
		
	col1_begin = res1->begin();
	col1_end = res1->end();
	res1->ref_begin() = NULL;
	delete res1;

	col2_begin = res2->begin();
	col2_end = res2->end();
	res2->ref_begin() = NULL;
	delete res2;

	fclose(file);

	return true;
};

bool two_columns_write(const char * filename, const char * mask,
		       const REAL * col1_begin, const REAL * col1_end,
		       const REAL * col2_begin, const REAL * col2_end) 
{
	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(SURFIT_WARNING, "writing two-columns file: NULL pointer to file.");
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "writing two-columns file: file error.");
		fclose(file);
		return false;
	}
	while (col1_begin != col1_end) {
		fprintf(file, mask, *col1_begin, *col2_begin);
		col1_begin++;
		col2_begin++;
	}
	fflush(file);
	fclose(file);
	return true;
};

bool three_columns_read(const char * filename, 
                        int columns, 
                        int col1, int col2, int col3, 
                        const char * delimiter, int grow_by,
                        REAL *& col1_begin, REAL *& col1_end,
                        REAL *& col2_begin, REAL *& col2_end,
                        REAL *& col3_begin, REAL *& col3_end)
{
	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "Loading from therr-column file: file error.");
		fclose(file);
		return false;
	}

	vec *res1 = new vec;
	res1->set_grow(grow_by);
	vec *res2 = new vec;
	res2->set_grow(grow_by);
	vec *res3 = new vec;
	res3->set_grow(grow_by);

	vec *arr = new vec(columns);
	REAL *begin = arr->begin();
	REAL *end = arr->end();
	
	int counter = 0;
	int scan_res = 0;

	char string_buf[1024];
	char buf[256];
	char buf2[256];
	char buf3[256];
	char mask[256];
	strcpy(mask, "%s");
	strcat(mask, delimiter );
	strcat(mask, "%s" );
	strcat(mask, delimiter );
	strcat(mask, "%s" );
	
	while (!feof(file) ) {
		
		if (columns == 3) {
			if (!fgets(string_buf,1024,file)) 
				break;
			scan_res = sscanf(string_buf, mask, buf, buf2, buf3);
			if (scan_res == -1) 
				break;
			if (scan_res != 3) {
				writelog(SURFIT_ERROR, "Loading from three-column file: format error.");
				delete res1;
				delete res2;
				delete res3;
				delete arr;
				fclose(file);
				return false;
			};
			res1->push_back( (REAL)atof(buf)  );
			res2->push_back( (REAL)atof(buf2) );
			res3->push_back( (REAL)atof(buf3) );
		}
		else 
		{
			begin = arr->begin();
			while (begin != end) {
				if (feof(file)) {
					if (begin == arr->begin())
						break;
					writelog(SURFIT_ERROR, "Loading from three-column file: format error.");
					delete res1;
					delete res2;
					delete res3;
					delete arr;
					fclose(file);
					return false;
				}
				scan_res = fscanf(file,"%s",buf);
				if (scan_res == -1) 
					break;
				if (scan_res != 1) {
					writelog(SURFIT_ERROR, "Loading from three-column file: format error.");
					delete res1;
					delete res2;
					delete res3;
					delete arr;
					fclose(file);
					return false;
				};
				*begin = REAL(atof(buf));
				begin++;
			}
			if (scan_res == -1) 
				break;
			res1->push_back(*(arr->begin()+col1-1));
			res2->push_back(*(arr->begin()+col2-1));
			res3->push_back(*(arr->begin()+col3-1));
		}
		if(res3->size() % 1000000 == 0) {
			writelog(SURFIT_MESSAGE,"%d million points readed...",res3->size() / 1000000);
		}
	}

	delete arr;

	col1_begin = res1->begin();
	col1_end = res1->end();
	res1->ref_begin() = NULL;

	col2_begin = res2->begin();
	col2_end = res2->end();
	res2->ref_begin() = NULL;

	col3_begin = res3->begin();
	col3_end = res3->end();
	res3->ref_begin() = NULL;
	
	delete res1;
	delete res2;
	delete res3;
	fclose(file);
	
	return true;
};

bool three_columns_write(const char * filename, const char * mask,
			 const REAL * col1_begin, const REAL * col1_end,
			 const REAL * col2_begin, const REAL * col2_end,
			 const REAL * col3_begin, const REAL * col3_end) 
{
	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(SURFIT_WARNING, "Writing three-columns file: NULL pointer to file.");
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "Writing three-columns file: file error.");
		fclose(file);
		return false;
	}
	while (col1_begin != col1_end) {
		fprintf(file, mask, *col1_begin, *col2_begin, *col3_begin);
		col1_begin++;
		col2_begin++;
		col3_begin++;
	}
	fflush(file);
	fclose(file);
	return true;
};

bool four_columns_read(const char * filename, 
                       int columns, 
                       int col1, int col2, int col3, int col4, 
                       const char * delimiter, int grow_by,
                       REAL *& col1_begin, REAL *& col1_end,
                       REAL *& col2_begin, REAL *& col2_end,
                       REAL *& col3_begin, REAL *& col3_end,
					   REAL *& col4_begin, REAL *& col4_end)
{
	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "Loading from four-column file: file error.");
		fclose(file);
		return false;
	}

	vec *res1 = new vec;
	res1->set_grow(grow_by);
	vec *res2 = new vec;
	res2->set_grow(grow_by);
	vec *res3 = new vec;
	res3->set_grow(grow_by);
	vec *res4 = new vec;
	res4->set_grow(grow_by);

	vec *arr = new vec(columns);
	REAL *begin = arr->begin();
	REAL *end = arr->end();
	
	int counter = 0;
	int scan_res = 0;

	char string_buf[1024];
	char buf[256];
	char buf2[256];
	char buf3[256];
	char buf4[256];
	char mask[256];
	strcpy(mask, "%s");
	strcat(mask, delimiter );
	strcat(mask, "%s" );
	strcat(mask, delimiter );
	strcat(mask, "%s" );
	strcat(mask, delimiter );
	strcat(mask, "%s" );
	
	while (!feof(file) ) {
		
		if (columns == 4) {
			if (!fgets(string_buf,1024,file)) 
				break;
			scan_res = sscanf(string_buf, mask, buf, buf2, buf3, buf4);
			if (scan_res == -1) 
				break;
			if (scan_res != 4) {
				writelog(SURFIT_ERROR, "Loading from four-column file: format error.");
				delete res1;
				delete res2;
				delete res3;
				delete res4;
				delete arr;
				fclose(file);
				return false;
			};
			res1->push_back( (REAL)atof(buf)  );
			res2->push_back( (REAL)atof(buf2) );
			res3->push_back( (REAL)atof(buf3) );
			res4->push_back( (REAL)atof(buf4) );
		}
		else 
		{
			begin = arr->begin();
			while (begin != end) {
				if (feof(file)) {
					if (begin == arr->begin())
						break;
					writelog(SURFIT_ERROR, "Loading from four-column file: format error.");
					delete res1;
					delete res2;
					delete res3;
					delete res4;
					delete arr;
					fclose(file);
					return false;
				}
				scan_res = fscanf(file,"%s",buf);
				if (scan_res == -1) 
					break;
				if (scan_res != 1) {
					writelog(SURFIT_ERROR, "Loading from four-column file: format error.");
					delete res1;
					delete res2;
					delete res3;
					delete res4;
					delete arr;
					fclose(file);
					return false;
				};
				*begin = REAL(atof(buf));
				begin++;
			}
			if (scan_res == -1) 
				break;
			res1->push_back(*(arr->begin()+col1-1));
			res2->push_back(*(arr->begin()+col2-1));
			res3->push_back(*(arr->begin()+col3-1));
			res4->push_back(*(arr->begin()+col4-1));
		}
		if(res3->size() % 1000000 == 0) {
			writelog(SURFIT_MESSAGE,"%d million points readed...",res3->size() / 1000000);
		}
	}

	delete arr;

	col1_begin = res1->begin();
	col1_end = res1->end();
	res1->ref_begin() = NULL;

	col2_begin = res2->begin();
	col2_end = res2->end();
	res2->ref_begin() = NULL;

	col3_begin = res3->begin();
	col3_end = res3->end();
	res3->ref_begin() = NULL;

	col4_begin = res4->begin();
	col4_end = res4->end();
	res4->ref_begin() = NULL;
	
	delete res1;
	delete res2;
	delete res3;
	delete res4;
	fclose(file);
	
	return true;
};

bool four_columns_write(const char * filename, const char * mask,
			const REAL * col1_begin, const REAL * col1_end,
			const REAL * col2_begin, const REAL * col2_end,
			const REAL * col3_begin, const REAL * col3_end,
			const REAL * col4_begin, const REAL * col4_end) 
{
	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(SURFIT_WARNING, "Writing four-columns file: NULL pointer to file.");
		return false;
	}
	if (ferror(file) != 0) {
		writelog(SURFIT_ERROR, "Writing four-columns file: file error.");
		fclose(file);
		return false;
	}
	while (col1_begin != col1_end) {
		fprintf(file, mask, *col1_begin, *col2_begin, *col3_begin, *col4_begin);
		col1_begin++;
		col2_begin++;
		col3_begin++;
		col4_begin++;
	}
	fclose(file);
	return true;
};

}; // namespace surfit;


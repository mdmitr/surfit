
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

#include "sstuff_ie.h"
#include "fileio.h"

#include <errno.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <float.h>

#include "read_txt.h"
#include "vec.h"
#include "strvec.h"

#define MY_READ_BUF_SIZE 1024*4

namespace surfit {

REAL ator(char * text) {
	size_t pos = strcspn(text, "0123456789,.");
	if (pos == strlen(text))
		return FLT_MAX;
	char * ptr = strchr(text,',');
	if (ptr)
		*ptr = '.';
	return REAL(atof(text));
};

bool two_columns_read(const char * filename, 
                      int col1, int col2, 
		      int skip_lines,
		      const char * delimiter, int grow_by,
		      vec *& vcol1, vec *& vcol2,
		      int read_lines)
{
	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "Loading from two-column file: file error.");
		fclose(file);
		return false;
	}

	char string_buf[MY_READ_BUF_SIZE];

	int i;
	for (i = 0; i < skip_lines; i++) {
		if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) 
		{
			fclose(file);
			return false;
		}
		if (feof(file)) {
			fclose(file);
			return false;
		}
	};

	vcol1 = create_vec();
	vcol1->set_grow(grow_by);
	vcol2 = create_vec();
	vcol2->set_grow(grow_by);
	char * seps = strdup(delimiter);
	char * token = NULL;
	int columns = 0;
	int lines_readed = 0;
	int current_column = 0;
	int size = 0;

	// calculate number of columns!
	fpos_t pos;
	if (fgetpos(file, &pos) != 0)
		goto two_columns_read_failed;

	if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) 
		goto two_columns_read_failed;

	if (fsetpos(file, &pos) != 0)
		goto two_columns_read_failed;

	columns = calc_columns(string_buf, MY_READ_BUF_SIZE, seps);

	if (col1 > columns)
		goto two_columns_read_failed;
	if (col2 > columns)
		goto two_columns_read_failed;
	
	while (!feof(file) ) {
		if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) {
			if (feof(file))
				break;
			goto two_columns_read_failed;
		}
		
		if (read_lines > 0) {
			lines_readed++;
			if (lines_readed > read_lines)
				break;
		}

		current_column = 0;
		token = strtok(string_buf, seps);
		REAL val1 = FLT_MAX, val2 = FLT_MAX;
		while (token != NULL) {
			if (current_column+1 == col1) {
				if (strlen(token) > 0)
					val1 = (REAL)ator(token);
				
			}
				
			if (current_column+1 == col2)  {
				if (strlen(token) > 0)
					val2 = (REAL)ator(token);
			}
			
			current_column++;
			token = strtok( NULL, seps );
		}

		if (
			((val1 != FLT_MAX) || (col1 == 0)) &&
			((val2 != FLT_MAX) || (col2 == 0))
		   ) 
		{
			vcol1->push_back(val1);
			vcol2->push_back(val2);
		}
		val1 = FLT_MAX;
		val2 = FLT_MAX;
		
	}

	size = MIN( vcol1->size(), vcol2->size() );
	vcol1->resize(size);
	vcol2->resize(size);
		
	free(seps);
	fclose(file);
		
	return true;

two_columns_read_failed:

	fclose(file);
	free(seps);
	if (vcol1)
		vcol1->release();
	if (vcol2)
		vcol2->release();
	vcol1 = NULL;
	vcol2 = NULL;
	return false;
};

bool two_columns_write(const char * filename, const char * mask,
		       const vec * vcol1, const vec * vcol2) 
{
	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(LOG_WARNING, "writing two-columns file: NULL pointer to file.");
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "writing two-columns file: file error.");
		fclose(file);
		return false;
	}
	const REAL * col1_begin = vcol1->begin();
	const REAL * col1_end = vcol1->end();
	const REAL * col2_begin = vcol2->begin();
	const REAL * col2_end = vcol2->end();
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
                        int col1, int col2, int col3, 
			int skip_lines,
                        const char * delimiter, int grow_by,
                        vec *& vcol1, vec *& vcol2, vec *& vcol3,
			int read_lines)
{
	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "Loading from therr-column file: file error.");
		fclose(file);
		return false;
	}

	char string_buf[MY_READ_BUF_SIZE];

	int i;
	for (i = 0; i < skip_lines; i++) {
		if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) 
		{
			fclose(file);
			return false;
		}
		if (feof(file)) {
			fclose(file);
			return false;
		}
	};

	vcol1 = create_vec();
	vcol1->set_grow(grow_by);
	vcol2 = create_vec();
	vcol2->set_grow(grow_by);
	vcol3 = create_vec();
	vcol3->set_grow(grow_by);
	char * seps = strdup(delimiter);
	char * token = NULL;
	int columns = 0;
	int lines_readed = 0;
	int current_column = 0;
	size_t size = 0;

	// calculate number of columns!
	fpos_t pos;
	if (fgetpos(file, &pos) != 0)
		goto three_columns_read_failed;

	if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) 
		goto three_columns_read_failed;

	if (fsetpos(file, &pos) != 0)
		goto three_columns_read_failed;

	columns = calc_columns(string_buf, MY_READ_BUF_SIZE, seps);
	
	if (col1 > columns)
		goto three_columns_read_failed;
	if (col2 > columns)
		goto three_columns_read_failed;
	if (col3 > columns)
		goto three_columns_read_failed;

	while (!feof(file) ) {
		if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) {
			if (feof(file))
				break;
			goto three_columns_read_failed;
		}
		
		if (read_lines > 0) {
			lines_readed++;
			if (lines_readed > read_lines)
				break;
		}

		current_column = 0;
		token = strtok(string_buf, seps);
		REAL val1 = FLT_MAX, val2 = FLT_MAX, val3 = FLT_MAX;
		while (token != NULL) {
			if (current_column+1 == col1) {
				if (strlen(token) > 0)
					val1 = (REAL)ator(token);
				
			}
				
			if (current_column+1 == col2)  {
				if (strlen(token) > 0)
					val2 = (REAL)ator(token);
			}

			if (current_column+1 == col3)  {
				if (strlen(token) > 0)
					val3 = (REAL)ator(token);
			}
								
			current_column++;
			token = strtok( NULL, seps );
		}

		if ( ((val1 != FLT_MAX) || (col1 == 0)) && 
		     ((val2 != FLT_MAX) || (col2 == 0)) && 
		     ((val3 != FLT_MAX) || (col3 == 0)) 
		   ) 
		{
			vcol1->push_back(val1);
			vcol2->push_back(val2);
			vcol3->push_back(val3);
		}
		val1 = FLT_MAX;
		val2 = FLT_MAX;
		val3 = FLT_MAX;
		
	}
	
	size = MIN( vcol1->size(), vcol2->size() );
	size = MIN( size, vcol3->size() );
	vcol1->resize(size);
	vcol2->resize(size);
	vcol3->resize(size);

	free(seps);
	fclose(file);
		
	return true;

three_columns_read_failed:

	fclose(file);
	free(seps);
	if (vcol1)
		vcol1->release();
	if (vcol2)
		vcol2->release();
	if (vcol3)
		vcol3->release();
	vcol1 = NULL;
	vcol2 = NULL;
	vcol3 = NULL;
	return false;
};

bool three_columns_read_with_names(const char * filename, 
				   int col1, int col2, int col3, int col4, 
				   int skip_lines,
				   const char * delimiter, int grow_by,
				   vec *& vcol1, vec *& vcol2, vec *& vcol3, 
				   strvec *& names,
				   int read_lines)
{
	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "Loading from therr-column file: file error.");
		fclose(file);
		return false;
	}

	char string_buf[MY_READ_BUF_SIZE];

	int i;
	for (i = 0; i < skip_lines; i++) {
		if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) 
		{
			fclose(file);
			return false;
		}
		if (feof(file)) {
			fclose(file);
			return false;
		}
	};

	vcol1 = create_vec();
	vcol1->set_grow(grow_by);
	vcol2 = create_vec();
	vcol2->set_grow(grow_by);
	vcol3 = create_vec();
	vcol3->set_grow(grow_by);
	names = create_strvec();
	names->set_grow(grow_by);
	char * seps = strdup(delimiter);
	char * token = NULL;
	int columns = 0;
	int lines_readed = 0;
	int current_column = 0;
	size_t size = 0;

	// calculate number of columns!
	fpos_t pos;
	if (fgetpos(file, &pos) != 0)
		goto three_columns_read_failed;

	if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) 
		goto three_columns_read_failed;

	if (fsetpos(file, &pos) != 0)
		goto three_columns_read_failed;

	columns = calc_columns(string_buf, MY_READ_BUF_SIZE, seps);

	if (col1 > columns)
		goto three_columns_read_failed;
	if (col2 > columns)
		goto three_columns_read_failed;
	if (col3 > columns)
		goto three_columns_read_failed;
	if (col4 > columns)
		goto three_columns_read_failed;

	while (!feof(file) ) {
		if (!fgets(string_buf,MY_READ_BUF_SIZE,file)) {
			if (feof(file))
				break;
			goto three_columns_read_failed;
		}
		
		if (read_lines > 0) {
			lines_readed++;
			if (lines_readed > read_lines)
				break;
		}

		current_column = 0;
		token = strtok(string_buf, seps);
		REAL val1 = FLT_MAX, val2 = FLT_MAX, val3 = FLT_MAX;
		char * sval = NULL;
		while (token != NULL) {
			if (current_column+1 == col1) {
				if (strlen(token) > 0)
					val1 = (REAL)ator(token);
				
			}
				
			if (current_column+1 == col2)  {
				if (strlen(token) > 0)
					val2 = (REAL)ator(token);
			}

			if (current_column+1 == col3)  {
				if (strlen(token) > 0)
					val3 = (REAL)ator(token);
			}

			if (current_column+1 == col4) {
				if (strlen(token) > 0)
					sval = strdup(token);
			}
								
			current_column++;
			token = strtok( NULL, seps );
		}

		if ( 
			((val1 != FLT_MAX) || (col1 == 0)) && 
			((val2 != FLT_MAX) || (col2 == 0)) &&
			((val3 != FLT_MAX) || (col3 == 0)) && 
			((sval != NULL) || (col4 == 0))
		   ) 
		{
			vcol1->push_back(val1);
			vcol2->push_back(val2);
			vcol3->push_back(val3);
			names->push_back(sval);
			
		}
		val1 = FLT_MAX;
		val2 = FLT_MAX;
		val3 = FLT_MAX;
		sval = NULL;
		
	}
	
	size = MIN( vcol1->size(), vcol2->size() );
	size = MIN( size, vcol3->size() );
	vcol1->resize(size);
	vcol2->resize(size);
	vcol3->resize(size);
	names->resize(size);

	free(seps);
	fclose(file);
		
	return true;

three_columns_read_failed:

	fclose(file);
	free(seps);
	if (vcol1)
		vcol1->release();
	if (vcol2)
		vcol2->release();
	if (vcol3)
		vcol3->release();
	vcol1 = NULL;
	vcol2 = NULL;
	vcol3 = NULL;
	return false;
};

bool three_columns_write(const char * filename, const char * mask,
			 const vec * vcol1, const vec * vcol2, const vec * vcol3) 
{
	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(LOG_WARNING, "Writing three-columns file: NULL pointer to file.");
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "Writing three-columns file: file error.");
		fclose(file);
		return false;
	}

	const REAL * col1_begin = vcol1->begin();
	const REAL * col1_end = vcol1->end();
	const REAL * col2_begin = vcol2->begin();
	const REAL * col2_end = vcol2->end();
	const REAL * col3_begin = vcol3->begin();
	const REAL * col3_end = vcol3->end();

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
                       vec *& vcol1, vec *& vcol2,
                       vec *& vcol3, vec *& vcol4)
{
	FILE * file = fopen(filename, "r");
	if (!file) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "Loading from four-column file: file error.");
		fclose(file);
		return false;
	}

	vcol1 = create_vec();
	vcol1->set_grow(grow_by);
	vcol2 = create_vec();
	vcol2->set_grow(grow_by);
	vcol3 = create_vec();
	vcol3->set_grow(grow_by);
	vcol4 = create_vec();
	vcol4->set_grow(grow_by);

	vec *arr = create_vec(columns);
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
				goto exit;
			};
			vcol1->push_back( (REAL)ator(buf)  );
			vcol2->push_back( (REAL)ator(buf2) );
			vcol3->push_back( (REAL)ator(buf3) );
			vcol4->push_back( (REAL)ator(buf4) );
		}
		else 
		{
			begin = arr->begin();
			while (begin != end) {
				if (feof(file)) {
					if (begin == arr->begin())
						break;
					goto exit;
				}
				scan_res = fscanf(file,"%s",buf);
				if (scan_res == -1) 
					break;
				if (scan_res != 1) {
					goto exit;
				};
				*begin = REAL(ator(buf));
				begin++;
			}
			if (scan_res == -1) 
				break;
			vcol1->push_back(*(arr->begin()+col1-1));
			vcol2->push_back(*(arr->begin()+col2-1));
			vcol3->push_back(*(arr->begin()+col3-1));
			vcol4->push_back(*(arr->begin()+col4-1));
		}
		if(vcol3->size() % 1000000 == 0) {
			writelog(LOG_MESSAGE,"%d million points readed...",vcol3->size() / 1000000);
		}
	}

	if (arr)
		arr->release();
						
	fclose(file);
	
	return true;

exit:

	writelog(LOG_ERROR, "Loading from four-column file: format error.");
	if (vcol1)
		vcol1->release();
	if (vcol2)
		vcol2->release();
	if (vcol3)
		vcol3->release();
	if (vcol4)
		vcol4->release();
	if (arr)
		arr->release();
	fclose(file);
	vcol1 = NULL;
	vcol2 = NULL;
	vcol3 = NULL;
	vcol4 = NULL;
	return false;


};

bool four_columns_write(const char * filename, const char * mask,
			const vec * vcol1, const vec * vcol2, 
			const vec * vcol3, const vec * vcol4) 
{
	FILE * file = fopen(filename, "w");
	if (!file) {
		writelog(LOG_WARNING, "Writing four-columns file: NULL pointer to file.");
		return false;
	}
	if (ferror(file) != 0) {
		writelog(LOG_ERROR, "Writing four-columns file: file error.");
		fclose(file);
		return false;
	}

	const REAL * col1_begin = vcol1->begin();
	const REAL * col1_end = vcol1->end();
	const REAL * col2_begin = vcol2->begin();
	const REAL * col2_end = vcol2->end();
	const REAL * col3_begin = vcol3->begin();
	const REAL * col3_end = vcol3->end();
	const REAL * col4_begin = vcol4->begin();
	const REAL * col4_end = vcol4->end();

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


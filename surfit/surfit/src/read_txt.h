
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

#ifndef __surfit_read_txt_included__
#define __surfit_read_txt_included__

namespace surfit {

SURFIT_EXPORT
bool two_columns_read(const char * filename, 
                      int columns, 
                      int col1, int col2, 
                      const char *mask, int grow_by,
                      REAL *& col1_begin, REAL *& col1_end,
                      REAL *& col2_begin, REAL *& col2d_end);

SURFIT_EXPORT
bool two_columns_write(const char * filename, const char * mask,
		       const REAL * col1_begin, const REAL * col1_end,
		       const REAL * col2_begin, const REAL * col2_end);

SURFIT_EXPORT
bool three_columns_read(const char * filename, 
                        int columns, 
                        int col1, int col2, int col3, 
                        const char * mask, int grow_by,
                        REAL *& col1_begin, REAL *& col1_end,
                        REAL *& col2_begin, REAL *& col2_end,
                        REAL *& col3_begin, REAL *& col3_end);

SURFIT_EXPORT
bool three_columns_write(const char * filename, const char * mask,
			 const REAL * col1_begin, const REAL * col1_end,
			 const REAL * col2_begin, const REAL * col2_end,
			 const REAL * col3_begin, const REAL * col3_end);

SURFIT_EXPORT
bool four_columns_read(const char * filename, 
                       int columns, 
                       int col1, int col2, int col3, int col4,
                       const char * mask, int grow_by,
                       REAL *& col1_begin, REAL *& col1_end,
                       REAL *& col2_begin, REAL *& col2_end,
                       REAL *& col3_begin, REAL *& col3_end,
					   REAL *& col4_begin, REAL *& col4_end);

SURFIT_EXPORT
bool four_columns_write(const char * filename, const char * mask,
			const REAL * col1_begin, const REAL * col1_end,
			const REAL * col2_begin, const REAL * col2_end,
			const REAL * col3_begin, const REAL * col3_end,
			const REAL * col4_begin, const REAL * col4_end);

}; // namespace surfit;

#endif



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

#ifndef __surfit_surfit_threads_included__
#define __surfit_surfit_threads_included__

#define MAX_CPU 16

namespace surfit {

SURFIT_EXPORT
void init_threads(int cnt);

#ifdef HAVE_THREADS
struct job {
	virtual void do_job() = 0;
	virtual void release() { delete this; };
};

SURFIT_EXPORT
void set_job(job * j, unsigned int pos);

SURFIT_EXPORT
void do_jobs();
#endif

}; // namespace surfti;

#endif


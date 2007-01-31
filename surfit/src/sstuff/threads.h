
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

#ifndef __sstuff_threads_included__
#define __sstuff_threads_included__

#ifdef HAVE_THREADS

#define MAX_CPU 16

struct SSTUFF_EXPORT job {
	virtual void do_job() = 0;
	virtual void release();
};

SSTUFF_EXPORT
void set_job(job * j, size_t pos);

SSTUFF_EXPORT
void do_jobs();

SSTUFF_EXPORT
void sstuff_init_threads(size_t cnt);

SSTUFF_EXPORT
size_t sstuff_get_threads();

extern SSTUFF_EXPORT size_t cpu;

#include "ptypes.h"
#include "pasync.h"

USING_PTYPES

const int MSG_JOB = MSG_USER + 1;

class jobmessage: public message
{
public:
	jobmessage(): message(MSG_JOB) {};
};

class slavethread: public thread , protected msgqueue
{
protected:
	virtual void execute();
	virtual void cleanup();
	virtual void msghandler(message& msg);  // override msgqueue::msghandler()
public:
	
	semaphore sem;
	slavethread() : thread(true), sem(0), j(NULL) {};
	void post_do_job();
	void postquit();
	
	job * j;
};

#endif // HAVE_THREADS

#endif


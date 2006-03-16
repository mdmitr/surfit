
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

#ifndef __surfit_threads_included__
#define __surfit_threads_included__

#include "surfit_threads.h"

#ifdef HAVE_THREADS

#include "ptypes/ptypes.h"
#include "ptypes/pasync.h"

USING_PTYPES

namespace surfit {

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

};// namespace surfit;

#endif // HAVE_THREADS

#endif


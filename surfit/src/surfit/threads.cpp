
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
 *	See COPYING file for copying and redistribution conditions.
 *
 *	  program is free software; you can redistribute it and/or modify
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
#include "surfit_threads.h"
#include "threads.h"
#include "variables_tcl.h"
#include <vector>

namespace surfit {

#ifdef HAVE_THREADS
std::vector<slavethread *> slaves;
std::vector<job *> jobs;
#endif

void init_threads(int cnt) {
	cpu = MIN(cnt, MAX_CPU);
#ifdef HAVE_THREADS
	size_t ssize = slaves.size();
	if (ssize == cpu)
		return;
	size_t i;
	if ((int)ssize > cpu-1) {
		for (i = 0; i < ssize-cpu-1; i++) {
			slavethread * slave = *(slaves.end()-1);
			slave->postquit();
			slave->waitfor();
			slaves.erase(slaves.end()-1);
		}
	} else {
		for (i = 0; i < cpu-ssize-1; i++) {
			slavethread * slave = new slavethread();
			slaves.push_back(slave);
			slave->start();
		}
	}
	jobs.resize(cpu);
	for (i = 0; i < (size_t)cpu; i++)
		jobs[i] = NULL;
#endif //threads
};

int get_threads() {
	return cpu;
};

/*
void finish_threads() {
	if (master) {
		master->postquit();
		master->waitfor();
	}
	delete master; 
	master = NULL;
};
*/

#ifdef HAVE_THREADS
void set_job(job * j, size_t pos) {
	jobs[pos] = j;
};

void do_jobs() {
	
	size_t i;
	unsigned added_slaves = 0;
	for (i = 1; i < jobs.size(); i++) {
		job * j = jobs[i];
		if (j == NULL)
			break;

		slavethread * slave = slaves[i-1];
		slave->j = j;
		jobs[i] = NULL;
		slave->post_do_job();
		added_slaves++;
	}

	job * j = jobs[0];
	jobs[0] = NULL;
	j->do_job();

	for (i = 0; i < added_slaves; i++) {
		slavethread * slave = slaves[i];
		slave->sem.wait();
	}

};

void slavethread::execute()
{
	msgqueue::run();
}

void slavethread::cleanup()
{
}

void slavethread::msghandler(message& msg)
{
	switch (msg.id)
	{
	case MSG_JOB:
		{
			if (j) {
				j->do_job();
				j = NULL;
			}
			sem.post();
		}
		break;
	default:
		defhandler(msg);
	}
}

void slavethread::postquit()
{ 
	msgqueue::post(MSG_QUIT); 
}

inline void slavethread::post_do_job()
{  
	msgqueue::post(new jobmessage());
}
#endif // HAVE_THREADS

}; // namespace surfit;


/*
 *
 *  C++ Portable Types Library (PTypes)
 *  Version 1.3.2 Released: 26-Jun-2002
 *
 *  Copyright (C) 2001, 2002 Hovik Melikyan
 *
 *  http://www.melikyan.com/ptypes/
 *
 */

#ifdef WIN32
#  include <windows.h>
#else
#  include <sys/time.h>
#  include <pthread.h>
#  include <errno.h>
#endif

#include "pasync.h"


PTYPES_BEGIN


static void tsem_fail()
{
    fatal(CRIT_FIRST + 41, "Timed semaphore failed");
}



#ifdef WIN32


tsemaphore::tsemaphore(int initvalue)
: semaphore(initvalue) {}


tsemaphore::~tsemaphore() {}


bool tsemaphore::wait(int msecs)
{
    if (msecs == -1)
    {
        semaphore::wait();
        return true;
    }
    else
    {
        int r = WaitForSingleObject(handle, msecs);
        if (r == WAIT_FAILED)
            tsem_fail();
        return r != WAIT_TIMEOUT;
    }
}


#else

inline void syscheck(int r)
{
    if (r != 0)
        tsem_fail();
}


tsemaphore::tsemaphore(int initvalue)
: unknown()
{
    syscheck(pthread_mutex_init(&mtx, 0));
    syscheck(pthread_cond_init(&cond, 0));
    count = initvalue;
}


tsemaphore::~tsemaphore()
{
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mtx);
}


void tsemaphore::wait()
{
    pthread_mutex_lock(&mtx);
    while (count <= 0)
        pthread_cond_wait(&cond, &mtx);
    count -= 1;
    pthread_mutex_unlock(&mtx);
}


bool tsemaphore::wait(int msecs)
{
    if (msecs == -1)
    {
        wait();
        return true;
    }
    pthread_mutex_lock(&mtx);
    while (count <= 0) { 
        timespec abs_ts; 
        timeval cur_tv;
        gettimeofday(&cur_tv, NULL);
        abs_ts.tv_sec = cur_tv.tv_sec + msecs / 1000; 
        abs_ts.tv_nsec = cur_tv.tv_usec * 1000 + msecs % 1000;
        int rc = pthread_cond_timedwait(&cond, &mtx, &abs_ts);
        if (rc == ETIMEDOUT) { 
            pthread_mutex_unlock(&mtx);
            return false;
        }
    } 
    count -= 1;
    pthread_mutex_unlock(&mtx);
    return true;
} 


void tsemaphore::post()
{
    pthread_mutex_lock(&mtx);
    count += 1; 
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx);
}


#endif


PTYPES_END

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
#  include <pthread.h>
#endif

#include "pasync.h"


PTYPES_BEGIN

#ifndef __DARWIN__

static void sem_fail()
{
    fatal(CRIT_FIRST + 41, "Semaphore failed");
}


semaphore::semaphore(int initvalue) 
{
#ifdef WIN32
    handle = CreateSemaphore(nil, initvalue, 65535, nil);
    if (handle == 0)
        sem_fail();
#else
    if (sem_init(&handle, 0, initvalue) != 0)
        sem_fail();
#endif
}


semaphore::~semaphore() 
{
#ifdef WIN32
    CloseHandle(HANDLE(handle));
#else
    sem_destroy(&handle);
#endif
}


void semaphore::wait() 
{
#ifdef WIN32
    if (WaitForSingleObject(HANDLE(handle), INFINITE) == WAIT_FAILED)
        sem_fail();
#else
    if (sem_wait(&handle) != 0)
        sem_fail();
#endif
}


void semaphore::post() 
{
#ifdef WIN32
    if (ReleaseSemaphore(HANDLE(handle), 1, nil) == 0)
        sem_fail();
#else
    if (sem_post(&handle) != 0)
        sem_fail();
#endif
}

#endif // __DARWIN__

PTYPES_END

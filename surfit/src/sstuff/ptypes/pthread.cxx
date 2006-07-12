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


thread::thread(bool iautofree)
    :
#ifdef WIN32
    id(0),
#endif
    handle(-1), autofree(iautofree), 
    running(0), signaled(0), finished(false), relaxsem(0) {}


thread::~thread() 
{
    if (handle != -1)
        fatal(CRIT_FIRST + 46, "Attempt to free a working thread (need to call waitfor())");
}


void thread::signal() 
{
    if (pexchange(&signaled, 1) == 0)
        relaxsem.post();
}


void thread::waitfor() 
{
#ifdef WIN32
    HANDLE h = (HANDLE)pexchange(&handle, -1);
    if ((int)h != -1)
    {
        WaitForSingleObject(h, INFINITE);
        CloseHandle(h);
    }
#else
    pthread_t h = (pthread_t)pexchange(&handle, -1);
    if ((int)h != -1)
    {
        pthread_join(h, nil);
        pthread_detach(h);
    }
#endif
}


#ifdef WIN32
ulong WINAPI _threadproc(void* arg) 
{
#else
void* _threadproc(void* arg) 
{
#endif
    thread* thr = (thread*)arg;
    try 
    {
        thr->execute();
    }
    catch(exceptobj*) 
    {
        _threadepilog(thr);
        throw;
    }
    _threadepilog(thr);
    return 0;
}


void _threadepilog(thread* thr) 
{
    thr->cleanup();
    thr->finished = true;
    if (thr->autofree)
        delete thr;
}


void thread::start() 
{
    if (pexchange(&running, 1) == 0)
    {
#ifdef WIN32
        handle = (int)CreateThread(nil, 0, _threadproc, this, 0, &id);
        if (handle == 0)
            fatal(CRIT_FIRST + 40, "CreateThread() failed");
#else
        if (pthread_create((pthread_t*)&handle, nil, _threadproc, this) != 0)
            fatal(CRIT_FIRST + 40, "pthread_create() failed");
#endif
    }
}


PTYPES_END

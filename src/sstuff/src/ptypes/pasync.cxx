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
#  include <stdlib.h>
#  include <unistd.h>
#  include <pthread.h>
#endif

#include "pasync.h"


PTYPES_BEGIN


void psleep(uint milliseconds) 
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}


pthread_t pthrself() 
{
#ifdef WIN32
    return GetCurrentThreadId();
#else
    return pthread_self();
#endif
}


bool pthrequal(pthread_t id) 
{
#ifdef WIN32
    return GetCurrentThreadId() == (ulong)id;
#else
    return pthread_equal(pthread_self(), id);
#endif
}


PTYPES_END

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
#endif

#include "pasync.h"


PTYPES_BEGIN

//
// In order to implement SMP-safe atomic functions (exchange/increment/
// decrement) we use either of:
//
//   Win32: InterlockedXXX
//   other i386 platforms with GCC: GNU's inline assembly with
//       corresponding Pentium instructions
//   other "dumb" or unknown platforms: slow, slow mutex locks
//
// For "dumb" platforms we declare a table of mutex objects. For each lock 
// requested on a memory address a (random) mutex object is selected. This is
// a slow solution and highly depends on the implementation of POSIX threads.
//
// Desperately need help here with other CPU's to implement fast atomic ops!
//

#if defined(__GNUC__) && (defined(__i386__) || defined(__I386__))
#  define GCC_i386
#endif


//
// WIN32
//

#ifdef WIN32

int pexchange(int* target, int value)
{
    return InterlockedExchange((long*)target, (long)value);
}


int pincrement(int* target)
{
    return InterlockedIncrement((long*)target);
}


int pdecrement(int* target)
{
    return InterlockedDecrement((long*)target);
}


//
// GNU C compiler on any i386 platform (actually 486+ for xaddl)
//

#elif defined(GCC_i386)

int pexchange(int* target, int value)
{
    __asm__ __volatile ("lock ; xchgl (%1),%0" : "+r" (value) : "r" (target));
    return value;
}


int pincrement(int* target)
{
    int temp = 1;
    __asm__ __volatile ("lock ; xaddl %0,(%1)" : "+r" (temp) : "r" (target));
    return temp + 1;
}


int pdecrement(int* target)
{
    int temp = -1;
    __asm__ __volatile ("lock ; xaddl %0,(%1)" : "+r" (temp) : "r" (target));
    return temp - 1;
}


//
// other "dumb" or unknown platforms
//

#else

// we use a prime number for hashing
const int MUTEX_HASH_SIZE = 17;


#define MTX_INIT PTHREAD_MUTEX_INITIALIZER
#define mtx_t pthread_mutex_t
#define mtx_lock pthread_mutex_lock
#define mtx_unlock pthread_mutex_unlock


static mtx_t mutextbl[MUTEX_HASH_SIZE] = {
    MTX_INIT, MTX_INIT,
    MTX_INIT, MTX_INIT,
    MTX_INIT, MTX_INIT,
    MTX_INIT, MTX_INIT,
    MTX_INIT, MTX_INIT,
    MTX_INIT, MTX_INIT,
    MTX_INIT, MTX_INIT,
    MTX_INIT, MTX_INIT,
    MTX_INIT
};




inline mtx_t* pgetmemlock(void* addr)
{
    return mutextbl + uint(addr) % MUTEX_HASH_SIZE;
}


int pexchange(int* target, int value)
{
    mtx_t* m = pgetmemlock(target);
    mtx_lock(m);
    int r = *target;
    *target = value;
    mtx_unlock(m);
    return r;
}


int pincrement(int* target)
{
    mtx_t* m = pgetmemlock(target);
    mtx_lock(m);
    int r = ++(*target);
    mtx_unlock(m);
    return r;
}


int pdecrement(int* target)
{
    mtx_t* m = pgetmemlock(target);
    mtx_lock(m);
    int r = --(*target);
    mtx_unlock(m);
    return r;
}


#endif



PTYPES_END

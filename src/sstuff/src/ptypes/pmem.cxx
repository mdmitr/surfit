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

#include <stdlib.h>

#include "pport.h"


PTYPES_BEGIN


void memerror() 
{
    fatal(CRIT_FIRST + 5, "Not enough memory");
}


void* memalloc(uint a) 
{
    void* p = malloc(a);
    if (a > 0 && p == nil) 
        memerror();
    return p;
}


void* memrealloc(void* p, uint a) 
{
    p = realloc(p, a);
    if (a > 0 && p == nil) 
        memerror();
    return p;
}


void memfree(void* p) 
{
    if (p != nil)
        free(p);
}


PTYPES_END

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

#include "ptypes.h"


PTYPES_BEGIN


exceptobj::exceptobj(const char* imsg)
    : message(imsg) 
{
}


exceptobj::exceptobj(const string imsg) 
    : message(imsg) 
{
}


exceptobj::~exceptobj() 
{
}


PTYPES_END

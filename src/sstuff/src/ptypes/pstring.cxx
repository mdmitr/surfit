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
#include <string.h>
#include <time.h>

#include "ptypes.h"
#include "pasync.h"	// for atomic increment and decrement


PTYPES_BEGIN


static void stringoverflow() 
{
    fatal(CRIT_FIRST + 21, "String overflow");
}


const int quant = 16;
const int qmask = ~15;

int    stralloc;
char   emptystrbuf[strrecsize + 4];
char*  emptystr = emptystrbuf + strrecsize;


string nullstring;


inline int quantize(int numchars) 
{
    return (numchars + 1 + strrecsize + quant - 1) & qmask;
}


inline int memsize(int numchars) 
{
    return numchars == 0 ? 0 : quantize(numchars);
}


void string::_alloc(int numchars) 
{
    if (numchars <= 0) stringoverflow();
    size_t a = quantize(numchars);
    stralloc += a;
    data = (char*)(memalloc(a)) + strrecsize;
    STR_LENGTH(data) = numchars;
    STR_REFCOUNT(data) = 1;
    data[numchars] = 0;
}


/*

//
// reallocation will only be useful for the single-threaded version
// of PTypes in the future
//

void string::_realloc(int numchars) 
{
    if (numchars <= 0 || STR_LENGTH(data) <= 0)
        stringoverflow();
    int a = quantize(numchars);
    int b = quantize(STR_LENGTH(data));
    if (a != b)
    {
        stralloc += a - b;
        data = (char*)(memrealloc(data - strrecsize, a)) + strrecsize;
    }
    STR_LENGTH(data) = numchars;
    data[numchars] = 0;
}
*/


void string::_free() 
{
    stralloc -= quantize(STR_LENGTH(data));
    memfree((char*)(STR_BASE(data)));
    data = emptystr;
}


void string::initialize(const char* sc, int initlen) 
{
    if (initlen <= 0 || sc == nil)
        data = emptystr; 
    else 
    {
        _alloc(initlen);
        memmove(data, sc, initlen);
    }
}


void string::initialize(const char* sc) 
{
    initialize(sc, hstrlen(sc));
}


void string::initialize(char c) 
{
    _alloc(1);
    data[0] = c;
}


void string::initialize(const string& s)
{
    data = s.data;
    pincrement(&STR_REFCOUNT(data));
}


void string::finalize() 
{
    if (STR_LENGTH(data) != 0 && (pdecrement(&STR_REFCOUNT(data))) == 0)
        _free();
    data = emptystr;
}


/*

//
// a fatser, single-threaded version of unique()
// will be used in the future for the single-threaded version of PTypes
// 

char* unique(string& s) 
{
    if (!isempty(s) && refcount(s) > 1)
    {
        char* olddata = s.data;
        s._alloc(length(s));
        memcpy(s.data, olddata, length(s));
        STR_REFCOUNT(olddata)--;
    }
    return s.data;
}
*/


char* unique(string& s) 
{
    if (!isempty(s))
    {
        // by creating a local temporary copy of this object we "lock" the buffer
        // from being concurrently unique'd
        string t(s);
        
        // if refcount > 2 it means it was actually > 1 before
        if (refcount(t) > 2)
        {
            // now we create a new buffer and copy the contents to it;
            // note that refcount(s) is still > 2 in order to keep it locked
            t._alloc(length(s));
            memcpy(t.data, s.data, length(s));
            
            // since we detached t "illegally" we should now decrement the ref count by hand
            // and see if the buffer has become unique while we were copying it (this may 
            // happen if a concurrent thread is calling unique() simultaneously!)
            if (pdecrement(&STR_REFCOUNT(s.data)) == 0)
                s._free();
            
            // and finally, detach the old buffer (and possibly free it) and then
            // assign the newly created buffer
            s.assign(t);
        }
    }

    // at this point t is being destroyed and s is guaranteed to be unique (I hope so... :))
    return s.data;
}


void setlength(string& s, int newlen)
{
    int curlen = length(s);
    if (newlen < 0) 
        return;
    
    // if becoming empty
    if (newlen == 0)
        s.finalize();
    
    // if otherwise s was empty before
    else if (curlen == 0)
        s._alloc(newlen);
    
    // no reallocation is needed, but setlength() guarantees to always return
    // a unique string, so...
    else if (curlen == newlen)
        unique(s);

    // thread-safe reallocation; see comments in unique() for explanations
    else
    {
        string t(s);
        t._alloc(newlen);
        memcpy(t.data, s.data, imin(curlen, newlen));
        if (pdecrement(&STR_REFCOUNT(s.data)) == 0)
            s._free();
        s.assign(t);
    }
}


string dup(const string& s)
{
    return string(s.data, length(s));
}


void string::assign(const char* sc, int initlen) 
{
    finalize();
    initialize(sc, initlen);
}


void string::assign(const char* sc) 
{
    finalize();
    initialize(sc);
}


void string::assign(char c) 
{
    finalize();
    initialize(c);
}


void string::assign(const string& s) 
{
    finalize();
    initialize(s);
}


string nowstring(const char* fmt, bool utc)
{
    time_t longtime;
    time(&longtime);
    tm* t;
    if (utc)
        t = gmtime(&longtime);
    else
        t = localtime(&longtime);
    char buf[128];
    int r = strftime(buf, sizeof(buf), fmt, t);
    buf[r] = 0;
    return buf;
}


PTYPES_END

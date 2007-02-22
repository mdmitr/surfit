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

#ifndef __PPORT_H__
#define __PPORT_H__

//
// From now on we always work inside the PTypes namespace "pt",
// unlike previous versions of the library, where the namespace
// declaration was conditional
//

#define PTYPES_NAMESPACE pt

//
// conditional namespace declarations
//

#ifdef PTYPES_NAMESPACE
#  define PTYPES_BEGIN      namespace PTYPES_NAMESPACE {
#  define PTYPES_END        }
#  define USING_PTYPES      using namespace PTYPES_NAMESPACE;
#else
#  define PTYPES_NAMESPACE
#  define PTYPES_BEGIN
#  define PTYPES_END
#  define USING_PTYPES
#endif


PTYPES_BEGIN

//
// windows/msc/bcc specific
//

#ifdef _MSC_VER
// we don't want "unreferenced inline function" warning
#  pragma warning (disable: 4514)
#endif

#if defined(__WIN32__) && !defined(WIN32)
#  define WIN32
#endif

#if defined(__APPLE__)
#  define __DARWIN__
#endif

// CHECK_BOUNDS affects the way an item is retrieved from the
// following container objects: string, objlist, strlist.

#if defined(_DEBUG) && !defined(DEBUG)
#  define DEBUG
#endif


#ifdef DEBUG
#  define CHECK_BOUNDS
#endif


//
// useful typedefs
//

typedef size_t    uint;
typedef unsigned long   ulong;
typedef unsigned short  ushort;
typedef unsigned char   uchar;
typedef signed char     schar;
typedef char*           pchar;
typedef const char*     pconst;
typedef void*           ptr;
typedef int*            pint;


//
// portable 64-bit integers:
//

#if defined(_MSC_VER) || defined(__BORLANDC__)
   typedef __int64             large;
   typedef unsigned __int64    ularge;
#else
   typedef long long           large;
   typedef unsigned long long  ularge;
#endif


#if defined(_MSC_VER) || defined(__BORLANDC__)
#  define strcasecmp stricmp
#  define snprintf _snprintf
#  define atoll _atoi64
#endif


//
// misc.
//

#define nil 0

inline int   imax(int x, int y)       { return (x > y) ? x : y; }
inline int   imin(int x, int y)       { return (x < y) ? x : y; }
inline large lmax(large x, large y)   { return (x > y) ? x : y; }
inline large lmin(large x, large y)   { return (x < y) ? x : y; }


//
// critical error processing
//

#define CRIT_FIRST 0xC0000

typedef void (*_pcrithandler)(int code, const char* msg);

_pcrithandler getcrithandler();
_pcrithandler setcrithandler(_pcrithandler newh);

void fatal(int code, const char* msg);


//
// memory management
//

void* memalloc(uint a);
void* memrealloc(void* p, uint a);
void memfree(void* p);
void memerror();


PTYPES_END

#endif // __PPORT_H__

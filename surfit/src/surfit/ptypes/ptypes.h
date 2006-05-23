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

#ifndef __PTYPES_H__
#define __PTYPES_H__


#ifndef _INC_STRING
#include <string.h>
#endif

#ifndef __PPORT_H__
#include "pport.h"
#endif


PTYPES_BEGIN


#ifdef _MSC_VER
#pragma pack(push, 4)
#endif

// -------------------------------------------------------------------- //
// ---  string class -------------------------------------------------- //
// -------------------------------------------------------------------- //


struct _strrec 
{
    int refcount;
    int length;
};
typedef _strrec* _pstrrec;


#define STR_BASE(x)      (_pstrrec(x)-1)
#define STR_REFCOUNT(x)  (STR_BASE(x)->refcount)
#define STR_LENGTH(x)    (STR_BASE(x)->length)

const int strrecsize = sizeof(_strrec);

extern char* emptystr;
extern int   stralloc;


class string 
{
protected:
  char* data;

  void _alloc(int);
  void _free();

  void initialize()                             { data = emptystr; }
  void initialize(const char*, int);
  void initialize(const char*);
  void initialize(char);
  void initialize(const string& s);
  void initialize(const char*, int, const char*, int);
  void finalize();

  void assign(const char*, int);
  void assign(const char*);
  void assign(const string&);
  void assign(char);

  string(const char* s1, int len1, const char* s2, int len2)  { initialize(s1, len1, s2, len2); }

public:
  friend inline int  length(const string& s)    { return STR_LENGTH(s.data); }
  friend inline int  refcount(const string& s)  { return STR_REFCOUNT(s.data); }
  friend inline void assign(string& s, 
      const char* buf, int len)                 { s.assign(buf, len); }
  friend inline void clear(string& s)           { s.finalize(); }
  friend inline bool isempty(const string& s)   { return length(s) == 0; }

  friend void   setlength(string&, int);
  friend char*  unique(string&);
  friend void   concat(string& s, const char* sc, int catlen);
  friend void   concat(string& s, const char* s1);
  friend void   concat(string& s, char s1);
  friend void   concat(string& s, const string& s1);
  friend string copy(const string& s, int from, int cnt);
  friend void   ins(const char* s1, int s1len, string& s, int at);
  friend void   ins(const char* s1, string& s, int at);
  friend void   ins(char s1, string& s, int at);
  friend void   ins(const string& s1, string& s, int at);
  friend void   del(string& s, int at, int cnt);
  friend int    pos(const char* s1, const string& s);
  friend int    pos(char s1, const string& s);
  friend int    rpos(char s1, const string& s);
  friend bool   contains(const char* s1, int len, const string& s, int at);
  friend bool   contains(const char* s1, const string& s, int at);
  friend bool   contains(char s1, const string& s, int at);
  friend bool   contains(const string& s1, const string& s, int at);
  friend inline int pos(const string& s1, 
      const string& s)                          { return pos(s1.data, s); }
  friend string dup(const string& s);

  string()                                      { initialize(); }
  string(const char* sc, int initlen)           { initialize(sc, initlen); }
  string(const char* sc)                        { initialize(sc); }
  string(char c)                                { initialize(c); }
  string(const string& s)                       { initialize(s); }
  ~string()                                     { finalize(); }

  string& operator=  (const char* sc)           { assign(sc); return *this; }
  string& operator=  (char c)                   { assign(c); return *this; }
  string& operator=  (const string& s)          { assign(s); return *this; }
  string& operator+= (const char* sc)           { concat(*this, sc); return *this; }
  string& operator+= (char c)                   { concat(*this, c); return *this; }
  string& operator+= (const string& s)          { concat(*this, s); return *this; }

  string  operator+  (const char* sc) const;
  string  operator+  (char c) const;
  string  operator+  (const string& s) const;

  friend string operator+ (const char* sc, const string& s);
  friend string operator+ (char c, const string& s);

  bool    operator== (const char* sc) const     { return strcmp(data, sc) == 0; }
  bool    operator== (char) const;
  bool    operator== (const string&) const;
  bool    operator!= (const char* sc) const     { return !(*this == sc); }
  bool    operator!= (char c) const             { return !(*this == c); }
  bool    operator!= (const string& s) const    { return !(*this == s); }
  operator const char*() const                  { return data; }

#ifdef CHECK_BOUNDS
  char&   operator[] (int i);
#else
  char&   operator[] (int i)                    { return unique(*this)[i]; }
#endif

  friend inline void initialize(string& s)      { s.initialize(); }
  friend inline void initialize(string& s, 
      const string& s1)                         { s.initialize(s1); }
  friend inline void finalize(string& s)        { s.finalize(); }
};


typedef string* pstring;


extern string nullstring;


// -------------------------------------------------------------------- //
// ---  string utilities ---------------------------------------------- //
// -------------------------------------------------------------------- //


string fill(int width, char pad);
string itobase(large value, int base, int width = 0, char pad = 0);
string itostring(int v);
string itostring(large v);

string lowercase(const char* s);
string lowercase(const string& s);
char   hex4(char c);

inline char locase(char c) 
    { if (c >= 'A' && c <= 'Z') return char(c + 32); return c; }

inline char upcase(char c) 
    { if (c >= 'a' && c <= 'z') return char(c - 32); return c; }

inline int hstrlen(const char* p) // some Unix systems do not accept NULL
    { return p == nil ? 0 : strlen(p); }




// -------------------------------------------------------------------- //
// ---  character set class ------------------------------------------- //
// -------------------------------------------------------------------- //


const int  _csetbits = 256;
const int  _csetbytes = _csetbits / 8;
const int  _csetwords = _csetbytes / sizeof(int);
const char _csetesc = '~';


class cset 
{
protected:
    char data[_csetbytes];

    void assign(const cset& s)                  { memcpy(data, s.data, _csetbytes); }
    void assign(const char* setinit);
    void clear()                                { memset(data, 0, _csetbytes); }
    void fill()                                 { memset(data, -1, _csetbytes); }
    void include(char b)                        { data[uchar(b) / 8] |= uchar(1 << (uchar(b) % 8)); }
    void include(char min, char max);
    void exclude(char b)                        { data[uchar(b) / 8] &= uchar(~(1 << (uchar(b) % 8))); }
    void unite(const cset& s);
    void subtract(const cset& s);
    void intersect(const cset& s);
    void invert();
    bool contains(char b) const                 { return (data[uchar(b) / 8] & (1 << (uchar(b) % 8))) != 0; }
    bool eq(const cset& s) const                { return memcmp(data, s.data, _csetbytes) == 0; }
    bool le(const cset& s) const;

public:
    cset()                                      { clear(); }
    cset(const cset& s)                         { assign(s); }
    cset(const char* setinit)                   { assign(setinit); }

    cset& operator=  (const cset& s)            { assign(s); return *this; }
    cset& operator+= (const cset& s)            { unite(s); return *this; }
    cset& operator+= (char b)                   { include(b); return *this; }
    cset  operator+  (const cset& s) const      { cset t = *this; return t += s; }
    cset  operator+  (char b) const             { cset t = *this; return t += b; }
    cset& operator-= (const cset& s)            { subtract(s); return *this; }
    cset& operator-= (char b)                   { exclude(b); return *this; }
    cset  operator-  (const cset& s) const      { cset t = *this; return t -= s; }
    cset  operator-  (char b) const             { cset t = *this; return t -= b; }
    cset& operator*= (const cset& s)            { intersect(s); return *this; }
    cset  operator*  (const cset& s) const      { cset t = *this; return t *= s; }
    cset  operator!  () const                   { cset t = *this; t.invert(); return t; }
    bool  operator== (const cset& s) const      { return eq(s); }
    bool  operator!= (const cset& s) const      { return !eq(s); }
    bool  operator<= (const cset& s) const      { return le(s); }
    bool  operator>= (const cset& s) const      { return s.le(*this); }

    friend inline cset operator+ (char b, 
        const cset& s)                          { return s + b; }
    friend inline bool operator& (char b, 
        const cset& s)                          { return s.contains(b); }
    friend inline void assign(cset& s, 
        const char* setinit)                    { s.assign(setinit); }
    friend inline void clear(cset& s)           { s.clear(); }
    friend inline void fill(cset& s)            { s.fill(); }
    friend inline void include(cset& s, char b) { s.include(b); }
    friend inline void exclude(cset& s, char b) { s.exclude(b); }
    friend inline void include(cset& s, 
        char min, char max)                     { s.include(min, max); }

    friend string asstring(const cset& s);
};


// -------------------------------------------------------------------- //
// ---  basic abstract class ------------------------------------------ //
// -------------------------------------------------------------------- //


class unknown 
{
public:
    unknown();
    virtual ~unknown();
};

typedef unknown* punknown;


extern int objalloc;


// -------------------------------------------------------------------- //
// ---  component ----------------------------------------------------- //
// -------------------------------------------------------------------- //


class objlist;

class component: public unknown 
{
protected:
    objlist* freelist;
    virtual void freenotify(component* sender);
public:
    component();
    virtual ~component();
    void addnotification(component* obj);
    void delnotification(component* obj);
};

typedef component* pcomponent;


// -------------------------------------------------------------------- //
// ---  exception class ----------------------------------------------- //
// -------------------------------------------------------------------- //


class exceptobj: public unknown 
{
protected:
    string message;
public:
    exceptobj(const char* imsg);
    exceptobj(const string imsg);
    virtual ~exceptobj();
    virtual string get_message() { return message; }
};


// -------------------------------------------------------------------- //
// ---  object list --------------------------------------------------- //
// -------------------------------------------------------------------- //


class objlist: public unknown 
{
protected:
    unknown**   list;
    int         count;
    int         capacity;
    bool        ownobjects;

    void idxerror() const;

    void setcapacity(int newcap);
    int  getcount() const { return count; }
    void setcount(int newcount);
    void grow();
    void clear();
    void insitem(int i, unknown* iobj);
    void putitem(int i, unknown* iobj);
    void delitem(int i);
    unknown* getitem(int i) const  { return list[i]; }

public:
    objlist();
    objlist(bool iownobjects);
    virtual ~objlist();

    void checkidx(int i) const                      { if (i < 0 || i >= count) idxerror(); }

    friend inline int length(const objlist& s)      { return s.getcount(); }
    friend inline void setlength(objlist& s, 
        int newcount)                               { s.setcount(newcount); }
    friend inline void clear(objlist& s)            { s.clear(); }
    friend void ins(objlist& s, int i, unknown* iobj);
    friend int add(objlist& s, unknown* iobj);
    friend void put(objlist& s, int i, unknown* iobj);
    friend void del(objlist& s, int i);
    friend int indexof(const objlist& s, unknown* iobj);
    friend unknown* pop(objlist& s);
    friend inline unknown* top(const objlist& s)    { return get(s, length(s) - 1); }
    friend inline int push(objlist& s, 
        unknown* obj)                               { return add(s, obj); }

#ifdef CHECK_BOUNDS
    friend unknown* get(const objlist& s, int i);
#else
    friend inline unknown* get(const objlist& s, 
        int i)                                      { return s.getitem(i); }
#endif

    unknown* operator[] (int i) const               { return getitem(i); }
};


// -------------------------------------------------------------------- //
// ---  string list --------------------------------------------------- //
// -------------------------------------------------------------------- //


struct _stritem 
{
    string str;
    unknown* obj;
};

typedef _stritem* pstritem;
const int _stritemsize = sizeof(_stritem);

enum slflags 
{
    SL_SORTED = 0x0001,
    SL_DUPLICATES = 0x0002,
    SL_CASESENS = 0x0004,
    SL_OWNOBJECTS = 0x0008
};


class strlist: public unknown 
{
protected:
    _stritem*   list;
    int         count;
    int         capacity;
    slflags     flags;

    void idxerror() const;
    void sortederror() const;
    void notsortederror() const;
    void duperror() const;

    void setcapacity(int newcap);
    int  getcount() const { return count; }
    void grow();
    void clear();
    int  compare(const char* s1, const char* s2) const;
    bool search(const char* s, int& index) const;
    void insitem(int i, const string& istr, unknown* iobj);
    void putstr(int i, const string& istr);
    void putobj(int i, unknown* iobj);
    void delitem(int i);
    const string& getstr(int i) const  { return list[i].str; }
    unknown* getobj(int i) const  { return list[i].obj; }

public:
    strlist();
    strlist(slflags iflags);
    virtual ~strlist();

    void checkidx(int i) const                  { if (i < 0 || i >= count) idxerror(); }
    bool get_sorted() const                     { return (SL_SORTED & flags) != 0; }
    bool get_duplicates() const                 { return (SL_DUPLICATES & flags) != 0; }
    bool get_casesens() const                   { return (SL_CASESENS & flags) != 0; }
    bool get_ownobjects() const                 { return (SL_OWNOBJECTS & flags) != 0; }
    int  get_capacity() const                   { return capacity; }

    friend inline int  length(const strlist& s) { return s.getcount(); }
    friend inline void clear(strlist& s)        { s.clear(); }
    friend bool search(const strlist& s, const char* istr, int& index);
    friend void ins(strlist& s, int i, const string& istr, unknown* iobj);
    friend int  add(strlist& s, const string& istr, unknown* iobj);
    friend void put(strlist& s, int i, const string& istr, unknown* iobj);
    friend void put(strlist& s, int i, unknown* iobj);
    friend void del(strlist& s, int i);
    friend int  find(const strlist& s, const char* istr);
    friend int  indexof(const strlist& s, unknown* iobj);
    friend string valueof(const strlist& s, const char* key);

#ifdef CHECK_BOUNDS
    friend const string& getstr(const strlist& s, int i);
    friend unknown* get(const strlist& s, int i);
#else
    friend const string& getstr(const strlist& s, int i) { return s.getstr(i); }
    friend inline unknown* get(const strlist& s, int i)  { return s.getobj(i); }
#endif

    unknown* operator[] (int i) const                    { return getobj(i); }
};


// -------------------------------------------------------------------- //
// ---  string map ---------------------------------------------------- //
// -------------------------------------------------------------------- //


class strmap: protected strlist 
{
protected:
    unknown* getobj(const char* istr) const;
    void putobj(const string& istr, unknown* iobj);
public:
    strmap();
    strmap(slflags iflags);
    virtual ~strmap();

    unknown* operator[] (const string& istr)    { return getobj(istr); }
    friend inline int length(const strmap& s)   { return s.getcount(); }
    friend inline void clear(strmap& m)         { m.clear(); }
    friend inline unknown* get(const strmap& m, 
        const char* istr)                       { return m.getobj(istr); }
    friend inline void put(strmap& m, 
        const string& istr, unknown* iobj)      { m.putobj(istr, iobj); }

    friend void del(strmap& m, const string& istr);
};



#ifdef _MSC_VER
#pragma pack(pop)
#endif

PTYPES_END

#endif // __PTYPES_H__

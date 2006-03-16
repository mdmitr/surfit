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

#ifndef __PASYNC_H__
#define __PASYNC_H__

#ifdef WIN32
#  include <windows.h>
#else
#  include <pthread.h>
#  include <semaphore.h>
#endif

#ifndef __PPORT_H__
#include "pport.h"
#endif

#ifndef __PTYPES_H__
#include "ptypes.h"
#endif


PTYPES_BEGIN


#ifdef WIN32
  typedef int pthread_t;
  typedef HANDLE sem_t;
#endif


int pexchange(int* target, int value);
int pincrement(int* target);
int pdecrement(int* target);

void psleep(uint milliseconds);
bool pthrequal(pthread_t id);
pthread_t pthrself();

#define FREEANDNULL(x) { delete punknown(pexchange((int*)&(x), 0)); }


// -------------------------------------------------------------------- //
// --- mutex ---------------------------------------------------------- //
// -------------------------------------------------------------------- //


#ifdef WIN32

class mutex
{
protected:
    CRITICAL_SECTION critsec;
public:
    mutex()         { InitializeCriticalSection(&critsec); }
    ~mutex()        { DeleteCriticalSection(&critsec); }
    void enter()    { EnterCriticalSection(&critsec); }
    void leave()    { LeaveCriticalSection(&critsec); }
};


#else

struct mutex
{
protected:
    pthread_mutex_t mtx;
public:
    mutex()          { pthread_mutex_init(&mtx, 0); }
    ~mutex()         { pthread_mutex_destroy(&mtx); }
    void enter()     { pthread_mutex_lock(&mtx); }
    void leave()     { pthread_mutex_unlock(&mtx); }
};

#endif


// -------------------------------------------------------------------- //
// --- semaphore ------------------------------------------------------ //
// -------------------------------------------------------------------- //


#ifdef __DARWIN__

// POSIX semaphores aren't working on Darwin (sem_init() always returns error)
// so we use our own mutex/rwlock implementation of semaphores

class tsemaphore;
typedef tsemaphore semaphore;

#else

class semaphore: public unknown
{
protected:
    sem_t handle;
    friend class thread;
public:
    semaphore(int initvalue);
    virtual ~semaphore();

    void wait();  // decrement and wait if < 0
    void post();  // increment
    void signal()  { post(); }
};

#endif

#ifdef WIN32

class tsemaphore: public semaphore
{
protected:
public:
    tsemaphore(int initvalue);
    virtual ~tsemaphore();
    bool wait(int msecs);
};


#else

class tsemaphore: public unknown
{
protected:
    int count;
    pthread_mutex_t mtx;
    pthread_cond_t cond;
public:
    tsemaphore(int initvalue);
    virtual ~tsemaphore();
    void wait();
    void post();
    void signal()  { post(); }
    bool wait(int msecs);
};

#endif


// -------------------------------------------------------------------- //
// --- thread --------------------------------------------------------- //
// -------------------------------------------------------------------- //


class thread: public unknown
{
protected:
#ifdef WIN32
    ulong id;
#endif
    int  handle;
    bool autofree;
    int  running;
    int  signaled;
    bool finished;
    tsemaphore relaxsem;

    virtual void execute() = 0;
    virtual void cleanup() = 0;

    bool relax(int msecs) { return relaxsem.wait(msecs); }

    friend void _threadepilog(thread* thr);

#ifdef WIN32
    friend ulong __stdcall _threadproc(void* arg);
#else
    friend void* _threadproc(void* arg);
#endif

public:
    thread(bool iautofree);
    virtual ~thread();

#ifdef WIN32
    pthread_t  get_id()   { return pthread_t(id); }
#else
    pthread_t  get_id()   { return pthread_t(handle); }
#endif

    bool get_running()    { return running != 0; }
    bool get_finished()   { return finished; }
    bool get_signaled()   { return signaled != 0; }

    void start();
    void signal();
    void waitfor();
};



// -------------------------------------------------------------------- //
// --- msgqueue ------------------------------------------------------- //
// -------------------------------------------------------------------- //


const int MSG_USER = 0;
const int MSG_USER_MAX = 0xBFFFF;
const int MSG_LIB = 0xC0000;
const int MSG_QUIT = MSG_LIB;

class message: unknown
{
protected:
    message* next;          // next in the message chain, used internally
    semaphore* sync;        // used internally by msgqueue::send(), when called from a different thread
    friend class msgqueue;  // my friend, message queue...
public:
    int id;
    int result;
    int param;
    message(int iid, int iparam = 0);
    virtual ~message();
};


class msgqueue
{
private:
    int       owner;        // thread calling run() or processX()
    message*  head;         // queue head
    message*  tail;         // queue tail
    int       qcount;       // number of items in the queue
    semaphore sem;          // queue semaphore
    mutex     critsec;      // critical sections in enqueue and dequeue

    void enqueue(message* msg);
    void push(message* msg);
    message* dequeue(bool safe = true);

    void purgequeue();
    int  finishmsg(message* msg);
    void handlemsg(message* msg);
    void takeownership();
    void cancelownership();

protected:
    bool quit;

    void defhandler(message& msg);
    virtual void msghandler(message& msg) = 0;

public:
    msgqueue();
    virtual ~msgqueue();

    // functions calling from the owner thread:
    int  msgsavail()  { return qcount; }
    void processone();  // process one message, may hang if no msgs in the queue
    void processmsgs(); // process all available messages and return
    void run();         // process messages until MSG_QUIT

    // functions calling from any thread:
    void post(message* msg);
    void post(int id, int param = 0);
    void posturgent(message* msg);
    void posturgent(int id, int param = 0);
    int  send(message* msg);
    int  send(int id, int param = 0);
};


PTYPES_END

#endif // __PASYNC_H__

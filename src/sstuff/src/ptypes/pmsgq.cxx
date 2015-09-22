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

#include "pasync.h"


PTYPES_BEGIN


message::message(int iid, int iparam)
    : next(nil), sync(nil), id(iid), 
      result(0), param(iparam)  
{
}


message::~message()  
{
    if (sync != nil)
        delete sync;
}


msgqueue::msgqueue()
    : owner(0), head(nil), tail(nil), qcount(0), 
      sem(0), critsec(), quit(false)  
{ 
}


msgqueue::~msgqueue() 
{
    purgequeue();
}


static void msgerror() 
{
    fatal(CRIT_FIRST + 42, "Invalid message object");
}


void msgqueue::takeownership() 
{
    if (pexchange(&owner, int(pthrself())) != 0)
        fatal(CRIT_FIRST + 45, "Ownership of the message queue already taken");
}


inline void msgqueue::cancelownership()
{
    owner = 0;
}


void msgqueue::enqueue(message* msg) 
{
    if (msg == nil)
        msgerror();

    critsec.enter();
    msg->next = nil;
    if (head != nil)
        head->next = msg;
    head = msg;
    if (tail == nil)
        tail = msg;
    qcount++;
    critsec.leave();
    sem.post();
}


void msgqueue::push(message* msg) 
{
    if (msg == nil)
        msgerror();

    critsec.enter();
    msg->next = tail;
    tail = msg;
    if (head == nil)
        head = msg;
    qcount++;
    critsec.leave();
    sem.post();
}


message* msgqueue::dequeue(bool safe) 
{
    sem.wait();
    if (safe)
        critsec.enter();
    message* msg = tail;
    tail = msg->next;
    qcount--;
    if (tail == nil)
        head = nil;
    if (safe)
        critsec.leave();
    return msg;
}


void msgqueue::purgequeue() 
{
    critsec.enter();
    while (msgsavail() > 0)
        delete dequeue(false);
    critsec.leave();
}


void msgqueue::post(message* msg) 
{
    enqueue(msg);
}


void msgqueue::post(int id, int param) 
{
    post(new message(id, param));
}


void msgqueue::posturgent(message* msg) 
{
    push(msg);
}


void msgqueue::posturgent(int id, int param) 
{
    posturgent(new message(id, param));
}


int msgqueue::finishmsg(message* msg) 
{
    if (msg != nil) 
    {
        int result = msg->result;

        // if the message was sent by send(), 
        // just signale the semaphore
        if (msg->sync != nil)
        {
            msg->sync->post();
        }

        // otherwise finish him!
        else
        {
            delete msg;
        }
        
        return result;
    }
    else
        return 0;
}


int msgqueue::send(message* msg) 
{
    if (msg == nil)
        msgerror();

    try 
    {
        // if we are in the main thread, 
        // immediately handle the msg
        if (pthrequal(pthread_t(owner))) 
        {
            handlemsg(msg);
        }
        
        // if this is called from a concurrent thread,
        // sync through a semaphore
        else 
        {
            if (msg->sync != nil)
                msgerror();
            msg->sync = new semaphore(0);
            push(msg);
            msg->sync->wait();
            FREEANDNULL(msg->sync);
        }
    }
    catch (...) 
    {
        finishmsg(msg);
        throw;
    }

    return finishmsg(msg);
}


int msgqueue::send(int id, int param) 
{
    return send(new message(id, param));
}


void msgqueue::processone() 
{
    takeownership();
    message* msg = dequeue();
    try 
    {
        handlemsg(msg);
    }
    catch(...) 
    {
        cancelownership();
        finishmsg(msg);
        throw;
    }
    cancelownership();
    finishmsg(msg);
}


void msgqueue::processmsgs() 
{
    while (!quit && msgsavail() > 0)
        processone();
}


void msgqueue::run() 
{
    while (!quit)
        processone();
}


void msgqueue::handlemsg(message* msg) 
{
    msghandler(*msg);
}


void msgqueue::defhandler(message& msg) 
{
    switch(msg.id) 
    {
    case MSG_QUIT:
        quit = true;
        break;
    }
}


PTYPES_END

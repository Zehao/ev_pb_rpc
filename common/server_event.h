//
// Created by Zehao Jin on 18/03/2018.
//

#ifndef EV_PB_RPC_SERVER_EVENT_H
#define EV_PB_RPC_SERVER_EVENT_H


#include<event.h>

static struct event_base *server_event_base = NULL;

event_base *GetServerEventBase()
{
    return server_event_base;
}

void SetServerEventBase(event_base *base)
{
    server_event_base = base;
}


#endif //EV_PB_RPC_SERVER_EVENT_H

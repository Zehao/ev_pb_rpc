//
// Created by Zehao Jin on 18/03/2018.
//
#include <event.h>
#include "log.h"
#include "server_event.h"
#include "listener.h"

void InitEventBase()
{
    auto base = event_base_new();
    if(base == NULL){
        log("create event base failed");
        return;
    }
    SetServerEventBase(base);
}

void StartBaseLoop()
{
    auto base = GetServerEventBase();
    event_base_dispatch(base);
}

int main()
{
    InitEventBase();

    Listener listener("0.0.0.0", 8899);
    listener.Listen();

    StartBaseLoop();
    return 0;
}
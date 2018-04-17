//
// Created by Zehao Jin on 18/03/2018.
//

#ifndef EV_PB_RPC_LISTENER_H
#define EV_PB_RPC_LISTENER_H

#include <event.h>
#include <functional>
#include <string>



class Listener {

public:
    bool Listen();
    void Stop();
    ~Listener();
    explicit Listener(const std::string &host, int port);

    static void AcceptCallback(evutil_socket_t fd, short events, void *args);


private:
    int socket_fd;

    std::string host;
    int port;

    struct event ev;
};


#endif //EV_PB_RPC_LISTENER_H

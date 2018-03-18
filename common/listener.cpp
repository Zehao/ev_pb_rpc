//
// Created by Zehao Jin on 18/03/2018.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include "listener.h"
#include "log.h"

event_base *GetServerEventBase();

void SetServerEventBase(event_base *base);

bool Listener::Listen()
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd <= 0){
        log("Create socket failed");
        return false;
    }

    if(evutil_make_socket_nonblocking(socket_fd) < 0)
    {
        log("make non-block failed");
        evutil_closesocket(socket_fd);
        return false;
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    auto tmp_addr = host.c_str();
    if(evutil_inet_pton(AF_INET, tmp_addr, (void *)&server_addr.sin_addr) < 0)
    {
        log("inet_pton failed");
        evutil_closesocket(socket_fd);
        return false;
    }

    if(evutil_make_listen_socket_reuseable(socket_fd) < 0)
    {
        log("reuse error");
        evutil_closesocket(socket_fd);
        return false;
    }

    if(bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        log("bind error");
        evutil_closesocket(socket_fd);
        return false;
    }

    if(listen(socket_fd, SOMAXCONN) < 0)
    {
        log("listen failed");
        evutil_closesocket(socket_fd);
        return false;
    }

    event_assign(&ev, GetServerEventBase(), socket_fd, EV_READ|EV_PERSIST, AcceptCallback, this);
    if(event_add(&ev, nullptr) < 0)
    {
        log("event add failed");
        evutil_closesocket(socket_fd);
        return false;
    }
    log("start listen %s:%d, fd=%d", host.c_str(), port, socket_fd);
    return true;
}

Listener::Listener(const std::string &host, int port)
{
    this->host = host;
    this->port = port;
    socket_fd = 0;
}

void Listener::AcceptCallback(evutil_socket_t fd, short events, void *args)
{
    auto listener = reinterpret_cast<Listener *>(args);
    struct sockaddr_in conn_addr;
    auto len = sizeof(conn_addr);
    bzero(&conn_addr, len);
    auto conn_fd = accept(fd, (struct sockaddr *)&conn_addr, reinterpret_cast<socklen_t *>(&len));
    log("serverfd:%d connfd:%d, errno:%d", fd, conn_fd, errno);
    if (conn_fd < 0){
        log("accept error");
        return;
    }
    if(evutil_make_socket_nonblocking(conn_fd) < 0)
        return;
    char ip[20];
    const char *sp = evutil_inet_ntop(AF_INET, (void *)&conn_addr.sin_addr, ip, sizeof(ip));
    log("connected:fd=%d, ip=%s", conn_fd, sp);

}

Listener::~Listener()
{
    this->Stop();
}

void Listener::Stop()
{
    if(!event_initialized(&ev))
        return;

    event_del(&ev);
    bzero(&ev, sizeof(ev));
    evutil_closesocket(socket_fd);
    socket_fd = 0;
}


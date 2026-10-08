#pragma once

#include <winsock2.h>

class Application;

class SocketServer
{
public:
    SocketServer();
    ~SocketServer();

    bool start(unsigned short port);
    void run(Application& app);

private:
    SOCKET m_listenSocket;
    SOCKET m_clientSocket;
    bool m_wsaStarted;
};
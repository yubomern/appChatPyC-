#include "SocketServer.h"
#include "Application.h"
#include "CommandExecutor.h"
#include <iostream>
#include <string>

#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
SocketServer::SocketServer()
    : m_listenSocket(INVALID_SOCKET),
      m_clientSocket(INVALID_SOCKET),
      m_wsaStarted(false)
{
}

SocketServer::~SocketServer()
{
    if (m_clientSocket != INVALID_SOCKET)
    {
        closesocket(m_clientSocket);
    }

    if (m_listenSocket != INVALID_SOCKET)
    {
        closesocket(m_listenSocket);
    }

    if (m_wsaStarted)
    {
        WSACleanup();
    }
}

bool SocketServer::start(unsigned short port)
{
    WSADATA wsaData{};

    int result = WSAStartup(
        MAKEWORD(2, 2),
        &wsaData
    );

    if (result != 0)
    {
        std::cerr << "WSAStartup failed: "
                  << result << '\n';

        return false;
    }

    m_wsaStarted = true;

    // --------------------------------
    // Create socket
    // --------------------------------

    m_listenSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP
    );

    if (m_listenSocket == INVALID_SOCKET)
    {
        std::cerr << "socket failed: "
                  << WSAGetLastError()
                  << '\n';

        return false;
    }

    // --------------------------------
    // Server address
    // --------------------------------

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;

    // Local only for a safer demo.
    inet_pton(
        AF_INET,
        "127.0.0.1",
        &serverAddress.sin_addr
    );

    serverAddress.sin_port = htons(port);

    // --------------------------------
    // Bind
    // --------------------------------

    result = bind(
        m_listenSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    );

    if (result == SOCKET_ERROR)
    {
        std::cerr << "bind failed: "
                  << WSAGetLastError()
                  << '\n';

        return false;
    }

    // ---------*----------------------
    // List*n
    // -------------------------*------

    result = listen(
        m_listenSocket,
        SOMAXCONN
    );

    if (result == SOCKET_ERROR)
    {
        std::cerr << "listen failed: "
                  << WSAGetLastError()
                  << '\n';

        return false;
    }

    std::cout
        << "SServer listening on 127.0.0.1:"
        << port
        << '\n';

    return true;
}

void SocketServer::run(Application& app)
{
    std::cout << "Waiting for client...\n";

    m_clientSocket = accept(
        m_listenSocket,
        nullptr,
        nullptr
    );

    if (m_clientSocket == INVALID_SOCKET)
    {
        std::cerr << "accept failed: "
                  << WSAGetLastError()
                  << '\n';
        return;
    }

    std::cout << "Client connected\n";

    char buffer[1024];

    while (true)
    {
        int received = recv(
            m_clientSocket,
            buffer,
            sizeof(buffer),
            0
        );

        if (received == 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }

        if (received == SOCKET_ERROR)
        {
            std::cerr << "recv failed: "
                      << WSAGetLastError()
                      << '\n';

            break;
        }

        std::string command(
            buffer,
            received
        );

        // Remove CR/LF from t*lnet-style input.
        while (!command.empty() &&
               (command.back() == '\r' ||
                command.back() == '\n'))
        {
            command.pop_back();
        }

        std::cout
           << "Request: "
           << command
            << '\n';

       std::string response =
           CommandExecutor::execute(command);

        size_t sentTotal = 0;

       while (sentTotal < response.size())
        {
            int sent = send(
                m_clientSocket,
                response.data() + sentTotal,
                static_cast<int>(
                    response.size() - sentTotal
                ),
                0
           );

            if (sent == SOCKET_ERROR)
            {
               std::cerr
                  << "send failed: "
                  << WSAGetLastError()
                  << '\n';

               return;
            }

          sentTotal +=
               static_cast<size_t>(sent);
      }
    }
}
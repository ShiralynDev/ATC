#include "tcpSocket.hpp"
#include <iostream>

namespace Networking {
    TcpSocket::TcpSocket(int SocketDomain, int SocketType, int Protocol) {
        socketFd = socket(SocketDomain, SocketType, Protocol);

        if (socketFd == -1) {
            std::cerr << "Failed to open socket: " << errno << std::endl;
            return;
        }

        socketAddress.sin_family = SocketDomain;
        socketAddress.sin_addr.s_addr = htonl(address);
        socketAddress.sin_port = htons(port);
    }
}
#ifdef __linux__
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <unistd.h>
#elif _WIN32
    #include <winsock2.h>
#endif

#include "../../utils.hpp"

namespace Networking {

    class TcpSocket : private Utils::NoCopy { // add windows support
    private:
        sockaddr_in socketAddress;
        in_port_t port = 1337;
        in_addr_t address = INADDR_LOOPBACK;
        int socketFd;
    public:
        TcpSocket(int SocketDomain = AF_INET, int SocketType = SOCK_STREAM | SOCK_NONBLOCK, int Protocol = 0); // AF_UNIX = local communication, allow other types later
        int bind();
        int connect();            
    };
}
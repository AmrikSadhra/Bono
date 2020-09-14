#include "udp_client.h"

#define BUFLEN 512 // Max length of buffer

namespace Bono
{
    UdpClient::UdpClient(const std::string &ipAddress, uint32_t port)
    {
        WSADATA wsa;

        // Initialise winsock
        printf("Initialising Winsock...");
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        {
            printf("Failed. Error Code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
        if ((m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
        {
            printf("socket() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        // Setup socket descriptor
        sockaddr_in socketInfo = {};
        socketInfo.sin_family           = AF_INET;
        socketInfo.sin_port             = htons(port);
        socketInfo.sin_addr.S_un.S_addr = inet_addr(ipAddress.c_str());

        ::bind(m_socket, (SOCKADDR*) &socketInfo, sizeof(socketInfo));

        char buf[BUFLEN];
        int slen = 0;

        // start communication
        while (1)
        {
            // Clear the buffer and block to receive data from the socket
            memset(buf, '\0', BUFLEN);
            if (recvfrom(m_socket, buf, BUFLEN, 0, (struct sockaddr *) &socketInfo, &slen) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code : %d", WSAGetLastError());
                exit(EXIT_FAILURE);
            }
            puts(buf);
        }
    }

    UdpClient::~UdpClient()
    {
        closesocket(m_socket);
        WSACleanup();
    }
} // namespace Bono

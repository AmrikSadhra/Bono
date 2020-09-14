#pragma once

#include <winsock2.h>
#include <string>

namespace Bono
{
    class UdpClient
    {
    public:
        explicit UdpClient(const std::string &ipAddress, uint32_t port);
        ~UdpClient();
    private:
        SOCKET m_socket;
    };
} // namespace Bono


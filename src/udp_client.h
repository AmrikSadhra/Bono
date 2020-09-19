#pragma once

#include <array>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "config.h"
#include "gamedata.h"

namespace Bono
{
    class UdpClient
    {
    public:
        UdpClient(const std::string& ipAddress, uint32_t port, const std::shared_ptr<RaceDataBuffer>& gameData);
        void Receive();
        void Shutdown();

    private:
        void _HandleReceive(const boost::system::error_code& error, size_t bytes_transferred);
        void _Wait();

        // Boost UDP Primitives
        boost::asio::io_service m_ioService;
        boost::asio::ip::udp::socket m_socket{m_ioService};
        std::array<char, 1024> m_receiveBuffer = {};
        boost::asio::ip::udp::endpoint m_remoteEndpoint;

        // Gamedata
        std::shared_ptr<RaceDataBuffer> m_gameData;
    };
} // namespace Bono

#pragma once

#include <array>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>

#include "packets.h"

namespace Bono
{
    const uint32_t MAX_NUM_PACKETS = 100;

    class UdpClient
    {
    public:
        UdpClient(const std::string& ipAddress, uint32_t port);
        void Receive();

        // Lets protect the dumbass circular buffers from concurrent access on render thread
        std::mutex mtxData;

        // F1 2019 Data
        boost::circular_buffer<PacketMotionData> motionData;
        boost::circular_buffer<PacketSessionData> sessionData;
        boost::circular_buffer<PacketLapData> lapData;
        boost::circular_buffer<PacketEventData> eventData;
        boost::circular_buffer<PacketParticipantsData> participantsData;
        boost::circular_buffer<PacketCarSetupData> carSetupData;
        boost::circular_buffer<PacketCarTelemetryData> carTelemetryData;
        boost::circular_buffer<PacketCarStatusData> carStatusData;

    private:
        void _HandleReceive(const boost::system::error_code& error, size_t bytes_transferred);
        void _Wait();

        // Boost UDP Primitives
        boost::asio::io_service m_ioService;
        boost::asio::ip::udp::socket m_socket{m_ioService};
        std::array<char, 1024> m_receiveBuffer = {};
        boost::asio::ip::udp::endpoint m_remoteEndpoint;
    };
} // namespace Bono

#include "udp_client.h"

using boost::asio::ip::udp;
using boost::asio::ip::address;

namespace Bono
{
    UdpClient::UdpClient(const std::string &ipAddress, uint32_t port) :
        motionData(MAX_NUM_PACKETS), sessionData(MAX_NUM_PACKETS), lapData(MAX_NUM_PACKETS),
        eventData(MAX_NUM_PACKETS), participantsData(MAX_NUM_PACKETS), carSetupData(MAX_NUM_PACKETS),
        carTelemetryData(MAX_NUM_PACKETS), carStatusData(MAX_NUM_PACKETS)
    {
        m_socket.open(udp::v4());
        m_socket.bind(udp::endpoint(address::from_string("127.0.0.1"), port));
    }

    void UdpClient::Receive()
    {
        // Queue initial async callback
        this->_Wait();

        // Start to service the queue
        std::cout << "Receiving\n";
        m_ioService.run();
        std::cout << "Receiver exit\n";
    }

    void UdpClient::_HandleReceive(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if (error)
        {
            std::cout << "Receive failed: " << error.message() << "\n";
            return;
        }

        // Take the lock until end of scope
        const std::lock_guard<std::mutex> lock(mtxData);

        // Check the packet type
        auto *packetHeader = reinterpret_cast<PacketHeader*>(m_receiveBuffer.data());
        switch(packetHeader->packetId)
        {
        case PacketType::Motion:
            motionData.push_back(*reinterpret_cast<PacketMotionData*>(m_receiveBuffer.data()));
            break;
        case PacketType::Session:
            sessionData.push_back(*reinterpret_cast<PacketSessionData*>(m_receiveBuffer.data()));
            break;
        case PacketType::LapData:
            lapData.push_back(*reinterpret_cast<PacketLapData*>(m_receiveBuffer.data()));
            break;
        case PacketType::Event:
            eventData.push_back(*reinterpret_cast<PacketEventData*>(m_receiveBuffer.data()));
            break;
        case PacketType::Participants:
            participantsData.push_back(*reinterpret_cast<PacketParticipantsData*>(m_receiveBuffer.data()));
            break;
        case PacketType::CarSetups:
            carSetupData.push_back(*reinterpret_cast<PacketCarSetupData*>(m_receiveBuffer.data()));
            break;
        case PacketType::CarTelemetry:
            carTelemetryData.push_back(*reinterpret_cast<PacketCarTelemetryData*>(m_receiveBuffer.data()));
            break;
        case PacketType::CarStatus:
            carStatusData.push_back(*reinterpret_cast<PacketCarStatusData*>(m_receiveBuffer.data()));
            break;
        }

        // Requeue the callback
        this->_Wait();
    }

    void UdpClient::_Wait()
    {
        m_socket.async_receive_from(boost::asio::buffer(m_receiveBuffer),m_remoteEndpoint,
                                  boost::bind(&UdpClient::_HandleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

    }
} // namespace Bono

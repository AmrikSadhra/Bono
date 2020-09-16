#pragma once

#include <boost/circular_buffer.hpp>
#include <mutex>
#include <vector>

#include "packets.h"

namespace Bono
{
    class GameData
    {
    public:
        explicit GameData(const size_t kBufferSize) :
            m_motionData(kBufferSize),
            m_sessionData(kBufferSize),
            m_lapData(kBufferSize),
            m_eventData(kBufferSize),
            m_participantsData(kBufferSize),
            m_carSetupData(kBufferSize),
            m_carTelemetryData(kBufferSize),
            m_carStatusData(kBufferSize)
        {
        }

        void PushMotionData(PacketMotionData motionData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_motionData.push_back(motionData);
        }

        // TODO: Taking vector copies per frame is FUCKING STUPID
        std::vector<PacketMotionData> GetMotionData()
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            return std::vector<PacketMotionData>(m_motionData.begin(), m_motionData.end());
        }

        void PushSessionData(PacketSessionData sessionData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_sessionData.push_back(sessionData);
        }

        std::vector<PacketMotionData> GetSessionData()
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            return std::vector<PacketMotionData>(m_motionData.begin(), m_motionData.end());
        }

        void PushCarTelemetryData(PacketCarTelemetryData carTelemetryData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_carTelemetryData.push_back(carTelemetryData);
        }

        std::vector<PacketCarTelemetryData> GetCarTelemetryData()
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            return std::vector<PacketCarTelemetryData>(m_carTelemetryData.begin(), m_carTelemetryData.end());
        }

    private:
        // Lets protect the dumbass circular buffers from concurrent access on threads
        std::mutex m_mtxData;

        // F1 2019 Data
        boost::circular_buffer<PacketMotionData> m_motionData;
        boost::circular_buffer<PacketSessionData> m_sessionData;
        boost::circular_buffer<PacketLapData> m_lapData;
        boost::circular_buffer<PacketEventData> m_eventData;
        boost::circular_buffer<PacketParticipantsData> m_participantsData;
        boost::circular_buffer<PacketCarSetupData> m_carSetupData;
        boost::circular_buffer<PacketCarTelemetryData> m_carTelemetryData;
        boost::circular_buffer<PacketCarStatusData> m_carStatusData;
    };
} // namespace Bono

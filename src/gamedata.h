#pragma once

#include <boost/circular_buffer.hpp>
#include <mutex>
#include <vector>

#include "packets.h"

namespace Bono
{
    class RaceDataBuffer
    {
    public:
        explicit RaceDataBuffer(const size_t kBufferSize) :
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

        PacketMotionData GetMotionData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);

            dataAvailable = !m_motionData.empty();

            PacketMotionData carMotionPkt = {};
            if(dataAvailable)
            {
                carMotionPkt = m_motionData.front();
                m_motionData.pop_front();
            }

            return carMotionPkt;
        }

        void PushSessionData(PacketSessionData sessionData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_sessionData.push_back(sessionData);
        }

        PacketSessionData GetSessionData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            dataAvailable = !m_sessionData.empty();

            PacketSessionData sessionPkt = {};
            if(dataAvailable)
            {
                sessionPkt = m_sessionData.front();
                m_sessionData.pop_front();
            }

            return sessionPkt;
        }

        void PushLapData(PacketLapData LapData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_lapData.push_back(LapData);
        }

        PacketLapData GetLapData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            dataAvailable = !m_lapData.empty();

            PacketLapData LapPkt = {};
            if(dataAvailable)
            {
                LapPkt = m_lapData.front();
                m_lapData.pop_front();
            }

            return LapPkt;
        }

        void PushEventData(PacketEventData EventData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_eventData.push_back(EventData);
        }

        PacketEventData GetEventData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            dataAvailable = !m_eventData.empty();

            PacketEventData EventPkt = {};
            if(dataAvailable)
            {
                EventPkt = m_eventData.front();
                m_eventData.pop_front();
            }

            return EventPkt;
        }

        void PushParticipantsData(PacketParticipantsData ParticipantsData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_participantsData.push_back(ParticipantsData);
        }

        PacketParticipantsData GetParticipantsData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            dataAvailable = !m_participantsData.empty();

            PacketParticipantsData ParticipantPkt = {};
            if(dataAvailable)
            {
                ParticipantPkt = m_participantsData.front();
                m_participantsData.pop_front();
            }

            return ParticipantPkt;
        }

        void PushCarSetupData(PacketCarSetupData CarSetupData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_carSetupData.push_back(CarSetupData);
        }

        PacketCarSetupData GetCarSetupData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            dataAvailable = !m_carSetupData.empty();

            PacketCarSetupData ParticipantPkt = {};
            if(dataAvailable)
            {
                ParticipantPkt = m_carSetupData.front();
                m_carSetupData.pop_front();
            }

            return ParticipantPkt;
        }
        
        void PushCarTelemetryData(PacketCarTelemetryData carTelemetryData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_carTelemetryData.push_back(carTelemetryData);
        }

        PacketCarTelemetryData GetCarTelemetryData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            dataAvailable = !m_carTelemetryData.empty();

            PacketCarTelemetryData carTelemetryPkt = {};
            if(dataAvailable)
            {
                carTelemetryPkt = m_carTelemetryData.front();
                m_carTelemetryData.pop_front();
            }

            return carTelemetryPkt;
        }

        void PushCarStatusData(PacketCarStatusData carStatusData)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            m_carStatusData.push_back(carStatusData);
        }

        PacketCarStatusData GetCarStatusData(bool &dataAvailable)
        {
            const std::lock_guard<std::mutex> lock(m_mtxData);
            dataAvailable = !m_carStatusData.empty();

            PacketCarStatusData carStatusPkt = {};
            if(dataAvailable)
            {
                carStatusPkt = m_carStatusData.front();
                m_carStatusData.pop_front();
            }

            return carStatusPkt;
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

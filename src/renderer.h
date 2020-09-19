#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include <memory>
#include <iostream>
#include "config.h"
#include "gamedata.h"
#include "udp_client.h"

enum WindowStatus : uint8_t
{
    UI,
    GAME
};

#define CHANNEL_COUNT 4

namespace Bono
{
    // Utility structure for realtime plot
    struct ScrollingBuffer
    {
        std::string name;
        bool show;
        int MaxSize;
        int Offset;
        ImVector<ImVec2> Data;
        ScrollingBuffer()
        {
            MaxSize = 2000;
            Offset  = 0;
            Data.reserve(MaxSize);
            show = false;
            name = "Undefined";
        }
        void AddPoint(float x, float y)
        {
            if (Data.size() < MaxSize)
                Data.push_back(ImVec2(x, y));
            else
            {
                Data[Offset] = ImVec2(x, y);
                Offset       = (Offset + 1) % MaxSize;
            }
        }
        void Erase()
        {
            if (!Data.empty())
            {
                Data.shrink(0);
                Offset = 0;
            }
        }
    };

    const std::string analogueChannelNames[] = {"Throttle", "Brake", "Steering", "Speed"};

    class Renderer
    {
    public:
        explicit Renderer(std::shared_ptr<RaceDataBuffer> gameData);
        ~Renderer();
        void Render();

    private:
        void _InitOpenGL(uint32_t resolutionX, uint32_t resolutionY, const std::string &windowName);
        void _InitIMGUI();
        void _BeginFrame();
        void _DrawUI();
        void _EndFrame();
        // TODO: Move somewhere else
        void _GetData();

        static inline void GlfwError(int id, const char *description) { std::cerr << description; }
        static inline void _WindowSizeCallback(GLFWwindow *window, int width, int height)
        {
            Config::get().windowWidth  = width;
            Config::get().windowHeight = height;
            glViewport(0, 0, width, height);
        }

        std::shared_ptr<GLFWwindow> m_window;
        WindowStatus m_windowStatus = WindowStatus::UI;

        // UDP buffered data from F1 2019
        std::shared_ptr<RaceDataBuffer> m_raceDataBuffer;

        // TODO: Migrate these elsewhere
        // Long term analysis and render buffers
        std::vector<PacketMotionData> m_motionData;
        std::vector<PacketSessionData> m_sessionData;
        std::vector<PacketLapData> m_lapData;
        std::vector<PacketEventData> m_eventData;
        std::vector<PacketParticipantsData> m_participantsData;
        std::vector<PacketCarSetupData> m_carSetupData;
        std::vector<PacketCarTelemetryData> m_carTelemetryData;
        std::vector<PacketCarStatusData> m_carStatusData;

        bool paused = false;
        ScrollingBuffer dataChannels[CHANNEL_COUNT];
    };
} // namespace Bono

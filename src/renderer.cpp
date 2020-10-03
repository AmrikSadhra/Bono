#include "renderer.h"

#include <implot.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace Bono
{
    Renderer::Renderer(const std::shared_ptr<RaceDataBuffer> raceDataBuffer) : m_raceDataBuffer(raceDataBuffer)
    {
        this->_InitOpenGL(Config::get().windowWidth, Config::get().windowWidth, "Bono!");
        this->_InitIMGUI();

        for (int i = 0; i < CHANNEL_COUNT; ++i)
            dataChannels[i].name = analogueChannelNames[i];
    }

    Renderer::~Renderer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
    }

    void Renderer::Render()
    {
        while (!glfwWindowShouldClose(m_window.get()))
        {
            // glfwGetTime is called only once, the first time this function is called
            static double lastTime = glfwGetTime();
            // Compute time difference between current and last frame
            double currentTime = glfwGetTime();
            // Update time between engine ticks
            auto deltaTime = float(currentTime - lastTime); // Keep track of time between engine ticks

            // Clear the screen for next input and grab focus
            this->_BeginFrame();

            // Retrieve data from UDP buffers
            // TODO: Move this elsewhere
            this->_GetData();

            // Actual Render here
            this->_DrawUI();

            // Draw the UI VAOs and swap buffers
            this->_EndFrame();

            // For the next frame, the "last time" will be "now"
            lastTime = currentTime;
        }
    }

    void Renderer::_InitOpenGL(uint32_t resolutionX, uint32_t resolutionY, const std::string& windowName)
    {
        // Initialise GLFW
        if (glfwInit() == GLFW_FALSE)
        {
            std::cerr << "GLFW Init failed.";
            getchar();
            glfwTerminate();
        }
        glfwSetErrorCallback(&Renderer::GlfwError);

        glfwWindowHint(GLFW_SAMPLES, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(resolutionX, resolutionY, windowName.c_str(), nullptr, nullptr), [](GLFWwindow* w) { glfwTerminate(); });
        if (m_window == nullptr)
        {
            std::cerr << "Failed to create a GLFW window.";
            getchar();
            glfwTerminate();
        }
        glfwMakeContextCurrent(m_window.get());
        glfwSetWindowSizeCallback(m_window.get(), Renderer::_WindowSizeCallback);

        // Initialize GLEW
        glewExperimental = GL_TRUE; // Needed for core profile
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW";
            getchar();
            glfwTerminate();
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(m_window.get(), GLFW_STICKY_KEYS, GL_TRUE);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::_InitIMGUI()
    {
        ImGui::CreateContext();
        ImPlot::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(m_window.get(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
        // Enable VTX offset support to handle large indices
        ImGui::GetIO().BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
    }

    void Renderer::_BeginFrame()
    {
        // Clear the screen
        glClearColor(0.1f, 0.f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Get any queued GLFW input events
        glfwPollEvents();

        // Setup the IMGUI VAO's
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Detect a click on the 3D Window by detecting a click that isn't on ImGui
        if ((glfwGetMouseButton(m_window.get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && (!ImGui::GetIO().WantCaptureMouse))
        {
            m_windowStatus                 = WindowStatus::GAME;
            ImGui::GetIO().MouseDrawCursor = false;
        }
        else if (glfwGetKey(m_window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            m_windowStatus                 = WindowStatus::UI;
            ImGui::GetIO().MouseDrawCursor = true;
        }
    }

    void Renderer::_GetData()
    {
        bool isDataAvailable = false;
        PacketMotionData motionPkt = m_raceDataBuffer->GetMotionData(isDataAvailable);
        if (isDataAvailable)
        {
            m_motionData.push_back(motionPkt);
        }
        PacketSessionData sessionPkt = m_raceDataBuffer->GetSessionData(isDataAvailable);
        if (isDataAvailable)
        {
            m_sessionData.push_back(sessionPkt);
        }
        PacketLapData lapPkt = m_raceDataBuffer->GetLapData(isDataAvailable);
        if (isDataAvailable)
        {
            m_lapData.push_back(lapPkt);
        }
        PacketEventData eventPkt = m_raceDataBuffer->GetEventData(isDataAvailable);
        if (isDataAvailable)
        {
            m_eventData.push_back(eventPkt);
        }
        PacketParticipantsData participantsPkt = m_raceDataBuffer->GetParticipantsData(isDataAvailable);
        if (isDataAvailable)
        {
            m_participantsData.push_back(participantsPkt);
        }
        PacketCarSetupData carSetupPkt = m_raceDataBuffer->GetCarSetupData(isDataAvailable);
        if (isDataAvailable)
        {
            m_carSetupData.push_back(carSetupPkt);
        }
        PacketCarTelemetryData carTelemetryPkt = m_raceDataBuffer->GetCarTelemetryData(isDataAvailable);
        if (isDataAvailable)
        {
            m_carTelemetryData.push_back(carTelemetryPkt);
        }
        PacketCarStatusData carStatusPkt = m_raceDataBuffer->GetCarStatusData(isDataAvailable);
        if (isDataAvailable)
        {
            m_carStatusData.push_back(carStatusPkt);
        }
    }

    void Renderer::_DrawUI()
    {
        // Most structures contain 20 cars – this is the maximum that can be in a race in the game.
        // There is a data item called m_numActiveCars in the participants packet which tells you how many cars are active in the race.
        // However, you should check the individual result status of each car in the lap data to see if that car is actively providing data.
        // If it is not “Invalid” or “Inactive” then the corresponding vehicle index has valid data.

        // for(uint8_t uCarIdx = 0; uCarIdx <  m_participantsData.back().numActiveCars; ++uCarIdx)
        // {
        //     m_participantsData.back().participants[uCarIdx].name;
        //     m_lapData.back().lapData[uCarIdx].resultStatus == 2;
        // }

        if (ImGui::CollapsingHeader("Telemetry Trace"))
        {
            ImGui::BeginGroup();

            // Buttons
            if (ImGui::Button("Clear", ImVec2(100, 0)))
            {
                for (auto& dataChannel : dataChannels)
                {
                    dataChannel.show = false;
                }
            }
            if (ImGui::Button(paused ? "Resume" : "Pause", ImVec2(100, 0)))
            {
                paused = !paused;
            }
            for (uint8_t uDataSrcIdx = 0; uDataSrcIdx < CHANNEL_COUNT; ++uDataSrcIdx)
            {
                ImGui::Checkbox(dataChannels[uDataSrcIdx].name.c_str(), &dataChannels[uDataSrcIdx].show);
                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
                {
                    ImGui::SetDragDropPayload("DND_ANALOG_PLOT", &uDataSrcIdx, sizeof(int));
                    ImGui::TextUnformatted(dataChannels[uDataSrcIdx].name.c_str());
                    ImGui::EndDragDropSource();
                }
            }
            ImGui::EndGroup();
            ImGui::SameLine();

            // Data
            static float sessionTime = 0.f;
            if (!paused)
            {
                // Analog signal values
                for (uint8_t uDataSrcIdx = 0; uDataSrcIdx < CHANNEL_COUNT; ++uDataSrcIdx)
                {
                    if (dataChannels[uDataSrcIdx].show && !m_carTelemetryData.empty())
                    {
                        const PacketCarTelemetryData& carTelemetryPacket = m_carTelemetryData.back();
                        sessionTime = carTelemetryPacket.header.sessionTime;
                        switch (uDataSrcIdx)
                        {
                        case 0:
                            dataChannels[uDataSrcIdx].AddPoint(sessionTime, carTelemetryPacket.carTelemetryData[0].throttle);
                            break;
                        case 1:
                            dataChannels[uDataSrcIdx].AddPoint(sessionTime, carTelemetryPacket.carTelemetryData[0].brake);
                            break;
                        case 2:
                            dataChannels[uDataSrcIdx].AddPoint(sessionTime, carTelemetryPacket.carTelemetryData[0].steer);
                            break;
                        case 3:
                            dataChannels[uDataSrcIdx].AddPoint(sessionTime, (float)carTelemetryPacket.carTelemetryData[0].speed);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            ImPlot::SetNextPlotLimitsY(0, 1);
            ImPlot::SetNextPlotLimitsX(sessionTime - 10.0, sessionTime, paused ? ImGuiCond_Once : ImGuiCond_Always);
            if (ImPlot::BeginPlot("##Digital"))
            {
                for (auto& dataChannel : dataChannels)
                {
                    if (dataChannel.show)
                    {
                        if (!dataChannel.Data.empty())
                            ImPlot::PlotLine(dataChannel.name.c_str(), &dataChannel.Data[0].x, &dataChannel.Data[0].y, dataChannel.Data.size(), dataChannel.Offset,
                                             2 * sizeof(float));
                    }
                }
                ImPlot::EndPlot();
            }
        }
    }

    void Renderer::_EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window.get());
    }
} // namespace Bono

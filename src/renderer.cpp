#include "renderer.h"

namespace Bono
{
    Renderer::Renderer()
    {
        this->_InitOpenGL(Config::get().windowWidth, Config::get().windowWidth, "Bono!");
        this->_InitIMGUI();
    }

    Renderer::~Renderer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    // TODO: I shouldn't be passing the entire UDP client in..
    void Renderer::Render(UdpClient *udpClient)
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

            // Actual Render here
            this->_DrawUI(udpClient);

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
        ImGui_ImplGlfw_InitForOpenGL(m_window.get(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
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

    void Renderer::_DrawUI(UdpClient *udpClient)
    {
        // TODO: Add UI code here, and feed a struct of Packets
        ImGui::Begin("Bono");

        // Take the lock from UDP client whilst the data is parsed into a renderable format
        udpClient->mtxData.lock();
        std::vector<PacketCarTelemetryData> carTelemetryDataPkts(udpClient->carTelemetryData.begin(), udpClient->carTelemetryData.end());
        udpClient->mtxData.unlock();

        // No point plotting if no data...
        if(!carTelemetryDataPkts.empty())
        {
            // TODO: Revisit fast path...
            //// Calculate the players throttle offset in the packet
            //size_t firstDriverThrottleOffset = offsetof(PacketCarTelemetryData, carTelemetryData[0].throttle);
            //firstDriverThrottleOffset += carTelemetryDataPkts[0].header.playerCarIndex * sizeof(CarTelemetryData);
            //// Floats aren't contiguous but part of a structure,pass a pointer to driver float and the sizeof() of Packet in the Stride parameter.
            //ImGui::PlotLines("Lines", (float*)(carTelemetryDataPkts.data() + firstDriverThrottleOffset) , carTelemetryDataPkts.size(), 0, "", 0.f, 1.0f, ImVec2(0,80), sizeof(PacketCarTelemetryData));
            std::vector<float> playerCarThrottleTrace;
            for(auto &carTelemetryDataPkt : carTelemetryDataPkts)
            {
                playerCarThrottleTrace.push_back(carTelemetryDataPkt.carTelemetryData[10].speed);
            }
            ImGui::PlotLines("Lines", playerCarThrottleTrace.data() , playerCarThrottleTrace.size(), 0, "", 0.f, 350.0f, ImVec2(0,80));
        }


        ImGui::End();
    }

    void Renderer::_EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window.get());
    }
} // namespace Bono

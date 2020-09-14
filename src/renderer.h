#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <memory>
#include <iostream>
#include "config.h"
#include "udp_client.h"

enum WindowStatus : uint8_t
{
    UI,
    GAME
};

namespace Bono
{
    class Renderer
    {
    public:
        explicit Renderer();
        ~Renderer();
        void Render(UdpClient *udpClient);

    private:
        void _InitOpenGL(uint32_t resolutionX, uint32_t resolutionY, const std::string &windowName);
        void _InitIMGUI();
        void _BeginFrame();
        static void _DrawUI(UdpClient *udpClient);
        void _EndFrame();

        static inline void GlfwError(int id, const char *description) { std::cerr << description; }
        static inline void _WindowSizeCallback(GLFWwindow *window, int width, int height)
        {
            Config::get().windowWidth  = width;
            Config::get().windowHeight = height;
            glViewport(0, 0, width, height);
        }

        std::shared_ptr<GLFWwindow> m_window;
        WindowStatus m_windowStatus = WindowStatus::UI;
    };
} // namespace Bono

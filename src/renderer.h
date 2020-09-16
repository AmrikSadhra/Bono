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
#include "gamedata.h"
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
        explicit Renderer(std::shared_ptr<GameData> gameData);
        ~Renderer();
        void Render();

    private:
        void _InitOpenGL(uint32_t resolutionX, uint32_t resolutionY, const std::string &windowName);
        void _InitIMGUI();
        void _BeginFrame();
        void _DrawUI();
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

        // Gamedata
        std::shared_ptr<GameData> m_gameData;
    };
} // namespace Bono

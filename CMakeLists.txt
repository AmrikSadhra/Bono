cmake_minimum_required(VERSION 3.14)
project(Bono)

set(CMAKE_CXX_STANDARD 14)

set(IMGUI_SOURCE_FILES
        lib/imgui/imgui.cpp
        lib/imgui/imgui.h
        lib/imgui/imgui_demo.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/imgui_internal.h
        lib/imgui/imconfig.h
        lib/imgui/imstb_rectpack.h
        lib/imgui/imstb_textedit.h
        lib/imgui/imstb_truetype.h
        lib/imgui/examples/imgui_impl_glfw.cpp
        lib/imgui/examples/imgui_impl_glfw.h
        lib/imgui/examples/imgui_impl_opengl3.cpp
        lib/imgui/examples/imgui_impl_opengl3.h
        lib/implot/implot.cpp
        lib/implot/implot.h
        lib/implot/implot_items.cpp
        lib/implot/implot_demo.cpp
        )

set(SOURCE_FILES
        lib/glew-cmake/src/glew.c
        src/main.cpp
        src/renderer.cpp
        src/renderer.h
        src/config.h
        src/packets.h
        src/udp_client.cpp
        src/udp_client.h
        src/gamedata.h
        src/shaders/race_shader.cpp
        src/shaders/race_shader.h
        src/shaders/base_shader.cpp
        src/shaders/base_shader.h
        src/shaders/shader_set.cpp
        src/shaders/shader_set.h
        )

add_executable(Bono ${SOURCE_FILES} ${IMGUI_SOURCE_FILES})

#[[IMGUI]]
include_directories(lib/imgui)
include_directories(lib/implot)

#[[GLEW Configuration]]
add_subdirectory(lib/glew-cmake)
target_link_libraries(Bono libglew_static)

#[[GLM Configuration]]
include_directories(lib/glm)

#[[OpenGL Configuration]]
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(Bono ${OPENGL_LIBRARIES})

#[[GLFW Configuration]]
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)
target_link_libraries(Bono glfw)

#[[Boost and winsock for ASIO - You knew it was coming, didn't ya]]
add_subdirectory(lib/boost-cmake)
target_link_libraries(Bono Boost::boost ws2_32)
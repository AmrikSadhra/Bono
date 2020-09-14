cmake_minimum_required(VERSION 3.14)
project(Bono)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
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
        lib/glew-cmake/src/glew.c
        src/main.cpp
        src/renderer.cpp
        src/renderer.h
        src/config.h
        src/packets.h
        src/udp_client.cpp
        src/udp_client.h)

add_executable(Bono  ${SOURCE_FILES})

#[[Shitty Windows only WinSock]]
target_link_libraries(Bono wsock32 ws2_32)

#[[IMGUI]]
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui")

#[[GLEW Configuration]]
add_definitions(-DGLEW_STATIC -D__NO_INLINE__)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/glew-cmake/include")

#[[GLM Configuration]]
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/glm")

#[[OpenGL Configuration]]
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(Bono ${OPENGL_LIBRARIES})

#[[GLFW Configuration]]
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw/ "${CMAKE_CURRENT_BINARY_DIR}/glfw")
target_link_libraries(Bono glfw)
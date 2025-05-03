cmake_minimum_required(VERSION 3.30)
project(hw2)

set(CMAKE_CXX_STANDARD 11)

# Find packages
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)

# Add the executable
add_executable(hw2 src/main.cpp
        headers/base.h
        src/globals.cpp
        headers/globals.h
        src/window.cpp
        src/text.cpp
        src/file_utilities.cpp
        src/shaders.cpp
        src/callback.cpp
        src/cubemap.cpp
)

# Link OpenGL, GLEW, and GLFW to the target executable
target_link_libraries(hw2 OpenGL::GL GLEW::GLEW glfw Freetype::Freetype)

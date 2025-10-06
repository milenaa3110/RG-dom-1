cmake_minimum_required(VERSION 3.16)
project(graphics_homework_1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(glfw)

add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_executable(main main.cpp
        load.h
        callbacks.h
        window.h)
target_include_directories(main PRIVATE glad/include glfw/include)
target_link_libraries(main PRIVATE glad glfw)

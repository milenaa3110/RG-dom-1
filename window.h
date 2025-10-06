#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

static int VERSION = 4;

static double scale = 1.5;
static int winWidth, winHeight;
static double aspect = 1.0;
static double centerX = -0.75, centerY = 0.0;

inline GLFWwindow *initialize() {
    if (!glfwInit()) return nullptr;
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    winWidth = mode->width;
    winHeight = mode->height;
    aspect = static_cast<double>(winWidth) / static_cast<double>(winHeight);
    GLFWwindow *window = glfwCreateWindow(
        winWidth, winHeight, "Mandelbrot set", monitor, nullptr
    );
    if (!window) {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    return window;
}
#endif

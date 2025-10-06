#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

using namespace std;

static int max_iteration = 100;
static bool dragging = false;
static double dragStartX = 0, dragStartY = 0;
static double dragCenterX = 0, dragCenterY = 0;

inline void callback_framebuffer_size(GLFWwindow *window, int width, int height) {
    winWidth = width;
    winHeight = height;
    glViewport(0, 0, width, height);
    aspect = static_cast<double>(width) / static_cast<double>(height);
}

inline void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) return;
    if (key == GLFW_KEY_KP_ADD || key == GLFW_KEY_EQUAL)
        max_iteration += 10;
    if (key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT)
        max_iteration = max(1, max_iteration - 10);
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

inline void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            dragging = true;
            glfwGetCursorPos(window, &dragStartX, &dragStartY);
            dragCenterX = centerX;
            dragCenterY = centerY;
        } else if (action == GLFW_RELEASE) {
            dragging = false;
        }
    }
}

inline void screen_to_complex(double sx, double sy, double &cx, double &cy) {
    const auto normX = sx / winWidth * 2.0 - 1.0;
    const auto normY = -(sy / winHeight * 2.0 - 1.0); 
    cx = centerX + normX * scale * aspect;
    cy = centerY + normY * scale;
}

inline void callback_cursor_position(GLFWwindow *window, double cursorX, double cursorY) {
    if (dragging) {
        const auto dx = cursorX - dragStartX;
        const auto dy = cursorY - dragStartY;
        centerX = dragCenterX + dx / winWidth * 2.0 * scale * aspect;
        centerY = dragCenterY - dy / winHeight * 2.0 * scale; 
    }
}

inline void callback_scroll(GLFWwindow *window, double scrollX, double scrollY) {
    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    double complexX, complexY;
    screen_to_complex(mx, my, complexX, complexY);
    double zoomFactor = (scrollY > 0) ? 0.9 : 1.1;
    scale *= zoomFactor;
    double normX = (mx / winWidth) * 2.0 - 1.0;
    double normY = -(my / winHeight * 2.0 - 1.0); 
    centerX = complexX - normX * scale * aspect; 
    centerY = complexY - normY * scale;
}

#endif

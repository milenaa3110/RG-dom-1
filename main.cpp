#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "callbacks.h"
#include "load.h"
#include "window.h"

int main() {
    const auto window = initialize();

    const auto vertex_shader_source = load_shader_source("../res/vertex.glsl");
    const auto fragment_shader_source = load_shader_source("../res/fragment.glsl");

    const auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const auto *vertexSourcePtr = vertex_shader_source.c_str();
    glShaderSource(vertexShader, 1, &vertexSourcePtr, nullptr);
    glCompileShader(vertexShader);

    const auto *fragmentSourcePtr = fragment_shader_source.c_str();
    const auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourcePtr, nullptr);
    glCompileShader(fragmentShader);

    const auto shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    constexpr float quadVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, 1.0f
    };
    const unsigned int quadIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, callback_scroll);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, callback_cursor_position);
    glfwSetFramebufferSizeCallback(window, callback_framebuffer_size);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        const auto loc_center = glGetUniformLocation(shader, "center");
        glUniform2f(loc_center, static_cast<float>(centerX), static_cast<float>(centerY));

        const auto loc_scale = glGetUniformLocation(shader, "scale");
        glUniform1f(loc_scale, static_cast<float>(scale));

        const auto loc_aspect = glGetUniformLocation(shader, "aspect");
        glUniform1f(loc_aspect, static_cast<float>(aspect));

        const GLint loc_iter = glGetUniformLocation(shader, "max_iteration");
        glUniform1i(loc_iter, max_iteration);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

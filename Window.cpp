#include "Engine.h"

Window::Window(int width, int height, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (m_window == NULL) {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }

    glfwMakeContextCurrent(m_window);
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

GLFWwindow* Window::getGLFWWindow() {
    return m_window;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}
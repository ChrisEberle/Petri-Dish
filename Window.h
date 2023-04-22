#pragma once

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();
    GLFWwindow* getGLFWWindow();
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    GLFWwindow* m_window;
private:
};

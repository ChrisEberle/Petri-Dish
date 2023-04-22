#include "Engine.h"

Camera2d cam;

void display(GLFWwindow& window) {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    // Apply camera transformation
    cam.apply();
    Graphics::drawCircle(0,0,450,100);

    // Swap buffers
    glfwSwapBuffers(&window);
}

void update(GLFWwindow& window, float deltaTime) {
    // Update camera position
    cam.setCameraPosition(0, 0);
}

int main() {
    // Initialize GLFW
    glfwInit();

    // Create a window and context
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL 2D Camera and Body", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Register callbacks

    // Event loop
    double prevTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        // Handle GLFW events
        glfwPollEvents();
        // Display Simulation
        update(*window, 60);
        display(*window);
    }
    // Clean up
    glfwTerminate();
    return 0;
}

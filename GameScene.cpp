#include "Engine.h"

void GameScene::display(GLFWwindow& window, Camera2d& cam)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    // Apply camera transformation
    cam.apply();
    // Draw Game
    Graphics::drawTriangle(0, 0, 50, 255, 0, 0);
    // Swap buffers
    glfwSwapBuffers(&window);
}

void GameScene::update(GLFWwindow& window, float deltaTime, Camera2d& cam)
{
    // Update camera position
    cam.setCameraPosition(0, 0);
}

int GameScene::game(int width, int height, Camera2d& cam)
{
    // Initialize GLFW
    glfwInit();
    // Create a window and context
    GLFWwindow* window = glfwCreateWindow(width, height, "Petri Dish", NULL, NULL);
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
        update(*window, 60, cam);
        display(*window, cam);
    }
    // Clean up
    glfwTerminate();
    return 0;
}

#include "Engine.h"


void GameScene::display(GLFWwindow& window, Camera2d& cam)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    // Apply camera transformation
    cam.apply();
    // Draw Game
    //Graphics::circleTextured(0, 0, 500, COLOR_DARKKHAKI, "assets/goop.jpg");
     Graphics::circle(0, 0, 500, COLOR_FIREBRICK);
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
    // Set the camera object as the user pointer for the window
    glfwSetWindowUserPointer(window, &cam);
    // Make the window's context current
    glfwMakeContextCurrent(window);
        // Register callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

  
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
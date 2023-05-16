#include "Engine.h"

void GameScene::display(GLFWwindow& window, Camera2d& cam)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // objects
    //Graphics::rectangleTextured(0, 0, 2000, 1940, COLOR_WHITE, boomTexture);
    Graphics::drawTexturePng(birdTexture, 50000, 50000);

    // ui window
     IMGUIUI::ui_tools("Developer Tools", rx,ry,rw,rh,rx, song1,effect1);
    // Swap buffers
    glfwSwapBuffers(&window);
}

void GameScene::update(GLFWwindow& window, float deltaTime, Camera2d& cam)
{
    // Apply camera transformation
    cam.apply();
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

    // load textures
    goopTexture = TextureManager::loadTextureJPEG("assets/goop.jpg");
    spaceTexture = TextureManager::loadTextureJPEG("assets/space.jpg");
    aTexture = TextureManager::loadTextureJPEG("assets/Font/A.jpg");
    birdTexture = TextureManager::loadTexturePNG("assets/bird.png");
    boomTexture = TextureManager::loadTexturePNG("assets/boom.png");

    // load audio files
    song1 = Mix_LoadMUS("audio/music/song1.wav");
    effect1 = Mix_LoadWAV("audio/soundeffects/retro1.wav");

    // initialize imgui
    IMGUIUI::init_scene(window);

    //initialize camera starting position
    cam.setCameraPosition(0, 0);

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
    IMGUIUI::clean_scene();
    glfwTerminate();
    return 0;
}
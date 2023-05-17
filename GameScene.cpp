#include "Engine.h"

void GameScene::display(GLFWwindow& window, Camera2d& cam)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // objects
    //Graphics::drawTexture(boomTexture, 500, 500, 0, 0);
    int arraysize = sizeof(textures) / sizeof(textures[0]);

    TextureManager::textureAnimation(textures, arraysize, 500, 500, 0, 0, tracker);
    
    // ui window
     IMGUIUI::ui_tools("Developer Tools", rx,ry,rw,rh,tracker, song1,effect1);
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
    // Disable VSync
    glfwSwapInterval(0);
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
    textures[0] =  TextureManager::loadTexturePNG("assets/boom.png");
    textures[1] =  TextureManager::loadTexturePNG("assets/bird.png");
    textures[2] = TextureManager::loadTexturePNG("assets/over.png");
    textures[3] = TextureManager::loadTexturePNG("assets/space.jpg");
    textures[4] = TextureManager::loadTexturePNG("assets/goop.jpg");
    textures[5] = TextureManager::loadTextureJPEG("assets/Font/A.jpg");
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
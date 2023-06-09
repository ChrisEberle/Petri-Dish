#pragma once

class GameScene
{
public:
    void display(GLFWwindow& window, Camera2d& cam);
    void update(GLFWwindow& window, float deltaTime, Camera2d& cam);
    int game(int width, int height, Camera2d& cam);
    float rx = 3240, ry = 40, rw = 30, rh = 520;
    float vars[4] = { rx,ry,rw,rh };
    int tracker = 60;
private:
    // Load the WAV audio file
    Mix_Music* song1;
    Mix_Chunk* effect1;
    // texture ID's
    // JPEGS
    unsigned int goopTexture;
    unsigned int spaceTexture;
    unsigned int aTexture;
    unsigned int overTexture;
    //PNGS
    unsigned int birdTexture;
    unsigned int boomTexture;
    unsigned int textures[6];
    

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        Camera2d* cam = static_cast<Camera2d*>(glfwGetWindowUserPointer(window));
        cam->setWindowSize(width, height);
        glViewport(0, 0, width, height);
    }

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        Camera2d* cam = static_cast<Camera2d*>(glfwGetWindowUserPointer(window));
        if (yoffset > 0) {
            cam->zoom(1.1f); // zoom in
        }
        else if (yoffset < 0) {
            cam->zoom(0.9f); // zoom out
        }
    }

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        Camera2d* cam = static_cast<Camera2d*>(glfwGetWindowUserPointer(window));
        cam->handleMouseInput(window, xpos, ypos);
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        Camera2d* cam = static_cast<Camera2d*>(glfwGetWindowUserPointer(window));
        cam->handleMouseButton(window, button, action, mods);
    }
};
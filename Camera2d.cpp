#include "Engine.h"

float Camera2d::getCameraX() const
{
    return cameraX_;
}

float Camera2d::getCameraY() const
{
    return cameraY_;
}

ImVec2 Camera2d::getPosition() const
{
    return ImVec2(cameraX_, cameraY_);
}

void Camera2d::setCameraPosition(float x, float y)
{
    cameraX_ = x;
    cameraY_ = y;
}

void Camera2d::zoom(float factor)
{
    zoom_ *= factor;
}

void Camera2d::apply()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Apply camera position and zoom
    glOrtho(cameraX_ - screenWidth_ / 2.0f / zoom_, cameraX_ + screenWidth_ / 2.0f / zoom_, cameraY_ - screenHeight_ / 2.0f / zoom_, cameraY_ + screenHeight_ / 2.0f / zoom_, -1.0f, 1.0f);

    // Apply translation
    glTranslatef(cameraX_, cameraY_, 0.0f);

    // Apply rotation transformation
    glRotatef(rotation_, 0.0f, 0.0f, 1.0f);

    // Undo translation
    glTranslatef(-cameraX_, -cameraY_, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera2d::handleMouseInput(GLFWwindow* window, double xpos, double ypos)
{
    if (isDragging_) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            // Calculate rotation amount based on mouse movement
            float deltaX = xpos - lastMouseX_;
            float deltaY = ypos - lastMouseY_;
            float sensitivity = 0.1f;
            float rotationAmount = deltaX * sensitivity;

            // Update rotation angle
            rotation_ += rotationAmount;
            if (rotation_ > 360.0f) {
                rotation_ -= 360.0f;
            }
            else if (rotation_ < 0.0f) {
                rotation_ += 360.0f;
            }
        }
        else {
            // Calculate camera movement based on mouse movement
            float deltaX = xpos - lastMouseX_;
            float deltaY = ypos - lastMouseY_;
            float speed = 0.5f / zoom_; // Calculate speed based on zoom level
            cameraX_ -= deltaX * speed;
            cameraY_ += deltaY * speed;
        }

        lastMouseX_ = xpos;
        lastMouseY_ = ypos;
    }
}

void Camera2d::handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        // ...
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            isDragging_ = true;
            glfwGetCursorPos(window, &lastMouseX_, &lastMouseY_);
        }
        else if (action == GLFW_RELEASE) {
            isDragging_ = false;
        }
    }
}



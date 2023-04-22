#pragma once

class Camera2d {
public:
    Camera2d() {
        rotation_ = 0.0f;
        cameraX_ = 0.0f;
        cameraY_ = 0.0f;
        zoom_ = 1.0f;
        isDragging_ = false;
        lastMouseX_ = 0.0f;
        lastMouseY_ = 0.0f;
        screenWidth_ = screenWidth;
        screenHeight_ = screenHeight;
    }
    float getCameraX() const;
    float getCameraY() const;
    void setCameraPosition(float x, float y);
    void zoom(float factor);
    void apply();
    void handleMouseInput(GLFWwindow* window, double xpos, double ypos);
    void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
    void setZoom(double zoomLevel) {
        zoom_ = 1.0f / (zoomLevel * 0.01f);
    }

private:
    float rotation_;
    float cameraX_;
    float cameraY_;
    double zoom_;
    bool isDragging_;
    double lastMouseX_;
    double lastMouseY_;
    float screenWidth_;
    float screenHeight_;
};

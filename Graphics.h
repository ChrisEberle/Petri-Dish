#pragma once

class Graphics {
public:
    // ELLIPSE
    static void ellipse(float cx, float cy, float cx2, float cy2, float eccentricity, const float* color);
    static void ellipseOutline(float cx, float cy, float cx2, float cy2, float eccentricity, const float* color);
    // CIRCLE
    static void circle(float centerX, float centerY, float radius, const float* color);
    static void circleOutline(float centerX, float centerY, float radius);
    static void circleTextured(float centerX, float centerY, float radius, const float* color, const char* imagePath);
    // TRIANGLE
    static void triangle(float centerX, float centerY, float sideLength, const float* color);
    static void triangleOutline(float centerX, float centerY, float sideLength, const float* color);
    static void triangleTextured(float centerX, float centerY, float sideLength, const float* color, const char* imagePath);
    // RECTANGLE
    static void rect(float x1, float y1, float x2, float y2, const float* color);
    static void rectOutline(float x1, float y1, float x2, float y2, const float* color);
    static void rectTextured(float x1, float y1, float x2, float y2, const float* color, const char* imagePath);
    // LINE
    static void drawLine(float x1, float y1, float x2, float y2, const float* color);
    // FPS
    static void drawFPS(GLFWwindow* window);
private:
};
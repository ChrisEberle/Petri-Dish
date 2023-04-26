#pragma once

class Graphics {
public:
    // ELLIPSE
    static void ellipse(float cx, float cy, float cx2, float cy2, float eccentricity, int r, int g, int b);
    static void ellipseOutline(float cx, float cy, float cx2, float cy2, float eccentricity, int r, int g, int b);
    // CIRCLE
    static void circle(float centerX, float centerY, float radius, int nSeg, int r, int g, int b);
    static void circleOutline(float centerX, float centerY, float radius);
    static void circleTextured(float centerX, float centerY, float radius, int r, int g, int b, const char* imagePath);
    // TRIANGLE
    static void triangle(float centerX, float centerY, float sideLength, int r, int g, int b);
    static void triangleOutline(float centerX, float centerY, float sideLength, int r, int g, int b);
    static void triangleTextured(float centerX, float centerY, float sideLength, int r, int g, int b, const char* imagePath);
    // RECTANGLE
    static void rect(float x1, float y1, float x2, float y2, int r, int g, int b);
    static void rectOutline(float x1, float y1, float x2, float y2, int r, int g, int b);
    static void rectTextured(float x1, float y1, float x2, float y2, int r, int g, int b, const char* imagePath);
    // LINE
    static void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
    // FPS
    static void drawFPS(GLFWwindow* window);
private:
};
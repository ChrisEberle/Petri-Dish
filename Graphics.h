#pragma once

class Graphics {
public:
    // SHAPES
    
    // ELLIPSE
    static void ellipse(float cx, float cy, float cx2, float cy2, float eccentricity, const float* color);
    static void ellipseOutline(float cx, float cy, float cx2, float cy2, float eccentricity, const float* color);
    // CIRCLE
    static void circle(float centerX, float centerY, float radius, const float* color);
    static void circleOutline(float centerX, float centerY, float radius, const float* color);
    static void circleTextured(float centerX, float centerY, float radius, const float* color, unsigned int textureID);
    // TRIANGLE
    static void triangle(float centerX, float centerY, float sideLength, const float* color);
    static void triangleOutline(float centerX, float centerY, float sideLength, const float* color);
    static void triangleTextured(float centerX, float centerY, float sideLength, const float* color, unsigned int textureID);
    // RECTANGLE
    static void rectangle(float x1, float y1, float x2, float y2, const float* color);
    static void rectangleOutline(float x1, float y1, float x2, float y2, const float* color);
    static void rectangleTextured(float x1, float y1, float x2, float y2, const float* color, unsigned int textureID);
    // LINE
    static void drawLine(float x1, float y1, float x2, float y2, const float* color);
    // FPS
    static void drawFPS(GLFWwindow* window);

    // TEXTURES

    // Function to load a texture (called once during initialization)
    static unsigned int loadTexture(const char* imagePath);

  
private:
    // This resizes the texture image depending on distance (mipmapping)
    static unsigned char* resizeImageData(const unsigned char* imageData, int srcWidth, int srcHeight, int dstWidth, int dstHeight);
};
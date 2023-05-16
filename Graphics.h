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

    static void drawTexturePng(unsigned int texture, int width, int height) {
        // Enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Enable texture functionality
        glEnable(GL_TEXTURE_2D);

        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Calculate the aspect ratio of the texture
        float aspectRatio = static_cast<float>(width) / height;

        // Calculate the quad's dimensions based on the aspect ratio
        float quadWidth = 2.0f;
        float quadHeight = 2.0f / aspectRatio;

        // Calculate the quad's position to center it on the screen
        float quadX = -quadWidth / 2.0f;
        float quadY = -quadHeight / 2.0f;

        // Enable alpha testing for transparent pixels
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);

        // Draw a quad with the texture
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(quadX, quadY);
        glTexCoord2f(1, 0);
        glVertex2f(quadX + quadWidth, quadY);
        glTexCoord2f(1, 1);
        glVertex2f(quadX + quadWidth, quadY + quadHeight);
        glTexCoord2f(0, 1);
        glVertex2f(quadX, quadY + quadHeight);
        glEnd();

        // Disable alpha testing and blending
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
    }
private:
};
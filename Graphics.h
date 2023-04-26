#pragma once

class Graphics {
public:
    static void drawCircleOutline(float x, float y, float radius, int nSeg, int r, int g, int b);
    static void drawRectangle(float x1, float y1, float x2, float y2, int r, int g, int b);
    static void drawCircle(float x, float y, float radius, int nSeg, int r, int g, int b);
    static void drawTriangle(float x, float y, float radius, int r, int g, int b);
    static void drawLine(GLFWwindow* window, float x1, float y1, float x2, float y2, int r, int g, int b);
    static void drawFPS(GLFWwindow* window);
    static void clear(GLFWwindow* window);
    static void ellipse(float cx, float cy, float cx2, float cy2, float eccentricity, int num_segments, int r, int g, int b);
    static void drawRectangleWithTexture(float x1, float y1, float x2, float y2, int r, int g, int b, const char* imagePath) {
        // Calculate the dimensions of the rectangle
        float width = abs(x2 - x1);
        float height = abs(y2 - y1);

        // Translate and rotate to the correct position and orientation
        glColor3f(1.0f, 1.0f, 1.0f);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(min(x1, x2), min(y1, y2), 0);
        if (x2 < x1 && y2 < y1) {
            glRotatef(180, 0, 0, 1);
        }
        else if (x2 < x1) {
            glRotatef(90, 0, 0, 1);
            std::swap(width, height);
        }
        else if (y2 < y1) {
            glRotatef(-90, 0, 0, 1);
            std::swap(width, height);
        }

        // Load and bind the texture
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int widthImg, heightImg, channels;
        unsigned char* image = stbi_load(imagePath, &widthImg, &heightImg, &channels, 0);
        if (image) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
           
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(image);

        // Draw the textured rectangle
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, height);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        // Draw the rectangle outline
        glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2d(0, 0);
        glVertex2d(width, 0);
        glVertex2d(width, height);
        glVertex2d(0, height);
        
        glEnd();

        glPopMatrix();
        glDeleteTextures(1, &textureID);
    }
private:
};
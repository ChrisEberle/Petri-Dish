#include "Engine.h"

void Graphics::ellipse(float cx, float cy, float cx2, float cy2, float eccentricity, const float* color)
{
    // calculate midpoint between two points
    float mx = (cx + cx2) / 2.0;
    float my = (cy + cy2) / 2.0;

    // calculate distance between the two points
    float dx = cx2 - cx;
    float dy = cy2 - cy;
    float distance = sqrt(dx * dx + dy * dy);

    // calculate semimajor and semiminor axes based on distance and eccentricity
    float a = distance / 2.0;
    float bb = a * sqrt(1.0 - eccentricity * eccentricity);

    // calculate angle between two points
    float angle = atan2(dy, dx);
    int num_segments = 320;
    float theta = 2 * M_PI / float(num_segments);
    float c = cos(theta);//precalculate the sine and cosine
    float s = sin(theta);
    float t;

    float x = 1;//we start at angle = 0 
    float y = 0;

    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[3] / 255.0f);
    // translate to center of ellipse
    glTranslatef(mx, my, 0.0f);

    // rotate to align with two points
    glRotatef(angle * 180.0 / M_PI, 0.0, 0.0, 1.0);

    // draw ellipse
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)
    {
        // apply radius and offset
        glVertex2f(a * x, bb * y);

        // apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void Graphics::ellipseOutline(float cx, float cy, float cx2, float cy2, float eccentricity, const float* color)
{
    // calculate midpoint between two points
    float mx = (cx + cx2) / 2.0;
    float my = (cy + cy2) / 2.0;

    // calculate distance between the two points
    float dx = cx2 - cx;
    float dy = cy2 - cy;
    float distance = sqrt(dx * dx + dy * dy);

    // calculate semimajor and semiminor axes based on distance and eccentricity
    float a = distance / 2.0;
    float bb = a * sqrt(1.0 - eccentricity * eccentricity);

    // calculate angle between two points
    float angle = atan2(dy, dx);
    int num_segments = 320;
    float theta = 2 * M_PI / float(num_segments);
    float c = cos(theta);//precalculate the sine and cosine
    float s = sin(theta);
    float t;

    float x = 1;//we start at angle = 0 
    float y = 0;

    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
    // translate to center of ellipse
    glTranslatef(mx, my, 0.0f);

    // rotate to align with two points
    glRotatef(angle * 180.0 / M_PI, 0.0, 0.0, 1.0);

    // draw ellipse
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        // apply radius and offset
        glVertex2f(a * x, bb * y);

        // apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void Graphics::circle(float centerX, float centerY, float radius, const float* color)
{
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);

    int nSeg = 320;
    const float theta = 2.0f * 3.1415926f / float(nSeg);
    float cos_theta = cosf(theta);
    float sin_theta = sinf(theta);
    float dx = radius;
    float dy = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= nSeg; i++) {
        glVertex2f(dx, dy);
        float temp = dx;
        dx = cos_theta * dx - sin_theta * dy;
        dy = sin_theta * temp + cos_theta * dy;
    }
    glEnd();
    glPopMatrix();
}

void Graphics::circleOutline(float centerX, float centerY, float radius) {
    // Draw the circle outline
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    int numSegments = 320;
    float anglePerSegment = 2.0f * M_PI / numSegments;
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * anglePerSegment;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void Graphics::circleTextured(float centerX, float centerY, float radius, const float* color, const char* imagePath) {
    // Translate and rotate to the correct position and orientation
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

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

    // Draw the textured circle
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    int numSegments = 320;
    float anglePerSegment = 2.0f * M_PI / numSegments;
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * anglePerSegment;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glTexCoord2f((x + radius) / (2.0f * radius), (y + radius) / (2.0f * radius));
        glVertex2f(x, y);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glDeleteTextures(1, &textureID);
}

void Graphics::triangle(float centerX, float centerY, float sideLength, const float* color)
{
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);

    const float angle = 2.0f * 3.1415926f / 3; // 3 vertices for a triangle
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float h = (sqrt(3) / 2.0f) * sideLength;

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, h / 2.0f);
    glVertex2f(-sideLength / 2.0f, -h / 2.0f);
    glVertex2f(sideLength / 2.0f, -h / 2.0f);
    glEnd();

    glPopMatrix();
}

void Graphics::triangleOutline(float centerX, float centerY, float sideLength, const float* color)
{
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);

    const float angle = 2.0f * 3.1415926f / 3; // 3 vertices for a triangle
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float h = (sqrt(3) / 2.0f) * sideLength;

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, h / 2.0f);
    glVertex2f(-sideLength / 2.0f, -h / 2.0f);
    glVertex2f(sideLength / 2.0f, -h / 2.0f);
    glEnd();

    glPopMatrix();
}

void Graphics::triangleTextured(float centerX, float centerY, float sideLength, const float* color, const char* imagePath) {
    // Translate and rotate to the correct position and orientation
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

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

    // Draw the textured triangle
    glEnable(GL_TEXTURE_2D);
    const float angle = 2.0f * M_PI / 3; // 3 vertices for a triangle
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float h = (sqrt(3) / 2.0f) * sideLength;

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 0.0f);
    glVertex2f(0.0f, h / 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-sideLength / 2.0f, -h / 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(sideLength / 2.0f, -h / 2.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glDeleteTextures(1, &textureID);
}

void Graphics::rect(float x1, float y1, float x2, float y2, const float* color) {
        // Calculate the dimensions of the rectangle
        float width = abs(x2 - x1);
        float height = abs(y2 - y1);

        // Translate and rotate to the correct position and orientation
        glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
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

        // Draw the filled-in rectangle
        glBegin(GL_QUADS);
        glVertex2d(0, 0);
        glVertex2d(width, 0);
        glVertex2d(width, height);
        glVertex2d(0, height);
        glEnd();

        glPopMatrix();
}

void Graphics::rectOutline(float x1, float y1, float x2, float y2, const float* color)
{
    // Calculate the dimensions of the rectangle
    float width = abs(x2 - x1);
    float height = abs(y2 - y1);

    // Translate and rotate to the correct position and orientation
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
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

    // Draw the rectangle outline
    glBegin(GL_LINE_LOOP);
    glVertex2d(0, 0);
    glVertex2d(width, 0);
    glVertex2d(width, height);
    glVertex2d(0, height);
    glEnd();

    glPopMatrix();
}

void Graphics::rectTextured(float x1, float y1, float x2, float y2, const float* color, const char* imagePath) {
    // Calculate the dimensions of the rectangle
    float width = abs(x2 - x1);
    float height = abs(y2 - y1);

    // Translate and rotate to the correct position and orientation
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
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

    glPopMatrix();
    glDeleteTextures(1, &textureID);
}

void Graphics::drawLine(float x1, float y1, float x2, float y2, const float* color) {
    glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    // Set the line color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    // Begin drawing the line
    glBegin(GL_LINES);

    // Specify the coordinates of the two endpoints of the line
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);

    // End drawing the line
    glEnd();
    glPopMatrix();
}

void Graphics::drawFPS(GLFWwindow* window)
{
    static float previousSeconds = glfwGetTime();
    static int frameCount = 0;
    float currentSeconds = glfwGetTime();
    float elapsedSeconds = currentSeconds - previousSeconds;
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        float fps = (float)frameCount / elapsedSeconds;
        char buffer[30];
        snprintf(buffer, 30, "FPS: %.1f", fps);
        glfwSetWindowTitle(window, buffer);
        frameCount = 0;
    }
    frameCount++;
}
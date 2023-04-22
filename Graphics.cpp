#include "Engine.h"

void Graphics::drawCircle(float x, float y, float radius, int nSeg, int r, int g, int b)
{
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

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

void Graphics::drawTriangle(float x, float y, float radius, int r, int g, int b)
{
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    const float angle = 2.0f * 3.1415926f / 3; // 3 vertices for a triangle
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float dx = radius / 2.0f;
    float dy = -sqrt(3) / 2.0f * radius;

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, radius);
    glVertex2f(dx, dy);
    glVertex2f(-dx, dy);
    glEnd();

    glPopMatrix();
}

void Graphics::drawCircleOutline(float x, float y, float radius, int nSeg, int r, int g, int b)
{
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    const float theta = 2.0f * 3.1415926f / float(nSeg);
    float cos_theta = cosf(theta);
    float sin_theta = sinf(theta);
    float dx = radius;
    float dy = 0.0f;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < nSeg; i++) {
        glVertex2f(dx, dy);
        float temp = dx;
        dx = cos_theta * dx - sin_theta * dy;
        dy = sin_theta * temp + cos_theta * dy;
    }
    glEnd();
    glPopMatrix();
}

void Graphics::drawRectangle(float x1, float y1, float x2, float y2, int r, int g, int b) {
    // Calculate the dimensions of the rectangle
    float width = abs(x2 - x1);
    float height = abs(y2 - y1);

    // Translate and rotate to the correct position and orientation
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
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

void Graphics::drawLine(GLFWwindow* window, float x1, float y1, float x2, float y2, int r, int g, int b) {
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
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

void Graphics::clear(GLFWwindow* window)
{
    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::ellipse(float cx, float cy, float cx2, float cy2, float eccentricity, int num_segments, int r, int g, int b )
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

    float theta = 2 * M_PI / float(num_segments);
    float c = cos(theta);//precalculate the sine and cosine
    float s = sin(theta);
    float t;

    float x = 1;//we start at angle = 0 
    float y = 0;

    glColor3f(r / 255.0f, g / 255.0f, bb / 255.0f);
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


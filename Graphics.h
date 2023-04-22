#pragma once

class Graphics {
public:
    static void drawCircleOutline(float x, float y, float radius, int nSeg);
    static void drawRectangle(float x1, float y1, float x2, float y2);
    static void drawCircle(float x, float y, float radius, int nSeg);
    static void drawTriangle(float x, float y, float radius);
    static void drawLine(GLFWwindow* window, float x1, float y1, float x2, float y2);
    static void drawFPS(GLFWwindow* window);
    static void clear(GLFWwindow* window);
    static void ellipse(float cx, float cy, float cx2, float cy2, float eccentricity, int num_segments);
private:
};

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
private:
};

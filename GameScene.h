#pragma once

class GameScene
{
public:
    void display(GLFWwindow& window, Camera2d& cam);
    void update(GLFWwindow& window, float deltaTime, Camera2d& cam);
    int game(int width, int height, Camera2d& cam);
private:
};


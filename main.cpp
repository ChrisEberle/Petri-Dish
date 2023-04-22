#include "Engine.h"

GameScene gScene;
Camera2d cam;
int main() {
    // GAME SCENE ~~~~~
    gScene.game(screenWidth,screenHeight, cam);
    return 0;
}
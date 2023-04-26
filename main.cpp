#include "Engine.h"

// Scene object init's
GameScene gScene;
// camera init
Camera2d cam;

int main() {
    
    // GAME SCENE ~~~~~
    gScene.game(screenWidth,screenHeight, cam);
    return 0;
}
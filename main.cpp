#include "Engine.h"
#include "main.h"

int main(int argc, char* argv[]) {
    AudioPlayer::init();
    // GAME SCENE ~~~~~
    game_scene.game(screenWidth, screenHeight, game_cam);
    // clean sdlmixer audio
    AudioPlayer::clean();
    return 0;
}
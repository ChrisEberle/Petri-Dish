#include "Engine.h"
#include "main.h"

int SDL_main(int argc, char* argv[]) {
    AudioPlayer audioPlayer;

    // Start playing the WAV file
    std::thread audioThread([&audioPlayer]() {
        audioPlayer.playWav("audio/music/song1.wav");
        });


    // GAME SCENE ~~~~~
    game_scene.game(screenWidth, screenHeight, game_cam);

    audioThread.join(); // Wait for the audio thread to finish

    return 0;
}
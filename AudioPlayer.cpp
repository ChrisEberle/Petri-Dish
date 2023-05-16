#include "Engine.h"

void AudioPlayer::init()
{
    // Initialize SDL2
    SDL_Init(SDL_INIT_AUDIO);

    // Initialize SDL2_mixer
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    std::cout << "SDL_mixer audio player has been initialized." << std::endl;
}

void AudioPlayer::clean()
{
    // clean the sdl_mixer
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    std::cout << "SDL_MIXER audio player has been cleaned" << std::endl;
}
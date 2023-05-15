#pragma once
class AudioPlayer
{
public:
    AudioPlayer() {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            // Handle initialization error
        }
    }

    ~AudioPlayer() {
        SDL_Quit();
    }

   static void init();
   static void clean();
};


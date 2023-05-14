#include "Engine.h"
#include "main.h"

const int SAMPLE_RATE = 44100;
const int AMPLITUDE = 28000;
const int FREQUENCY = 440;

void audioCallback(void* userdata, Uint8* stream, int len) {
    Uint32 length = static_cast<Uint32>(len);
    Uint8* audioData = reinterpret_cast<Uint8*>(stream);

    double time = 0;
    double increment = 2.0 * M_PI * FREQUENCY / SAMPLE_RATE;

    for (Uint32 i = 0; i < length; ++i) {
        double value = AMPLITUDE * sin(time);
        audioData[i] = static_cast<Uint8>(value);

        time += increment;
        if (time >= 2.0 * M_PI)
            time -= 2.0 * M_PI;
    }
}

int SDL_main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec audioSpec;
    audioSpec.freq = SAMPLE_RATE;
    audioSpec.format = AUDIO_U8;
    audioSpec.channels = 1;
    audioSpec.samples = 2048;
    audioSpec.callback = audioCallback;

    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0);
    SDL_PauseAudioDevice(audioDevice, 0);

    // Keep the program running for a few seconds
    SDL_Delay(5000);

    SDL_CloseAudioDevice(audioDevice);
    SDL_Quit();

    // GAME SCENE ~~~~~
    game_scene.game(screenWidth,screenHeight, game_cam);
    return 0;
}
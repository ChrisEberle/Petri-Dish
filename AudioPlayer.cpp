#include "Engine.h"

void AudioPlayer::playWav(const char* filePath)
{
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    if (SDL_LoadWAV(filePath, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        // Handle WAV loading error
        return;
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        // Handle audio device error
        SDL_FreeWAV(wavBuffer);
        return;
    }

    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    if (success != 0) {
        // Handle audio queueing error
        SDL_CloseAudioDevice(deviceId);
        SDL_FreeWAV(wavBuffer);
        return;
    }

    SDL_PauseAudioDevice(deviceId, 0);

    while (SDL_GetQueuedAudioSize(deviceId) > 0) {
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

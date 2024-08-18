#pragma once

#include <functional>

#include "portaudio.h"

#include "Audio.hpp"

class AudioStream {
public:
    AudioStream(AudioMetaData audioMetaData, bool isStreamOuptut);
    ~AudioStream();

    using callback_t = int(const void*, void*, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags);

    void setCallback(std::function<callback_t>& dataCallback);
    void setStreamFinishCallback(std::function<void()>& callback);
    void startStream();

    friend int callback(
        const void* inputBuffer, void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);
    friend void streamFinishCallback(void* userData);

private:
    PaStreamParameters outputParameters;
    PaStream* stream;
    PaError err;
    AudioMetaData metaData;
    std::function<callback_t> callback;
    std::function<void()> finishCallback;
    bool isOutput = false;

    void logError();
};

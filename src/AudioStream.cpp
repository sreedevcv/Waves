#include "AudioStream.hpp"
#include "portaudio.h"

#include <iostream>

int callback(
    const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    AudioStream* stream = (AudioStream*)userData;

    return stream->callback(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}

void streamFinishCallback(void* userData)
{
    AudioStream* stream = (AudioStream*)userData;
    stream->finishCallback();
}

AudioStream::AudioStream(AudioMetaData audioMetaData, bool isStreamOuptut)
    : metaData(audioMetaData)
    , isOutput(false)
{
    // Initialize PortAudio
    err = Pa_Initialize();
    if (err != paNoError) {
        logError();
        return;
    }

    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice) {
        std::cerr << "Error: No default output device." << std::endl;
        logError();
        return;
    }

    outputParameters.channelCount = audioMetaData.channels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    // err = Pa_SetStreamFinishedCallback(stream, &::streamFinishCallback);
    // if (err != paNoError) {
    //     logError();
    //     return;
    // }
}

AudioStream::~AudioStream()
{
    err = Pa_Terminate();
    if (err != paNoError) {
        logError();
    }
}

void AudioStream::logError()
{
    std::cerr << "An error occurred while using the portaudio stream\n";
    std::cerr << "Error number: " << err << "\n";
    std::cerr << "Error message: " << Pa_GetErrorText(err) << std::endl;
}

void AudioStream::setCallback(std::function<callback_t>& dataCallback)
{
    callback = dataCallback;
}

void AudioStream::startStream()
{
    err = Pa_OpenStream(&stream, NULL, &outputParameters, metaData.sampleRate, 64, paClipOff, ::callback, this);
    if (err != paNoError) {
        logError();
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        logError();
    }
}

void AudioStream::setStreamFinishCallback(std::function<void(void)>& callback)
{
    finishCallback = callback;
}
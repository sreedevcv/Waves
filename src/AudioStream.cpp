#include "AudioStream.hpp"
#include "portaudio.h"

#include <iostream>

AudioStream::AudioStream(AudioMetaData audioMetaData)
    : metaData{audioMetaData} 
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

}

void AudioStream::logError()
{
    Pa_Terminate();
    std::cerr << "An error occurred while using the portaudio stream\n";
    std::cerr << "Error number: " << err << "\n";
    std::cerr << "Error message: " << Pa_GetErrorText( err ) << std::endl;
}
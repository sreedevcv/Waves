#include "SourcePlayer.hpp"

#include "AudioStream.hpp"
#include "portaudio.h"
#include <cstring>
#include <functional>
#include <print>

SourcePlayer::SourcePlayer(AudioSource<float>& audioSource)
    : source(audioSource)
{
    stream = new AudioStream(source.getMetaData(), true);

    std::function<AudioStream::callback_t> callback = [&](
                                                          const void* inputBuffer,
                                                          void* outputBuffer,
                                                          unsigned long framesPerBuffer,
                                                          const PaStreamCallbackTimeInfo* timeInfo,
                                                          PaStreamCallbackFlags statusFlags) -> int {

        float* out = (float*)outputBuffer;
        for (int i = 0; i < framesPerBuffer * source.getMetaData().channels && !source.finished(); i++)  {
            *out++ = source.get();
        }

        if (!source.finished()) {
            return paContinue;
        } else {
            return paComplete;
        }
    };

    stream->setCallback(callback);

    std::function<void()> finishCallback = [&]() {
        std::println("Finished Source");
    };

    stream->setStreamFinishCallback(finishCallback);
}

SourcePlayer::~SourcePlayer()
{
    delete stream;
}

void SourcePlayer::play()
{
    stream->startStream();
}

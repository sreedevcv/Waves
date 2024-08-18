#pragma once

#include "AudioSource.hpp"
#include "AudioStream.hpp"
class SourcePlayer {
public:
    SourcePlayer(AudioSource<float>& audioSource);
    ~SourcePlayer();

    void play();
private:

    AudioSource<float>& source;
    AudioStream* stream;
};
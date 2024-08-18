#pragma once

#include "Audio.hpp"
template <typename T>
class AudioSource {
public:
    virtual void reset() = 0;
    virtual T get() = 0;
    virtual bool finished() = 0;
    virtual AudioMetaData getMetaData() = 0;

    virtual ~AudioSource() = default;
};
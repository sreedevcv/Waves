#pragma once

#include "Audio.hpp"
#include "AudioSource.hpp"
#include "WavFile.hpp"
#include <cstdint>

class WavSource : public AudioSource<float> {
public:
    WavSource(const char* filePath);

    virtual void reset() override;
    virtual float get() override;
    virtual bool finished() override;
    virtual AudioMetaData getMetaData() override;

private:
    WavFile file;
    Music music;

    uint32_t ptr = 0;
};
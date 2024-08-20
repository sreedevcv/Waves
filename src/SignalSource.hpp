#pragma once

#include "Audio.hpp"
#include "AudioSource.hpp"
#include <cstdint>
#include <vector>

class SignalSource : public AudioSource<float> {
public:
    SignalSource(uint32_t frequency, uint32_t sampleRate, uint32_t duration);

    virtual void reset() override;
    virtual float get() override;
    virtual bool finished() override;
    virtual AudioMetaData getMetaData() override;
private:
    uint32_t ptr = 0;
    std::vector<float> data;
    AudioMetaData metaData;
};

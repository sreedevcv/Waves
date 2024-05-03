#pragma once

#include <cstdint>
#include <vector>

#include "Audio.hpp"

class WaveGenerator {
private:
    AudioMetaData audioMeta;

public:
    WaveGenerator(AudioMetaData audioMetaData);

    std::vector<uint8_t> createSineWave(uint32_t frequency, int milliseconds);
};

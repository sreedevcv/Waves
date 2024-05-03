#include "WaveGenerator.hpp"
#include "Audio.hpp"

#include <cmath>
#include <cstdint>
#include <iostream>

WaveGenerator::WaveGenerator(AudioMetaData audioMetaData)
    : audioMeta { audioMetaData }
{
}

std::vector<uint8_t> WaveGenerator::createSineWave(uint32_t frequency, int milliseconds)
{
    uint32_t samples = audioMeta.sampleRate * milliseconds / 1000;
    double timeInterval = milliseconds * 1000.0 / (float) audioMeta.sampleRate;
    std::vector<uint8_t> data;

    for (uint32_t i = 0; i < samples; i++) {
        double angle = std::sin(2.0 * 3.14 * i * frequency * timeInterval);
        uint8_t value = static_cast<uint8_t>((angle * 128.0) + 128);

        for (uint32_t j = 0; j < audioMeta.channels; j++) {
            data.push_back(value);
        }
    }

    return data;
}

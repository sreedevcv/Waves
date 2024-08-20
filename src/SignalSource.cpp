#include "SignalSource.hpp"
#include "Audio.hpp"
#include <cmath>

SignalSource::SignalSource(uint32_t frequency, uint32_t sampleRate, uint32_t duration)
    : data(sampleRate * (duration / 1000))
{
    metaData = AudioMetaData {
        .sampleRate = sampleRate,
        .milliseconds = duration,
        .channels = 1,
        .sampleSizeInBits = 16,
    };

    for (int i = 0; i < data.size(); i++) {
        float time = i / static_cast<float>(data.size()) * (duration / 1000.0f);
        float angle = time * 2.0f * M_PI * frequency;
        data[i] = std::sin(angle);
    }
}

void SignalSource::reset()
{
    ptr = 0;
}

float SignalSource::get()
{
    return data[ptr++];
}

bool SignalSource::finished()
{
    return ptr == data.size();
}

AudioMetaData SignalSource::getMetaData()
{
    return metaData;
}

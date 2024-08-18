#pragma once

#include <cstdint>
#include <vector>

struct AudioMetaData {
    uint32_t sampleRate = 16000;
    uint32_t milliseconds = 2000;
    uint32_t channels = 1;
    uint32_t sampleSizeInBits = 8;
};


struct Music {
    AudioMetaData metaData;
    std::vector<float> data;
};
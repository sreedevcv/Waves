#pragma once

#include <cstdint>

struct AudioMetaData {
    uint32_t sampleRate = 16000;
    uint32_t milliseconds = 2000;
    uint32_t channels = 1;
    uint32_t sampleSizeInBits = 8;
};

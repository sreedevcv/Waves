#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Audio.hpp"

class WavFile {
public:
    WavFile(std::string filePath);
    ~WavFile() = default;

    void readFile();
    void writeFile(std::vector<uint8_t>& data, const AudioMetaData& metaData);

private:
    struct Header {
        uint32_t riffHeader = *((uint32_t*)"RIFF");
        uint32_t fileSize;
        uint32_t waveHeader = *((uint32_t*)"WAVE");

        uint32_t formatChunkMarker = *((uint32_t*)"fmt ");
        uint32_t headerLength = 16;
        uint16_t pcmFormat = 1; /* 1 = UnCompressed */
        uint16_t channelCount;
        uint32_t samplesPerSecond;
        uint32_t bytesPerSecond;
        uint16_t blockAlign;
        uint16_t bitsPerSample;

        uint32_t dataHeader = *((uint32_t*)"data");
        uint32_t dataSize;

        inline Header(uint32_t audioDataSize,
            uint16_t channels,
            uint32_t sampleRate,
            uint32_t sampleSizeInBits)
            : fileSize { 44 + audioDataSize }
            , channelCount { channels }
            , samplesPerSecond { sampleRate }
            , dataSize { audioDataSize }

        {
            bitsPerSample = sampleSizeInBits;
            bytesPerSecond = samplesPerSecond * bitsPerSample * channels / 8;
            blockAlign = bitsPerSample * channels / 8;
        }
    } __attribute__((packed));

    std::string file = "";
};

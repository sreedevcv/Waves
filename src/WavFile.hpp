#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Audio.hpp"

class WavFile {
public:
    WavFile(const std::string& filePath);
    ~WavFile() = default;

    Music readFile();
    void writeFile(std::vector<uint8_t>& data, const AudioMetaData& metaData);

private:
    struct Header {
        uint8_t riffHeader[4] = {'R', 'I', 'F', 'F'};
        uint32_t fileSize;
        uint8_t waveHeader[4] = {'W', 'A', 'V', 'E'};

        uint8_t formatChunkMarker[4] = {'f', 'm', 't', ' '};
        uint32_t headerLength = 16;
        uint16_t pcmFormat = 1; /* 1 = UnCompressed */
        uint16_t channelCount;
        uint32_t samplesPerSecond;
        uint32_t bytesPerSecond;
        uint16_t blockAlign;
        uint16_t bitsPerSample;

        uint8_t dataHeader[4] = {'d', 'a', 't', 'a'};
        uint32_t dataSize;

        inline Header() { }
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

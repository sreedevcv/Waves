#include "WavFile.hpp"
#include "Audio.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <print>
#include <vector>

WavFile::WavFile(const std::string& filePath)
    : file { filePath }
{
}

void WavFile::writeFile(std::vector<uint8_t>& data, const AudioMetaData& metaData)
{
    std::ofstream wavFile(file);
    Header head(data.size(), metaData.channels, metaData.sampleRate, metaData.sampleSizeInBits);

    wavFile.write((const char*)(&head), sizeof(head));
    wavFile.write((const char*)(&data[0]), data.size());
}

Music WavFile::readFile()
{
    Header header;

    FILE* wavFile = fopen(file.c_str(), "rb");
    if (wavFile == nullptr) {
        std::println("Failed to open {}.", file);
        std::exit(1);
    }
    uint32_t readBytes = std::fread(&header, 1, sizeof(header), wavFile);
    assert(readBytes == sizeof(header));

    std::println("File name: {}", file);
    std::println("Header Size: {}", sizeof(header));
    std::println("fileSize: {}", header.fileSize);
    std::println("headerLength: {}", header.headerLength);
    std::println("pcmFormat: {}", header.pcmFormat);
    std::println("channelCount: {}", header.channelCount);
    std::println("samplesPerSecond: {}", header.samplesPerSecond);
    std::println("bytesPerSecond: {}", header.bytesPerSecond);
    std::println("blockAlign: {}", header.blockAlign);
    std::println("bitsPerSample: {}", header.bitsPerSample);
    std::println("dataSize: {}", header.dataSize);
    std::println("Duration: {}", header.dataSize / (float)header.bytesPerSecond);

    // Read all the bytes
    std::vector<uint8_t> bytes(header.dataSize);

    readBytes = std::fread(bytes.data(), 1, header.dataSize, wavFile);
    assert(readBytes == header.dataSize);

    const uint32_t sampleSize = header.bitsPerSample / 8;
    const uint32_t numOfSamples = header.dataSize / (sampleSize);
    const uint64_t maxSampleSize = std::pow(2.0, header.bitsPerSample);
    std::vector<float> data(numOfSamples);

    for (int i = 0; i < bytes.size(); i += sampleSize) {
        uint64_t sample = 0;

        for (int j = sampleSize - 1; j >= 0; j--) {
            sample = sample << 8;
            sample |= bytes[i + j];

            // sample = sample | (bytes[i + j] << (8 * (sampleSize - j - 1)));
        }

        float normalizedSample = ((sample / (float)maxSampleSize) - 0.5) * 2.0;
        data[i / sampleSize] = normalizedSample;

        // std::println("{} {}", sample, normalizedSample);
        // if (i >= 100) break;
    }

    std::fclose(wavFile);

    return Music {
        .metaData = AudioMetaData {
            .sampleRate = header.samplesPerSecond,
            .milliseconds = static_cast<uint32_t>((header.dataSize / (float)header.bytesPerSecond) * 1000),
            .channels = header.channelCount,
            .sampleSizeInBits = header.bitsPerSample,
        },
        .data = std::move(data)
    };
}

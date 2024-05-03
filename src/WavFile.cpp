#include "WavFile.hpp"

#include <fstream>
#include <iostream>

WavFile::WavFile(std::string filePath)
    : file { filePath }
{
}

void WavFile::writeFile(std::vector<uint8_t>& data, const AudioMetaData& metaData)
{
    if (file == "") {
        std::cout << "Invalid File Name" << std::endl;
        return;
    }

    std::ofstream wavFile(file);
    Header head(data.size(), metaData.channels, metaData.sampleRate, metaData.sampleSizeInBits);

    wavFile.write((const char*)(&head), sizeof(head));
    wavFile.write((const char*)(&data[0]), data.size());
}

void WavFile::readFile()
{
}

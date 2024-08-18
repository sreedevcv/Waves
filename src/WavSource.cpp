#include "WavSource.hpp"
#include "WavFile.hpp"

WavSource::WavSource(const char* filePath)
    : file(filePath)
{
    music = file.readFile();
}

void WavSource::reset()
{
    ptr = 0;
}

float WavSource::get()
{
    return music.data[ptr++];
}

bool WavSource::finished()
{
    return ptr == music.data.size();
}

AudioMetaData WavSource::getMetaData()
{
    return music.metaData;
}
#include <cmath>
#include <functional>
#include <iostream>

#include "Audio.hpp"
#include "AudioStream.hpp"
#include "SignalSource.hpp"
#include "SourcePlayer.hpp"
#include "WavFile.hpp"
#include "WavSource.hpp"
#include "WaveGenerator.hpp"

#include "portaudio.h"
#include "ui/MainWindow.hpp"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow a;
    a.show();

    return app.exec();


    // WavSource source("/home/sreedev/Projects/Waves/assets/party-monster-100.wav");
    // SignalSource source(500, 32000, 10000);
    // SourcePlayer player(source);
    // player.play();
    // Pa_Sleep(10 * 1000);
    // return 0;
}

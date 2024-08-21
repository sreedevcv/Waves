#include "MainWindow.hpp"
#include "AudioChart.hpp"
#include "WavSource.hpp"

#include <qmainwindow.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , chart(new AudioChart())
{
    this->setCentralWidget(chart);

    WavSource source("/home/sreedev/Projects/Waves/assets/party-monster-100.wav");
    chart->populateData(source);
}

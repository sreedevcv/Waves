#pragma once

#include <QWidget>
#include <QtCharts/QLineSeries>
#include "AudioSource.hpp"

class AudioChart: public QWidget {
    // Q_OBJECT
public:
    explicit AudioChart(QWidget* parent = nullptr);
    ~AudioChart() = default;

    void populateData(AudioSource<float>& source);
private:
    QLineSeries* lineSeries;
};

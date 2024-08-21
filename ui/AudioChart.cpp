#include "AudioChart.hpp"

#include <QtCharts/QtCharts>

AudioChart::AudioChart(QWidget* parent)
    : QWidget { parent }
    , lineSeries{new QLineSeries}
{
    const int sampleCount = 32000;
    const int frequency = 100;
    const int duration = 2;

    QChart* chart = new QChart();
    QChartView* chartView = new QChartView(chart);
    chartView->setMinimumSize(500, 400);
    chart->addSeries(lineSeries);

    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, sampleCount);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("samples");
    chart->addAxis(axisX, Qt::AlignBottom);
    lineSeries->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(-1, 1);
    axisY->setTitleText("Audio Level");
    chart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisY);

    // for (int i = 0; i < sampleCount; i++) {
    //     float time = (i / (float)sampleCount) * duration;
    //     float angle = 2.0 * M_PI * frequency * time;
    //     lineSeries->append(i, std::sin(angle));
    // }

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);
}

void AudioChart::populateData(AudioSource<float>& source)
{
    int i = 0;
    while (!source.finished()) {
        lineSeries->append(i++, source.get());
    }
}

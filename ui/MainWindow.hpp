#pragma once

#include "AudioChart.hpp"
#include <QMainWindow>

class MainWindow : public QMainWindow {
    // Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

private:
    AudioChart* chart;
};

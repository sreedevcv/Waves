#pragma once

#include "qmainwindow.h"
#include <qtmetamacros.h>
#include <qwidget.h>

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    // Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

private:
    // Ui::MainWindow* ui;
};
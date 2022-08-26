#pragma once

#include <QtWidgets/QMainWindow>

class QCustomPlot;

class HMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HMainWindow(QWidget *parent = nullptr);
    ~HMainWindow();

private:
    QCustomPlot *customPlot = nullptr;
};

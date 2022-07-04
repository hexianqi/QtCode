#pragma once

#include <QtWidgets/QMainWindow>

class HMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HMainWindow(QWidget *parent = nullptr);
    ~HMainWindow() override;
};


#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui {
class HMainWindowDemo;
}

class HMainWindowDemo : public QMainWindow
{
    Q_OBJECT

public:
    HMainWindowDemo(QWidget *parent = nullptr);
    ~HMainWindowDemo();

private:
    Ui::HMainWindowDemo *ui;
};

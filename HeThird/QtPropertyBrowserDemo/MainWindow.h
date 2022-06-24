#pragma once

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class HMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HMainWindow(QWidget *parent = nullptr);
    ~HMainWindow();

private:
    Ui::MainWindow *ui;
};

#pragma once

#include "HeCore/HActionType.h"
#include <QtWidgets/QMainWindow>

HE_USE_NAMESPACE

namespace Ui {
class HMainWindowDemo;
}

class HMainWindowDemoPrivate;

class HMainWindowDemo : public QMainWindow
{
    Q_OBJECT

public:
    HMainWindowDemo(QWidget *parent = nullptr);
    ~HMainWindowDemo();

protected slots:
    void showDeviceFailed(const QString &port, const QString &text);
    void showActionFailed(HActionType action, const QString &text);
    void handleAction(HActionType action);
    void on_pushButton_01_clicked();
    void on_pushButton_02_clicked();
    void on_pushButton_03_clicked();
    void on_pushButton_04_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();

protected:
    void init();
    void refreshStdCurve();

private:
    Ui::HMainWindowDemo *ui;
    QScopedPointer<HMainWindowDemoPrivate> d_ptr;
};

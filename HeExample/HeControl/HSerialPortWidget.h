/***************************************************************************************************
**      2019-06-03  HSerialPortWidget 串口调试工具。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HSerialPortWidget;
}

HE_BEGIN_NAMESPACE

class HSerialPortWidgetPrivate;

class HSerialPortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSerialPortWidget(QWidget *parent = nullptr);
    ~HSerialPortWidget();

protected slots:
   void on_pushButton_101_clicked();
   void on_pushButton_501_clicked();
   void on_pushButton_601_clicked();
   void on_pushButton_602_clicked();
   void on_pushButton_603_clicked();
   void on_pushButton_604_clicked();
   void on_pushButton_605_clicked();

protected:
    void showTime();
    void updateUi(bool b);
    bool openPort();
    bool closePort();
    void writeData();
    void readData();
    void saveData();
    void autoSendData();
    void autoSaveData();

private:
    void init();

private:
    Ui::HSerialPortWidget *ui;
    QScopedPointer<HSerialPortWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

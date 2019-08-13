/***************************************************************************************************
**      2019-07-17  HUdpServerWidget UDP服务端
***************************************************************************************************/

#ifndef HUDPSERVERWIDGET_H
#define HUDPSERVERWIDGET_H

#include "HAbstractNetworkWidget.h"

namespace Ui {
class HUdpServerWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HUdpServerWidgetPrivate;

class HUdpServerWidget : public HAbstractNetworkWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HUdpServerWidget)

public:
    explicit HUdpServerWidget(QWidget *parent = nullptr);
    ~HUdpServerWidget() override;

public slots:
    void setServerIp(QString value);
    void setServerPort(int value);
    void setListenPort(int value);
    void clearData();
    void sendData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void handleReadyRead();
    void append(int type, QString data);

protected:
    void readSettings() override;
    void writeSettings() override;

private:
    void init();

private:
    Ui::HUdpServerWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HUDPSERVERWIDGET_H

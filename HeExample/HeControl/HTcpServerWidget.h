/***************************************************************************************************
**      2019-07-17  HTcpServerWidget TCP服务端
***************************************************************************************************/

#ifndef HTCPSERVERWIDGET_H
#define HTCPSERVERWIDGET_H

#include "HAbstractNetworkWidget.h"

namespace Ui {
class HTcpServerWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HTcpServerWidgetPrivate;

class HTcpServerWidget : public HAbstractNetworkWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTcpServerWidget)

public:
    explicit HTcpServerWidget(QWidget *parent = nullptr);
    ~HTcpServerWidget() override;

public slots:
    void setListenPort(int value);
    void clearData();
    void sendData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void handleReceiveData(QString ip, int port, QByteArray data);
    void handleClientConnected(QString ip, int port);
    void handleClientDisconnected(QString ip, int port);
    void append(int type, QString data);

protected:
    void readSettings() override;
    void writeSettings() override;

private:
    void init();

private:
    Ui::HTcpServerWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPSERVERWIDGET_H

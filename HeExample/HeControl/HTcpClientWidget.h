/***************************************************************************************************
**      2019-07-17  HTcpClientWidget TCP客户端
***************************************************************************************************/

#ifndef HTCPCLIENTWIDGET_H
#define HTCPCLIENTWIDGET_H

#include "HAbstractNetworkWidget.h"

namespace Ui {
class HTcpClientWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HTcpClientWidgetPrivate;

class HTcpClientWidget : public HAbstractNetworkWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTcpClientWidget)

public:
    explicit HTcpClientWidget(QWidget *parent = nullptr);
    ~HTcpClientWidget() override;

public slots:
    void setServerIp(QString value);
    void setServerPort(int value);
    void clearData();
    void sendData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void handleConnected();
    void handleDisconnected();
    void handleReadyRead();
    void append(int type, QString data);

protected:
    void readSettings() override;
    void writeSettings() override;

private:
    void init();

private:
    Ui::HTcpClientWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPCLIENTWIDGET_H

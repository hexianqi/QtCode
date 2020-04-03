/***************************************************************************************************
**      2019-07-17  HUdpServerWidget UDP服务端
***************************************************************************************************/

#ifndef HUDPSERVERWIDGET_H
#define HUDPSERVERWIDGET_H

#include "HAbstractServerWidget.h"

namespace Ui {
class HUdpServerWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HUdpServerWidgetPrivate;

class HUdpServerWidget : public HAbstractServerWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HUdpServerWidget)

public:
    explicit HUdpServerWidget(QWidget *parent = nullptr);
    ~HUdpServerWidget() override;

public slots:
    void sendData() override;
    void clearData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void handleClientConnected(const QString &ip, int port) override;
    void handleClientDisconnected(const QString &ip, int port) override;
    void append(int type, QString data) override;

protected:
    QString groupName() override;

private:
    void init();

private:
    Ui::HUdpServerWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HUDPSERVERWIDGET_H

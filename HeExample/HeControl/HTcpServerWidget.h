/***************************************************************************************************
**      2019-07-17  HTcpServerWidget TCP服务端
***************************************************************************************************/

#ifndef HTCPSERVERWIDGET_H
#define HTCPSERVERWIDGET_H

#include "HAbstractServerWidget.h"

namespace Ui {
class HTcpServerWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HTcpServerWidgetPrivate;

class HTcpServerWidget : public HAbstractServerWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTcpServerWidget)

public:
    explicit HTcpServerWidget(QWidget *parent = nullptr);
    ~HTcpServerWidget() override;

public slots:
    void sendData() override;
    void clearData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void on_pushButton_104_clicked();
    void handleClientConnected(const QString &ip, quint16 port) override;
    void handleClientDisconnected(const QString &ip, quint16 port) override;
    void append(int type, QString data) override;

protected:
    QString groupName() override;

private:
    void init();

private:
    Ui::HTcpServerWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPSERVERWIDGET_H

/***************************************************************************************************
**      2019-07-17  HTcpServerWidget TCP服务端
***************************************************************************************************/

#pragma once

#include "HAbstractServerWidget.h"

namespace Ui {
class HTcpServerWidget;
}

HE_BEGIN_NAMESPACE

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
    void handleConnected(const QString &address, int port) override;
    void handleDisconnected(const QString &address, int port) override;
    void append(int type, QString data) override;

protected:
    QString groupName() override;

private:
    void init();

private:
    Ui::HTcpServerWidget *ui;
};

HE_END_NAMESPACE

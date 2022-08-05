/***************************************************************************************************
**      2022-08-02  HWebServerWidget
***************************************************************************************************/

#pragma once

#include "HAbstractServerWidget.h"

namespace Ui {
class HWebServerWidget;
}

HE_BEGIN_NAMESPACE

class HWebServerWidgetPrivate;

class HWebServerWidget : public HAbstractServerWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HWebServerWidget)

public:
    explicit HWebServerWidget(QWidget *parent = nullptr);
    ~HWebServerWidget() override;

public slots:
    void sendData() override;
    void clearData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void on_pushButton_104_clicked();
    void handleConnected(const QString &address, int port) override;
    void handleDisconnected(const QString &address, int port) override;
    void handleSentDataText(const QString &address, int port, const QString &data);
    void handleReceiveDataText(const QString &address, int port, const QString &data);
    void append(int type, QString data) override;

protected:
    QString groupName() override;

private:
    void init();

private:
    Ui::HWebServerWidget *ui;
};

HE_END_NAMESPACE


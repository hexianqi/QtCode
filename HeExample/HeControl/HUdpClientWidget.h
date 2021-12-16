/***************************************************************************************************
**      2019-12-10  HUdpClientWidget UDP客户端
***************************************************************************************************/

#pragma once

#include "HAbstractClientWidget.h"

namespace Ui {
class HUdpClientWidget;
}

HE_BEGIN_NAMESPACE

class HUdpClientWidgetPrivate;

class HUdpClientWidget : public HAbstractClientWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HUdpClientWidget)

public:
    explicit HUdpClientWidget(QWidget *parent = nullptr);
    ~HUdpClientWidget() override;

public slots:
    void sendData() override;
    void clearData() override;

protected slots:
    void on_pushButton_101_clicked();
    void handleReadyRead();
    void append(int type, QString data);

protected:
    QString groupName() override;

private:
    void init();

private:
    Ui::HUdpClientWidget *ui;
};

HE_END_NAMESPACE

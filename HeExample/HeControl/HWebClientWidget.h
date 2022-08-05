/***************************************************************************************************
**      2022-08-02  HWebClientWidget
***************************************************************************************************/

#pragma once

#include "HAbstractClientWidget.h"

namespace Ui {
class HWebClientWidget;
}

HE_BEGIN_NAMESPACE

class HWebClientWidgetPrivate;

class HWebClientWidget : public HAbstractClientWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HWebClientWidget)

public:
    explicit HWebClientWidget(QWidget *parent = nullptr);
    ~HWebClientWidget() override;

public slots:
    void sendData() override;
    void clearData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void handleConnected();
    void handleDisconnected();
    void handleError();
    void handleTextMessageReceived(QString);
    void handleBinaryMessageReceived(QByteArray);
    void append(int type, QString data);

protected:
    QString groupName() override;

private:
    void init();

private:
    Ui::HWebClientWidget *ui;
};

HE_END_NAMESPACE


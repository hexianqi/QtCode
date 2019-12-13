/***************************************************************************************************
**      2019-07-17  HTcpClientWidget TCP客户端
***************************************************************************************************/

#ifndef HTCPCLIENTWIDGET_H
#define HTCPCLIENTWIDGET_H

#include "HAbstractClientWidget.h"

namespace Ui {
class HTcpClientWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HTcpClientWidgetPrivate;

class HTcpClientWidget : public HAbstractClientWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTcpClientWidget)

public:
    explicit HTcpClientWidget(QWidget *parent = nullptr);
    ~HTcpClientWidget() override;

public slots:    
    void sendData() override;
    void clearData() override;

protected slots:
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void handleConnected();
    void handleDisconnected();
    void handleReadyRead();
    void append(int type, QString data);

protected:
    QString groupName() override;

private:
    void init();

private:
    Ui::HTcpClientWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPCLIENTWIDGET_H

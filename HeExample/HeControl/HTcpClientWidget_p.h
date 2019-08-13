#ifndef HTCPCLIENTWIDGET_P_H
#define HTCPCLIENTWIDGET_P_H

#include "HTcpClientWidget.h"
#include "HAbstractNetworkWidget_p.h"

class QTcpSocket;

HE_CONTROL_BEGIN_NAMESPACE

class HTcpClientWidgetPrivate : public HAbstractNetworkWidgetPrivate
{
public:
    HTcpClientWidgetPrivate();

public:
    QString serverIp;
    int serverPort = 6000;
    bool connect = false;
    int currentCount = 0;
    int maxCount = 100;
    QTcpSocket *tcpSocket;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPCLIENTWIDGET_P_H

#ifndef HTCPCLIENTWIDGET_P_H
#define HTCPCLIENTWIDGET_P_H

#include "HTcpClientWidget.h"
#include "HAbstractClientWidget_p.h"

class QTcpSocket;

HE_CONTROL_BEGIN_NAMESPACE

class HTcpClientWidgetPrivate : public HAbstractClientWidgetPrivate
{
public:
    bool connected = false;
    QTcpSocket *socket = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HTCPCLIENTWIDGET_P_H

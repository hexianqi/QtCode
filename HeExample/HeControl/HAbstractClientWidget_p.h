#ifndef HABSTRACTCLIENTWIDGET_P_H
#define HABSTRACTCLIENTWIDGET_P_H

#include "HAbstractClientWidget.h"
#include "HAbstractNetworkWidget_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractClientWidgetPrivate : public HAbstractNetworkWidgetPrivate
{
public:
    QString serverAddress = "127.0.0.1";
    int serverPort = 6000;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTCLIENTWIDGET_P_H

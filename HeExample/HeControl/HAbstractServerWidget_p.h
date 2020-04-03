#ifndef HABSTRACTSERVERWIDGET_P_H
#define HABSTRACTSERVERWIDGET_P_H

#include "HAbstractServerWidget.h"
#include "HAbstractNetworkWidget_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractServerWidgetPrivate : public HAbstractNetworkWidgetPrivate
{
public:
    QString listenIP = "127.0.0.1";
    int listenPort = 6000;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTSERVERWIDGET_P_H

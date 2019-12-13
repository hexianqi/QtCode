#ifndef HUDPSERVERWIDGET_P_H
#define HUDPSERVERWIDGET_P_H

#include "HUdpServerWidget.h"
#include "HAbstractServerWidget_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HUdpServer;

class HUdpServerWidgetPrivate : public HAbstractServerWidgetPrivate
{
public:
    HUdpServer *server = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HUDPSERVERWIDGET_P_H

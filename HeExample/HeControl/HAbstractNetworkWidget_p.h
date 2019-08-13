#ifndef HABSTRACTNETWORKWIDGET_P_H
#define HABSTRACTNETWORKWIDGET_P_H

#include "HAbstractNetworkWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractNetworkWidgetPrivate
{
public:
    bool hexSend = false;
    bool hexReceive = false;
    bool ascii = false;
    bool autoSend = false;
    int interval = 1000;

public:
    QString groupName;
    QTimer *timer;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTNETWORKWIDGET_P_H

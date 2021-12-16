#pragma once

#include "HAbstractClientWidget.h"
#include "HAbstractNetworkWidget_p.h"

HE_BEGIN_NAMESPACE

class HAbstractClientWidgetPrivate : public HAbstractNetworkWidgetPrivate
{
public:
    QString serverAddress = "127.0.0.1";
    int serverPort = 6000;
};

HE_END_NAMESPACE

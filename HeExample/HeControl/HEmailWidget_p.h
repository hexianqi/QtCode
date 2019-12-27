#ifndef HEMAILWIDGET_P_H
#define HEMAILWIDGET_P_H

#include "HEmailWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HSendEmailThread;

class HEmailWidgetPrivate
{
public:
    HSendEmailThread *thread = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HEMAILWIDGET_P_H

#ifndef HCONTROLWIDGET_P_H
#define HCONTROLWIDGET_P_H

#include "HControlFactoryWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class IControlFactory;

class HControlFactoryWidgetPrivate
{
public:
    IControlFactory *factory = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLWIDGET_P_H

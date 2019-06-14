#ifndef HCONTROLWIDGET_P_H
#define HCONTROLWIDGET_P_H

#include "HControlWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class IControlFactory;

class HControlWidgetPrivate
{
public:
    IControlFactory *factory = nullptr;
};

HE_CONTROL_END_NAMESPACE



#endif // HCONTROLWIDGET_P_H

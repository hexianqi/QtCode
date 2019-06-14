#ifndef HSTYLEWIDGET_P_H
#define HSTYLEWIDGET_P_H

#include "HStyleWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class IStyleFactory;

class HStyleWidgetPrivate
{
public:
    IStyleFactory *factory = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HSTYLEWIDGET_P_H

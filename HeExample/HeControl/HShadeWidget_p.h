#ifndef HSHADEWIDGET_P_H
#define HSHADEWIDGET_P_H

#include "HShadeWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HShadeWidgetPrivate
{
public:
    QColor background;
    double opacity;
    QWidget *mainWidget = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HSHADEWIDGET_P_H

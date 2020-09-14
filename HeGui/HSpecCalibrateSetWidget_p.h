#ifndef HSPECCALIBRATESETWIDGET_P_H
#define HSPECCALIBRATESETWIDGET_P_H

#include "HSpecCalibrateSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecCalibrateSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool autoIntegralTime = false;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATESETWIDGET_P_H

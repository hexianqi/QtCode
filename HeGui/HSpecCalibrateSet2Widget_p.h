#ifndef HSPECCALIBRATESET2WIDGET_P_H
#define HSPECCALIBRATESET2WIDGET_P_H

#include "HSpecCalibrateSet2Widget.h"
#include "HAbstractTestSetWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecCalibrateSet2WidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool integralTimeAuto = false;
};

HE_GUI_END_NAMESPACE


#endif // HSPECCALIBRATESET2WIDGET_P_H

#ifndef HIVTESTSETWIDGET_P_H
#define HIVTESTSETWIDGET_P_H

#include "HIVTestSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HIVTestSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    double current = 1.0;
    double from = 1.0;
    double to = 100.0;
    double interval = 1.0;
};

HE_GUI_END_NAMESPACE

#endif // HIVTESTSETWIDGET_P_H

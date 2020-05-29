#ifndef HSIMPLETESTSETWIDGET_P_H
#define HSIMPLETESTSETWIDGET_P_H

#include "HSimpleTestSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HSimpleTestSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool integralTimeAuto = false;
};

HE_GUI_END_NAMESPACE

#endif // HSIMPLETESTSETWIDGET_P_H

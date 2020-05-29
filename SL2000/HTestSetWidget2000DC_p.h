#ifndef HTESTSETWIDGET2000DC_P_H
#define HTESTSETWIDGET2000DC_P_H

#include "HTestSetWidget2000DC.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

class HTestSetWidget2000DCPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    bool integralTimeAuto = false;
    QTimer *timerContinue = nullptr;
    QTimer *timerInterval = nullptr;
};

#endif // HTESTSETWIDGET2000DC_P_H

#ifndef HVERNIERWIDGET_P_H
#define HVERNIERWIDGET_P_H

#include "HVernierWidget.h"
#include "HCartesianWidget_p.h"

class QGridLayout;

class HVernierWidgetPrivate : public HCartesianWidgetPrivate
{
    Q_DECLARE_PUBLIC(HVernierWidget)

public:
    HVernierWidgetPrivate(HVernierWidget *q);

public:
    HVernierTracking *tracking;
    QLabel *labelLeft;
    QLabel *labelCenter;
    QLabel *labelRight;
    QGridLayout *layoutLabel;
    int decimals = 2;
};

#endif // HVERNIERWIDGET_P_H

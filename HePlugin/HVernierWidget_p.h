#ifndef HVERNIERWIDGET_P_H
#define HVERNIERWIDGET_P_H

#include "HVernierWidget.h"
#include "HCartesianWidget_p.h"

class QGridLayout;

class QDESIGNER_WIDGET_EXPORT HVernierWidgetPrivate : public HCartesianWidgetPrivate
{
public:
    HVernierWidgetPrivate();

public:
    HVernierTracking *tracking = nullptr;
    QLabel *labelLeft = nullptr;
    QLabel *labelCenter = nullptr;
    QLabel *labelRight = nullptr;
    QGridLayout *layoutLabel = nullptr;
    int decimals = 2;
};

#endif // HVERNIERWIDGET_P_H

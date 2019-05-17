#ifndef HCHROMATISMWIDGET_P_H
#define HCHROMATISMWIDGET_P_H

#include "HChromatismWidget.h"
#include "HCartesianWidget_p.h"


class HChromatismWidgetPrivate : public HCartesianWidgetPrivate
{
    Q_DECLARE_PUBLIC(HChromatismWidget)

public:
    HChromatismWidgetPrivate(HChromatismWidget *);

public:
    QPolygonF toEllipse();

public:
    QColor colorPointFocus = Qt::red;
    QColor colorTitle = Qt::black;
    QColor colorBody = Qt::red;
    QFont fontTitle;
    QFont fontBody;

public:
    QString title;
    QPointF pointFocus;
    QPointF pointCenter;
    double stdSdcm = 0.0;
    double stdTheta = 0.0;
    double stdA = 0.0;
    double stdB = 0.0;
    double sdcm = 0.0;
};

#endif // HCHROMATISMWIDGET_P_H

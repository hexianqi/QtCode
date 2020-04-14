/***************************************************************************************************
**      2018-06-19  HRubberBand 橡皮带策略。
***************************************************************************************************/

#ifndef HRUBBERBAND_H
#define HRUBBERBAND_H

#include "HAbstractMouseStrategy.h"
#include <QtCore/QRectF>

class HAbstractDomain;
class HRubberBandPrivate;

class HRubberBand : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HRubberBand)

public:
    explicit HRubberBand(QWidget *parent = nullptr);

signals:
    void rubberBandChanged(QRectF value);

public:
    bool setEnable(bool b) override;

public:
    bool mousePressEvent(QMouseEvent *) override;
    bool mouseMoveEvent(QMouseEvent *) override;
    bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HRubberBand(HRubberBandPrivate &p, QWidget *parent = nullptr);
};

#endif // HRUBBERBAND_H

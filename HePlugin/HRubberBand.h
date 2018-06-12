#ifndef HRUBBERBAND_H
#define HRUBBERBAND_H

#include "HAbstractMouseStrategy.h"
#include <QRectF>

class HAbstractDomain;
class HRubberBandPrivate;

class HRubberBand : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HRubberBand)

public:
    explicit HRubberBand(QWidget *parent = nullptr);
    ~HRubberBand();

signals:
    void rubberBandChanged(QRectF value);

public:
    virtual void setEnable(bool b) override;

public:
    virtual void paintEvent(QStylePainter *) override;
    virtual bool mousePressEvent(QMouseEvent *) override;
    virtual bool mouseMoveEvent(QMouseEvent *) override;
    virtual bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HRubberBand(HRubberBandPrivate &p, QWidget *parent = nullptr);
};

#endif // HRUBBERBAND_H

#ifndef HCARTESIANZOOM_H
#define HCARTESIANZOOM_H

#include "HAbstractMouseStrategy.h"

class HCartesianZoomPrivate;
class HCartesianCoordinate;

class HCartesianZoom : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCartesianZoom)

public:
    explicit HCartesianZoom(QWidget *parent = nullptr);
    ~HCartesianZoom();

signals:
    void coordinateChanged(HCartesianCoordinate *);

public:
    void setCoordinate(HCartesianCoordinate *);
    void resetCoordinate();

public:
    virtual void setValidRegion(QRectF value) override;

public:
    virtual void paintEvent(QStylePainter *) override;
    virtual bool mousePressEvent(QMouseEvent *) override;
    virtual bool mouseMoveEvent(QMouseEvent *) override;
    virtual bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HCartesianZoom(HCartesianZoomPrivate &p, QWidget *parent = nullptr);

protected:
    void handleRubberBandChanged(QRectF value);
    void zoom();
    void zoomIn();
    void zoomOut();

private:
    void init();
};

#endif // HCARTESIANZOOM_H

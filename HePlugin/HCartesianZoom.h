/***************************************************************************************************
**      2018-06-19  HCartesianZoom 缩放策略。
***************************************************************************************************/

#pragma once

#include "HAbstractMouseStrategy.h"

class HCartesianZoomPrivate;
class HCartesianCoordinate;

class HCartesianZoom : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCartesianZoom)

public:
    explicit HCartesianZoom(QWidget *parent = nullptr);

signals:
    void coordinateChanged(HCartesianCoordinate *);

public:
    void setCoordinate(HCartesianCoordinate *);
    void resetCoordinate();

public:
    bool setValidRegion(QRectF value) override;

public:
    bool mousePressEvent(QMouseEvent *) override;
    bool mouseMoveEvent(QMouseEvent *) override;
    bool mouseReleaseEvent(QMouseEvent *) override;

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

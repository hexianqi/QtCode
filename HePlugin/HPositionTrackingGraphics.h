#ifndef HPOSITIONTRACKINGGRAPHICS_H
#define HPOSITIONTRACKINGGRAPHICS_H

#include "IPositionTrackingControl.h"
#include <QGraphicsSimpleTextItem>

class HPositionTrackingGraphics : public QGraphicsSimpleTextItem, public IPositionTrackingControl
{
public:
    explicit HPositionTrackingGraphics(QGraphicsItem *parent = nullptr);

public:
    virtual void setValidRegion(QRectF value) override;
    virtual void setVisible(bool b) override;
    virtual void setText(QString text) override;
};

#endif // HPOSITIONTRACKINGGRAPHICS_H

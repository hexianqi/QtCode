#ifndef IPOSITIONTRACKINGCONTROL_H
#define IPOSITIONTRACKINGCONTROL_H

#include <QRectF>

class IPositionTrackingControl
{
public:
    virtual void setValidRegion(QRectF value) = 0;
    virtual void setVisible(bool b) = 0;
    virtual void setText(QString text) = 0;
};

#endif // IPOSITIONTRACKINGCONTROL_H

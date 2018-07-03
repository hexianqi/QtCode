#ifndef HPOSITIONTRACKING_LABEL_H
#define HPOSITIONTRACKING_LABEL_H

#include "IPositionTrackingControl.h"
#include <QLabel>

class HPositionTrackingLabel : public QLabel, public IPositionTrackingControl
{
public:
    using QLabel::QLabel;

public:
    virtual void setValidRegion(QRectF value) override;
    virtual void setVisible(bool b) override;
    virtual void setText(QString text) override;
};

#endif // HPOSITIONTRACKING_LABEL_H

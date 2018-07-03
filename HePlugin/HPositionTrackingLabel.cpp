#include "HPositionTrackingLabel.h"

void HPositionTrackingLabel::setValidRegion(QRectF value)
{
    setGeometry(value.left() + 10, value.top() + 10, value.width() - 20, fontMetrics().height());
}

void HPositionTrackingLabel::setVisible(bool b)
{
    QLabel::setVisible(b);
}

void HPositionTrackingLabel::setText(QString text)
{
    QLabel::setText(text);
}

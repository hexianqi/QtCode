#ifndef HSTATEPROGRESSBAR_P_H
#define HSTATEPROGRESSBAR_P_H

#include "HStateProgressBar.h"

HE_CONTROL_BEGIN_NAMESPACE

class HStateProgressBarPrivate
{
public:
    QString tip;
    HStateProgressBar::StateStyle stateStyle = HStateProgressBar::StateStyle_NACK;
    QColor barColor = QColor(255, 104, 124);
    QColor barBackground = QColor(100, 100, 100);
    QColor noteColor = QColor(100, 177, 243);
    QColor stateColor = QColor(255, 104, 124);
    QColor tipColor = QColor(255, 255, 255);
    QColor tipBackground = QColor(24, 189, 155);

    int maximum = 5;
    int value = 0;
    QStringList notes;
    QStringList states;

    int bigRadius;
    int smallRadius;
    int lineWidth;
    int lineHeight;
    int innerLineHeight;
};

HE_CONTROL_END_NAMESPACE

#endif // HSTATEPROGRESSBAR_P_H

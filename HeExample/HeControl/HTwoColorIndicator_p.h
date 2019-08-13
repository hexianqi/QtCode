#ifndef HTWOCOLORINDICATOR_P_H
#define HTWOCOLORINDICATOR_P_H

#include "HTwoColorIndicator.h"

HE_CONTROL_BEGIN_NAMESPACE

class HTwoColorIndicatorPrivate
{
public:
    QColor foreground = Qt::black;
    QColor background = Qt::white;
    bool active = false;
    bool dragEnabled = false;
    QPoint pressPos;
    bool foregroundPress = false;
    bool backgroundPress = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HTWOCOLORINDICATOR_P_H

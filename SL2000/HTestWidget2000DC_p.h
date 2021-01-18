#ifndef HTESTWIDGET2000DC_P_H
#define HTESTWIDGET2000DC_P_H

#include "HTestWidget2000DC.h"
#include "HTestWidget2000_p.h"

class HTestWidget2000DCPrivate : public HTestWidget2000Private
{
public:
    HTestWidget2000DCPrivate();

public:
    QAction *actionProbe = nullptr;
    QAction *actionProductInfo = nullptr;
};

#endif // HTESTWIDGET2000DC_P_H

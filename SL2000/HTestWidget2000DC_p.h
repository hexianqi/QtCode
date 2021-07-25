#pragma once

#include "HTestWidget2000DC.h"
#include "HeGui/HSpecTestWidget_p.h"

class HTestWidget2000DCPrivate : public HSpecTestWidgetPrivate
{
public:
    HTestWidget2000DCPrivate();

public:
    QAction *actionProbe = nullptr;
    QAction *actionProductInfo = nullptr;
};

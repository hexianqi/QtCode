#pragma once

#include "HTestWidget2000DC.h"
#include "HeGui/HSpecTestWidget_p.h"

class HTestWidget2000DCPrivate : public HSpecTestWidgetPrivate
{
public:
    HTestWidget2000DCPrivate();

public:
    IPrintTemplate *tagPrintTemplate = nullptr;

public:
    QAction *actionProbe = nullptr;
    QAction *actionPrintTag = nullptr;
};

#pragma once

#include "HTestWidget2000DC.h"
#include "HeGui/HSpecTestWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class IPrint;
class IPrintTemplate;
HE_DATA_END_NAMESPACE

class HTestWidget2000DCPrivate : public HSpecTestWidgetPrivate
{
public:
    HTestWidget2000DCPrivate();

public:
    IPrint *print = nullptr;
    IPrintTemplate *printTemplate = nullptr;

public:
    QAction *actionProbe = nullptr;
    QAction *actionProductInfo = nullptr;
    QAction *actionPrintTag = nullptr;
};

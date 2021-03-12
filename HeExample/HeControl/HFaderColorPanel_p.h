#pragma once

#include "HFaderColorPanel.h"
#include "HAbstractColorPanel_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFaderColorPanelPrivate : public HAbstractColorPanelPrivate
{
public:
    QColor background = Qt::transparent;
    int barSpace = 6;
    int groupSpace = 20;
};

HE_CONTROL_END_NAMESPACE

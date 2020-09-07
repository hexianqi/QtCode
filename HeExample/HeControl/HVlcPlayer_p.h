#pragma once

#include "HVlcPlayer.h"

HE_CONTROL_BEGIN_NAMESPACE

class HVlcPlayerControl;
class HFlatStyle;

class HVlcPlayerPrivate
{
public:
    HVlcPlayerPrivate();

public:
    QString fileFilter;
    HFlatStyle *style;
    HVlcPlayerControl *control = nullptr;
};

HE_CONTROL_END_NAMESPACE

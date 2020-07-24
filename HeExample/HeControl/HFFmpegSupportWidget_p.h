#pragma once

#include "HFFmpegSupportWidget.h"

class HEntireTableWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HFFmpegSupportWidgetPrivate
{
public:
    QList<HEntireTableWidget *> tableWidgets;
};

HE_CONTROL_END_NAMESPACE


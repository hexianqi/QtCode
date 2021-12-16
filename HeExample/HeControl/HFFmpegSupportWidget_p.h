#pragma once

#include "HFFmpegSupportWidget.h"

class HEntireTableWidget;

HE_BEGIN_NAMESPACE

class HFFmpegSupportWidgetPrivate
{
public:
    QList<HEntireTableWidget *> tableWidgets;
};

HE_END_NAMESPACE


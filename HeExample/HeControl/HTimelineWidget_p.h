#pragma once

#include "HTimelineWidget.h"

HE_BEGIN_NAMESPACE

class HTimelineWidgetPrivate
{
public:
    QHash<QDate, QString> infos;
};

HE_END_NAMESPACE


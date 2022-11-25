#pragma once

#include "HTimelineWidget.h"
#include <QtCore/QMap>

HE_BEGIN_NAMESPACE

class HTimelineWidgetPrivate
{
public:
    QMap<QDate, QString> infos;
};

HE_END_NAMESPACE


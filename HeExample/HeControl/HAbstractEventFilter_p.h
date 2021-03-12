#pragma once

#include "HAbstractEventFilter.h"
#include <QtCore/QHash>
#include <QtCore/QSet>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractEventFilterPrivate
{
public:
    bool enable = true;
    QSet<QObject *> watcheds;
    QHash<QEvent::Type, std::function<bool(QEvent *)>> handlers;
};

HE_CONTROL_END_NAMESPACE

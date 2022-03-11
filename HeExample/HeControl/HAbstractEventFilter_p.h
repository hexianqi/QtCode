#pragma once

#include "HAbstractEventFilter.h"
#include <QtCore/QHash>
#include <QtCore/QSet>

HE_BEGIN_NAMESPACE

class HAbstractEventFilterPrivate
{
public:
    bool enable = true;
    QSet<QObject *> watched;
    QHash<QEvent::Type, std::function<bool(QEvent *)>> handler;
};

HE_END_NAMESPACE

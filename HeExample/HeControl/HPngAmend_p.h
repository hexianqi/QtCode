#pragma once

#include "HPngAmend.h"
#include <QtCore/QFutureWatcher>

HE_CONTROL_BEGIN_NAMESPACE

class HPngAmendPrivate
{
public:
    QFutureWatcher<void> *watcher;
};

HE_CONTROL_END_NAMESPACE

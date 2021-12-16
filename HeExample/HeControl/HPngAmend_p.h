#pragma once

#include "HPngAmend.h"
#include <QtCore/QFutureWatcher>

HE_BEGIN_NAMESPACE

class HPngAmendPrivate
{
public:
    QFutureWatcher<void> *watcher;
};

HE_END_NAMESPACE

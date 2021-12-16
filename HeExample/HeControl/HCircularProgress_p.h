#pragma once

#include "HCircularProgress.h"
#include <QtCore/QMap>

HE_BEGIN_NAMESPACE

class ICircularFactory;

class HCircularProgressPrivate
{
public:
    bool reverse = false;
    int step = 36;
    int value = 0;
    QTimer *timer = nullptr;
    ICircular *circular = nullptr;
    ICircularFactory *factory = nullptr;
    QMap<QString, ICircular *> circularCache;
};

HE_END_NAMESPACE

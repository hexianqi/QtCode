#pragma once

#include "HDoublePropertyManager.h"
#include <QtCore/QMap>

class HDoublePropertyManagerPrivate
{
public:
    struct Data
    {
        QString prefix;
        QString suffix;
    };
    QMap<const QtProperty *, Data> propertyToData;
};




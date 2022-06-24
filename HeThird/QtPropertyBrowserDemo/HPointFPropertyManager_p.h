#pragma once

#include "HPointFPropertyManager.h"

class HPointFPropertyManagerPrivate
{
public:
    struct Data
    {
        QVariant value;
        QtVariantProperty *x;
        QtVariantProperty *y;
    };
    QMap<const QtProperty *, Data> propertyToData;
    QMap<const QtProperty *, QtProperty *> xToProperty;
    QMap<const QtProperty *, QtProperty *> yToProperty;
};




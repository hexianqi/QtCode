#pragma once

#include "HAbstractGradeWidget.h"

HE_BEGIN_NAMESPACE

class IDataFactory;
class IGradeItem;

class HAbstractGradeWidgetPrivate
{
public:
    HAbstractGradeWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IGrade *data = nullptr;
    QStringList optionals;
    QStringList selecteds;
    QStringList unselecteds;
    QList<IGradeItem *> items;
    bool modified = false;
};

HE_END_NAMESPACE


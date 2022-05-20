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
    QStringList optional;
    QStringList selected;
    QStringList unselected;
    QList<IGradeItem *> items;
    bool modified = false;
};

HE_END_NAMESPACE


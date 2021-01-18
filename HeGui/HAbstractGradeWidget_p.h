#pragma once

#include "HAbstractGradeWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
class IGradeItem;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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

HE_GUI_END_NAMESPACE


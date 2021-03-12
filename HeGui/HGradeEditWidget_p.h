#pragma once

#include "HGradeEditWidget.h"

class QStackedLayout;

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAbstractGradeWidget;

class HGradeEditWidgetPrivate
{
public:
    HGradeEditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    QStackedLayout *layout = nullptr;
    HAbstractGradeWidget *current = nullptr;
    QHash<QString, HAbstractGradeWidget *> widgets;
};

HE_GUI_END_NAMESPACE

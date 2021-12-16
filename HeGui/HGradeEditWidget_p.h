#pragma once

#include "HGradeEditWidget.h"

class QStackedLayout;

HE_BEGIN_NAMESPACE

class IDataFactory;
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

HE_END_NAMESPACE

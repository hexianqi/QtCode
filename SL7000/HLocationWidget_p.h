#pragma once

#include "HLocationWidget.h"
#include "HeCore/HHash.h"
#include "HeData/ITestData.h"


class QLabel;
class QGridLayout;
class HProgressBar;

HE_USE_NAMESPACE

class HLocationWidgetPrivate
{
public:
    HLocationWidgetPrivate();

public:
    QString css;
    QPolygon polygon;
    QColor colorSpacer;
    QColor colorInvalid;
    ITestData *testData = nullptr;

public:
    QHash<QPoint, QLabel *> labelTests;
    QHash<QPoint, QLabel *> labelSpacers;
    QLabel *labelError;
    HProgressBar *progressBar;
    QGridLayout *layout;
};


#pragma once

#include "HLocationWidget.h"
#include "HeData/ITestData.h"
#include <QtCore/QHash>
#include <QtCore/QPoint>

class QLabel;
class QGridLayout;
class HProgressBar;

HE_USE_NAMESPACE

uint qHash(const QPoint &key)
{
    return qHash(QPair<int, int>(key.x(), key.y()));
}

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


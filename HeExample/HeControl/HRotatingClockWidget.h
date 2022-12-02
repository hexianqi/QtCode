/***************************************************************************************************
**      2022-11-29  HRotatingClockWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HRotatingClockWidgetPrivate;

class HRotatingClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HRotatingClockWidget(QWidget *parent = nullptr);
    ~HRotatingClockWidget() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void onSecondTimer();
    void onAnimationTimer();
    int processRotate(int value, int max);
    int processPlace(int value, int max);

protected:
    QScopedPointer<HRotatingClockWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

/***************************************************************************************************
**      2023-02-01  HReelWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HReelWidgetPrivate;

class HReelWidget : public QWidget
{
    Q_OBJECT

public:
    enum State
    {
        NoRun,
        RuningUp,
        RuningDown
    };

public:
    explicit HReelWidget(QWidget *parent = nullptr);
    ~HReelWidget() override;

public:
    void setNumber(uint);

protected:
    void paintEvent(QPaintEvent *) override;
    void onTimer();
    void drawUnit(QPainter * painter, const QRect &rect, uint number);

protected:
    QScopedPointer<HReelWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE


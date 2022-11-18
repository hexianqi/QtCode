/***************************************************************************************************
**      2022-11-17  HLotteryTurntable
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HLotteryTurntableWidgetPrivate;

class HLotteryTurntableWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rotate READ rotate WRITE setRotate MEMBER painterRotate)

public:
    explicit HLotteryTurntableWidget(QWidget *parent = nullptr);
    ~HLotteryTurntableWidget() override;

public:
    int rotate();
    void setRotate(int);

protected:
    HLotteryTurntableWidget(HLotteryTurntableWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void init();

protected:
    QScopedPointer<HLotteryTurntableWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE


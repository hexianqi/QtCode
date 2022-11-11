/***************************************************************************************************
**      2022-11-01  HOnOffWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HOnOffWidgetPrivate;

class HOnOffWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HOnOffWidget(QWidget *parent = nullptr);
    ~HOnOffWidget() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void onTimer();

protected:
    QScopedPointer<HOnOffWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE



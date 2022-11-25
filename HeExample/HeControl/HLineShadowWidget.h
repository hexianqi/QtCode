/***************************************************************************************************
**      2022-11-21  HLineShadowWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HLineShadowWidgetPrivate;

class HLineShadowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HLineShadowWidget(QWidget *parent = nullptr);
    ~HLineShadowWidget() override;

protected:
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HLineShadowWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE


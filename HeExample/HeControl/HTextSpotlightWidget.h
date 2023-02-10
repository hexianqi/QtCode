/***************************************************************************************************
**      2022-12-27  HTextSpotlightWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HTextSpotlightWidgetPrivate;

class HTextSpotlightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HTextSpotlightWidget(QWidget *parent = nullptr);
    ~HTextSpotlightWidget() override;

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void onTimer();

protected:
    QScopedPointer<HTextSpotlightWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE


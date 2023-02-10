/***************************************************************************************************
**      2022-12-15  HGradientProgressBar
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QProgressBar>

HE_BEGIN_NAMESPACE

class HGradientProgressBarPrivate;

class HGradientProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit HGradientProgressBar(QWidget *parent = nullptr);
    ~HGradientProgressBar() override;

protected:
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HGradientProgressBarPrivate> d_ptr;
};

HE_END_NAMESPACE


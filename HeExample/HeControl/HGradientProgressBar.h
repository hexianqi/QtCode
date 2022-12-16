/***************************************************************************************************
**      2022-12-15  HGradientProgressBar
***************************************************************************************************/

#pragma once

#include "QProgressBar.h"

HE_BEGIN_NAMESPACE

class HGradientProgressBarPrivate;

class HGradientProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit HGradientProgressBar(QWidget *parent = nullptr);
    ~HGradientProgressBar() override;

protected:
    HGradientProgressBar(HGradientProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HGradientProgressBarPrivate> d_ptr;
};

HE_END_NAMESPACE


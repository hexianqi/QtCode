/***************************************************************************************************
**      2019-03-22  HSpecPelsWaveWidget 像元波长配置窗体。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HEntireTableWidget.h"

HE_BEGIN_NAMESPACE

class HSpecPelsWave;
class HSpecPelsWaveWidgetPrivate;

class HSpecPelsWaveWidget : public HEntireTableWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecPelsWaveWidget)

public:
    explicit HSpecPelsWaveWidget(QWidget *parent = nullptr);
    ~HSpecPelsWaveWidget() override;

public:
    void setData(HSpecPelsWave *);
    void saveData();
    void showData();

private:
    void init();
};

HE_END_NAMESPACE

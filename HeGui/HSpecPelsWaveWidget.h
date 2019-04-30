/***************************************************************************************************
**      2019-03-22  HSpecPelsWaveWidget 像元波长配置窗体。
***************************************************************************************************/

#ifndef HSPECPELSWAVEWIDGET_H
#define HSPECPELSWAVEWIDGET_H

#include "HGuiGlobal.h"
#include "HePlugin/HEntireTableWidget.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class HSpecPelsWave;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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

HE_GUI_END_NAMESPACE

#endif // HSPECPELSWAVEWIDGET_H

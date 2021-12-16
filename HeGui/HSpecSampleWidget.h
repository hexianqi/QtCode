/***************************************************************************************************
**      2019-03-28  HSpecSampleWidget 光谱采样窗体。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HVernierWidget.h"

HE_BEGIN_NAMESPACE

class HSpecSampleWidgetPrivate;

class HSpecSampleWidget : public HVernierWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecSampleWidget)

public:
    explicit HSpecSampleWidget(QWidget *parent = nullptr);
    ~HSpecSampleWidget() override;

public:
    void setEnablePeak(bool b);
    void refreshWidget();
    void refreshCenter();
    void refreshRight();

protected slots:
    void setCurve1Visible(bool b);
    void setCurve2Visible(bool b);
    void setVernier(const QList<double> &value);

private:
    void init();
};

HE_END_NAMESPACE

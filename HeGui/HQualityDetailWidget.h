/***************************************************************************************************
**      2019-05-06  HQualityDetailWidget 品质数据窗口部件。
***************************************************************************************************/

#ifndef HQUALITYDETAILWIDGET_H
#define HQUALITYDETAILWIDGET_H

#include "HAbstractDataDetailWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IQuality;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HQualityDetailWidgetPrivate;

class HQualityDetailWidget : public HAbstractDataDetailWidget<IQuality>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HQualityDetailWidget)

public:
    explicit HQualityDetailWidget(QWidget *parent = nullptr);
    ~HQualityDetailWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

private:
    void init();
};

HE_GUI_END_NAMESPACE

#endif // HQUALITYDETAILWIDGET_H

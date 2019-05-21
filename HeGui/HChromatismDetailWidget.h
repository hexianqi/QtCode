/***************************************************************************************************
**      2019-05-20  HChromatismDetailWidget 色容差数据窗口部件。
***************************************************************************************************/

#ifndef HCHROMATISMDETAILWIDGET_H
#define HCHROMATISMDETAILWIDGET_H

#include "HAbstractDataDetailWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IChromatism;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HChromatismDetailWidgetPrivate;

class HChromatismDetailWidget : public HAbstractDataDetailWidget<IChromatism>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismDetailWidget)

public:
    explicit HChromatismDetailWidget(QWidget *parent = nullptr);
    ~HChromatismDetailWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

private:
    void init();
};

HE_GUI_END_NAMESPACE

#endif // HCHROMATISMDETAILWIDGET_H

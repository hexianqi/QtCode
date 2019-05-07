/***************************************************************************************************
**      2019-04-28  HAdjustDetailWidget 调整数据窗口部件。
***************************************************************************************************/

#ifndef HADJUSTDETAILWIDGET_H
#define HADJUSTDETAILWIDGET_H

#include "HAbstractDataDetailWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IAdjust;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustDetailWidgetPrivate;

class HAdjustDetailWidget : public HAbstractDataDetailWidget<IAdjust>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjustDetailWidget)

public:
    explicit HAdjustDetailWidget(QWidget *parent = nullptr);
    ~HAdjustDetailWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

private:
    void init();
    void editData();
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTDETAILWIDGET_H

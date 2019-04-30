/***************************************************************************************************
**      2019-04-22  HGradeDetailWidget 分级数据窗口部件。
***************************************************************************************************/

#ifndef HGRADEDETAILWIDGET_H
#define HGRADEDETAILWIDGET_H

#include "HAbstractDataDetailWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IGrade;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HGradeDetailWidgetPrivate;

class HGradeDetailWidget : public HAbstractDataDetailWidget<IGrade>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGradeDetailWidget)

public:
    explicit HGradeDetailWidget(QWidget *parent = nullptr);
    ~HGradeDetailWidget();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

private:
    void init();
};

HE_GUI_END_NAMESPACE

#endif // HGRADEDETAILWIDGET_H

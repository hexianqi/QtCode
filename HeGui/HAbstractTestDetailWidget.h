/***************************************************************************************************
**      2019-03-26  HAbstractTestDetailWidget 抽象详情窗体类。
***************************************************************************************************/

#pragma once

#include "ITestDetailWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HAbstractTestDetailWidgetPrivate;

class HE_GUI_EXPORT HAbstractTestDetailWidget : public ITestDetailWidget
{
    Q_OBJECT

public:
    explicit HAbstractTestDetailWidget(QWidget *parent = nullptr);
    ~HAbstractTestDetailWidget() override;

public:
    void initialize(QVariantMap param) override;

protected:
    HAbstractTestDetailWidget(HAbstractTestDetailWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractTestDetailWidgetPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

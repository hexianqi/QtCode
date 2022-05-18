/***************************************************************************************************
**      2019-03-26  HAbstractTestDetailWidget 抽象详情窗体类。
***************************************************************************************************/

#pragma once

#include "ITestDetailWidget.h"

HE_BEGIN_NAMESPACE

class HAbstractTestDetailWidgetPrivate;

class HAbstractTestDetailWidget : public ITestDetailWidget
{
    Q_OBJECT

public:
    explicit HAbstractTestDetailWidget(QWidget *parent = nullptr);
    ~HAbstractTestDetailWidget() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void refreshWidget() override;
    void refreshData(QString) override;
    void refreshData(QStringList) override;

protected:
    HAbstractTestDetailWidget(HAbstractTestDetailWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void init();
    virtual void initHash() = 0;

protected:
    QScopedPointer<HAbstractTestDetailWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

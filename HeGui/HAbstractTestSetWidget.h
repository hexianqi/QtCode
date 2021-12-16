/***************************************************************************************************
**      2019-03-28  HAbstractTestSetWidget 抽象测试设置窗体类。
***************************************************************************************************/

#pragma once

#include "ITestSetWidget.h"

HE_BEGIN_NAMESPACE

class HAbstractTestSetWidgetPrivate;

class HAbstractTestSetWidget : public ITestSetWidget
{
    Q_OBJECT

public:
    explicit HAbstractTestSetWidget(QWidget *parent = nullptr);

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;
    bool setTestState(bool b) override;
    bool testState() override;
    bool setTestMode(int value) override;
    int testMode() override;
    bool setSaveMode(int value) override;
    int saveMode() override;

protected:
    HAbstractTestSetWidget(HAbstractTestSetWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractTestSetWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

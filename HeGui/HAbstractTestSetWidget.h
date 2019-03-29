/***************************************************************************************************
**      2019-03-28  HAbstractTestSetWidget   抽象测试设置窗体类。
***************************************************************************************************/

#ifndef HABSTRACTTESTSETWIDGET_H
#define HABSTRACTTESTSETWIDGET_H

#include "ITestSetWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HAbstractTestSetWidgetPrivate;

class HE_GUI_EXPORT HAbstractTestSetWidget : public ITestSetWidget
{
    Q_OBJECT
public:
    explicit HAbstractTestSetWidget(QWidget *parent = nullptr);
    ~HAbstractTestSetWidget() override;

public:
    void initialize(QVariantMap param) override;
    bool setTestState(bool b) override;
    bool setTestMode(int value) override;
    bool testState() override;
    int testMode() override;

protected:
    HAbstractTestSetWidget(HAbstractTestSetWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractTestSetWidgetPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTTESTSETWIDGET_H

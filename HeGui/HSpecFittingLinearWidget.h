/***************************************************************************************************
**      2019-03-27  HSpecFittingLinearWidget 拟合配置窗体（线性）。
***************************************************************************************************/

#pragma once

#include "HSpecFittingWidget.h"

namespace Ui {
class HSpecFittingLinearWidget;
}

HE_BEGIN_NAMESPACE

class HSpecFittingLinearWidgetPrivate;

class HSpecFittingLinearWidget : public HSpecFittingWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecFittingLinearWidget)

public:
    explicit HSpecFittingLinearWidget(QWidget *parent = nullptr);
    ~HSpecFittingLinearWidget() override;

public:
    bool setTestState(bool b) override;

protected:
    bool initParam() override;
    void saveData() override;
    void showData() override;

private:
    void init();

private:
    Ui::HSpecFittingLinearWidget *ui;
};

HE_END_NAMESPACE

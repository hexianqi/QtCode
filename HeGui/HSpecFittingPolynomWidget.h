/***************************************************************************************************
**      2019-07-22  HSpecFittingPolynomWidget 拟合配置窗体（多项式）。
***************************************************************************************************/

#ifndef HSPECFITTINGPOLYNOMWIDGET_H
#define HSPECFITTINGPOLYNOMWIDGET_H

#include "HSpecFittingWidget.h"

namespace Ui {
class HSpecFittingPolynomWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HSpecFittingPolynomWidgetPrivate;

class HE_GUI_EXPORT HSpecFittingPolynomWidget : public HSpecFittingWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecFittingPolynomWidget)

public:
    explicit HSpecFittingPolynomWidget(QWidget *parent = nullptr);
    ~HSpecFittingPolynomWidget() override;

public:
    bool setTestState(bool b) override;

protected:
    bool initParam() override;
    void saveData() override;
    void showData() override;

private:
    void init();

private:
    Ui::HSpecFittingPolynomWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HSPECFITTINGPOLYNOMWIDGET_H

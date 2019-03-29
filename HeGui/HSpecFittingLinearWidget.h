/***************************************************************************************************
**      2019-03-27  HSpecFittingLinearWidget 拟合配置窗体（线性）。
***************************************************************************************************/

#ifndef HSPECFITTINGLINEARWIDGET_H
#define HSPECFITTINGLINEARWIDGET_H

#include "HSpecFittingWidget.h"

namespace Ui {
class HSpecFittingLinearWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HSpecFittingLinearWidgetPrivate;

class HE_GUI_EXPORT HSpecFittingLinearWidget : public HSpecFittingWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecFittingLinearWidget)

public:
    explicit HSpecFittingLinearWidget(HSpecFitting *data, QWidget *parent = nullptr);
    ~HSpecFittingLinearWidget() override;

protected:
    bool initParam() override;
    void saveData() override;
    void showData() override;

private:
    void init();

private:
    Ui::HSpecFittingLinearWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HSPECFITTINGLINEARWIDGET_H

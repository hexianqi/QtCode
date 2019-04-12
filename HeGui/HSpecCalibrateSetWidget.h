/***************************************************************************************************
**      2019-04-11  HSpecCalibrateSetWidget 光谱校准设置窗体。
***************************************************************************************************/

#ifndef HSPECCALIBRATESETWIDGET_H
#define HSPECCALIBRATESETWIDGET_H

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HSpecCalibrateSetWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HSpecCalibrateSetWidgetPrivate;

class HE_GUI_EXPORT HSpecCalibrateSetWidget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateSetWidget)

public:
    explicit HSpecCalibrateSetWidget(QWidget *parent = nullptr);
    ~HSpecCalibrateSetWidget() override;

public:
    QString typeName() override;
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;
    bool setTestMode(int value) override;

protected slots:
    void setIntegralTimeAuto(bool b);
    void on_doubleSpinBox_01_editingFinished();
    void on_checkBox_01_clicked(bool b);
    void on_checkBox_02_clicked(bool b);
    void on_radioButton_01_clicked();
    void on_radioButton_02_clicked();

private:
    void init();

private:
    Ui::HSpecCalibrateSetWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATESETWIDGET_H

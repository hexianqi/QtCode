/***************************************************************************************************
**      2019-04-11  HSpecCalibrateSet2Widget 光谱校准设置窗体（带电）。
***************************************************************************************************/

#ifndef HSPECCALIBRATESET2WIDGET_H
#define HSPECCALIBRATESET2WIDGET_H

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HSpecCalibrateSet2Widget;
}

HE_GUI_BEGIN_NAMESPACE

class HSpecCalibrateSet2WidgetPrivate;

class HSpecCalibrateSet2Widget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateSet2Widget)

public:
    explicit HSpecCalibrateSet2Widget(QWidget *parent = nullptr);
    ~HSpecCalibrateSet2Widget();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;
    bool setTestMode(int value) override;

protected slots:
    void setIntegralTimeAuto(bool b);
    void on_doubleSpinBox_01_valueChanged(double value);
    void on_checkBox_01_clicked(bool b);
    void on_checkBox_02_clicked(bool b);
    void on_checkBox_03_clicked(bool b);
    void on_radioButton_01_clicked();
    void on_radioButton_02_clicked();

protected:
    bool adjustIntegralTime();

private:
    void init();

private:
    Ui::HSpecCalibrateSet2Widget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATESET2WIDGET_H

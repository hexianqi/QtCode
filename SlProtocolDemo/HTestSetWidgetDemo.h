#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HTestSetWidgetDemo;
}

class HTestSetWidgetDemoPrivate;

class HTestSetWidgetDemo : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidgetDemo)

public:
    explicit HTestSetWidgetDemo(QWidget *parent = nullptr);
    ~HTestSetWidgetDemo() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_1_valueChanged(double value);
    void on_spinBox_1_valueChanged(int value);
    void on_spinBox_2_valueChanged(int value);
    void on_checkBox_1_clicked(bool b);
    void on_checkBox_2_clicked(bool b);
    void on_comboBox_1_currentIndexChanged(int value);

private:
    void init();

private:
    Ui::HTestSetWidgetDemo *ui;
};

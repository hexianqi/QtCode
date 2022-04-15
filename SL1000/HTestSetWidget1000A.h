#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HTestSetWidget1000A;
}

class HTestSetWidget1000APrivate;

class HTestSetWidget1000A : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget1000A)

public:
    explicit HTestSetWidget1000A(QWidget *parent = nullptr);
    ~HTestSetWidget1000A() override;

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_1_valueChanged(double value);
    void on_doubleSpinBox_2_valueChanged(double value);
    void on_doubleSpinBox_3_valueChanged(double value);
    void on_doubleSpinBox_4_valueChanged(double value);
    void on_checkBox_1_clicked(bool b);
    void on_checkBox_2_clicked(bool b);
    void on_comboBox_1_currentIndexChanged(int value);
    void on_comboBox_2_currentIndexChanged(int value);
    void on_comboBox_3_currentIndexChanged(int value);

protected:
    bool adjustIntegralTime();
    bool adjustLuminousGears();

private:
    void init();

private:
    Ui::HTestSetWidget1000A *ui;
};


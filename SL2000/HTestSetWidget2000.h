#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HTestSetWidget2000;
}

class HTestSetWidget2000Private;

class HTestSetWidget2000 : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget2000)

public:
    explicit HTestSetWidget2000(QWidget *parent = nullptr);
    ~HTestSetWidget2000() override;

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_1_valueChanged(double value);
    void on_checkBox_1_clicked(bool b);
    void on_comboBox_1_currentIndexChanged(int value);

protected:
    bool adjustIntegralTime();

private:
    void init();

private:
    Ui::HTestSetWidget2000 *ui;
};

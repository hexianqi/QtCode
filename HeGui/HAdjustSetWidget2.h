#pragma once

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HAdjustSetWidget2;
}

HE_BEGIN_NAMESPACE

class HAdjustSetWidget2Private;

class HAdjustSetWidget2 : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjustSetWidget2)

public:
    explicit HAdjustSetWidget2(QWidget *parent = nullptr);
    ~HAdjustSetWidget2() override;

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_01_valueChanged(double value);
    void on_checkBox_01_clicked(bool b);
    void on_checkBox_02_clicked(bool b);
    void on_checkBox_03_clicked(bool b);

protected:
    bool adjustIntegralTime();

private:
    void init();

private:
    Ui::HAdjustSetWidget2 *ui;
};

HE_END_NAMESPACE

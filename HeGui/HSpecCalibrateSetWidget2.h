/***************************************************************************************************
**      2019-04-11  HSpecCalibrateSet2Widget 光谱校准设置窗体（带电）。
***************************************************************************************************/

#pragma once

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HSpecCalibrateSetWidget2;
}

HE_BEGIN_NAMESPACE

class HSpecCalibrateSetWidget2Private;

class HSpecCalibrateSetWidget2 : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateSetWidget2)

public:
    explicit HSpecCalibrateSetWidget2(QWidget *parent = nullptr);
    ~HSpecCalibrateSetWidget2();

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;
    bool setTestMode(int value) override;

protected slots:
    void setAutoIntegralTime(bool b);
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
    Ui::HSpecCalibrateSetWidget2 *ui;
};

HE_END_NAMESPACE

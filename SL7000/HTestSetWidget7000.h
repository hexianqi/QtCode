#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HTestSetWidget7000;
}

class HTestSetWidget7000Private;

class HTestSetWidget7000 : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget7000)

public:
    explicit HTestSetWidget7000(QWidget *parent = nullptr);
    ~HTestSetWidget7000() override;

public:
    QString typeName() override;

public:
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_checkBox_1_clicked(bool b);
    void on_checkBox_2_clicked(bool b);
    void setLuminousGears(int value);
    void setMotorLocation(int value);
    void setCurrentGears(int value);

protected:
    bool adjustIntegralTime();
    bool adjustLuminousGears();

private:
    void init();

private:
    Ui::HTestSetWidget7000 *ui;
};


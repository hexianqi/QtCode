#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HTestSetWidget2000DC;
}

class HTestSetWidget2000DCPrivate;

class HTestSetWidget2000DC : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget2000DC)

public:
    explicit HTestSetWidget2000DC(QWidget *parent = nullptr);
    ~HTestSetWidget2000DC() override;

public:
    QString typeName() override;

public:
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_checkBox_1_clicked(bool b);
    void on_checkBox_2_clicked(bool b);
    bool setTestMode(int value) override;
    void setCurrentGears(int value);
    void setLuminousGears(int value);

protected:
    bool adjustIntegralTime();
    bool adjustLuminousGears();

private:
    void init();

private:
    Ui::HTestSetWidget2000DC *ui;
};

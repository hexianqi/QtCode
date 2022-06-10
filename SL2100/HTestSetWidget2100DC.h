#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HTestSetWidget2100DC;
}

class HTestSetWidget2100DCPrivate;

class HTestSetWidget2100DC : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget2100DC)

public:
    explicit HTestSetWidget2100DC(QWidget *parent = nullptr);
    ~HTestSetWidget2100DC();

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_checkBox_1_clicked(bool b);
    bool setTestMode(int value) override;

protected:
    bool adjustIntegralTime();

private:
    void init();

private:
    Ui::HTestSetWidget2100DC *ui;
};


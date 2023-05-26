#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HTestSetWidget1000I;
}

class HTestSetWidget1000IPrivate;

class HTestSetWidget1000I : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget1000I)

public:
    explicit HTestSetWidget1000I(QWidget *parent = nullptr);
    ~HTestSetWidget1000I() override;

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

private:
    void init();

private:
    Ui::HTestSetWidget1000I *ui;
};


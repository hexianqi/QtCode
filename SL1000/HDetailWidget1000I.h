#pragma once

#include "HeGui/HAbstractTestDetailWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HDetailWidget1000I;
}

class HDetailWidget1000APrivate;

class HDetailWidget1000I : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDetailWidget1000A)

public:
    explicit HDetailWidget1000I(QWidget *parent = nullptr);
    ~HDetailWidget1000I()override;

public:
    QString typeName() override;

protected:
    void initHash() override;

private:
    Ui::HDetailWidget1000I *ui;
};


#pragma once

#include "HeGui/HAbstractTestDetailWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HDetailWidget1000A;
}

class HDetailWidget1000APrivate;

class HDetailWidget1000A : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDetailWidget1000A)

public:
    explicit HDetailWidget1000A(QWidget *parent = nullptr);
    ~HDetailWidget1000A() override;

public:
    QString typeName() override;

protected:
    void initHash() override;

private:
    Ui::HDetailWidget1000A *ui;
};


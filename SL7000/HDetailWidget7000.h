#pragma once

#include "HeGui/HAbstractTestDetailWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HDetailWidget7000;
}

class HDetailWidget7000Private;

class HDetailWidget7000 : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDetailWidget7000)

public:
    explicit HDetailWidget7000(QWidget *parent = nullptr);
    ~HDetailWidget7000() override;

public:
    QString typeName() override;

protected:
    void initHash() override;

private:
    Ui::HDetailWidget7000 *ui;
};


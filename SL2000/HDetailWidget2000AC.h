#pragma once

#include "HeGui/HAbstractTestDetailWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HDetailWidget2000AC;
}

class HDetailWidget2000ACPrivate;

class HDetailWidget2000AC : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDetailWidget2000AC)

public:
    explicit HDetailWidget2000AC(QWidget *parent = nullptr);
    ~HDetailWidget2000AC();

public:
    QString typeName() override;

public:
    void refreshWidget() override;

private:
    Ui::HDetailWidget2000AC *ui;
};


#pragma once

#include "HeGui/HAbstractTestDetailWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HDetailWidget2100DC;
}

class HDetailWidget2100DCPrivate;

class HDetailWidget2100DC : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDetailWidget2100DC)

public:
    explicit HDetailWidget2100DC(QWidget *parent = nullptr);
    ~HDetailWidget2100DC();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void refreshWidget() override;

private:
    Ui::HDetailWidget2100DC *ui;
};


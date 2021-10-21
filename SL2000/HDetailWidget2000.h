#pragma once

#include "HeGui/HAbstractTestDetailWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HDetailWidget2000;
}

class HDetailWidget2000Private;

class HDetailWidget2000 : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDetailWidget2000)

public:
    explicit HDetailWidget2000(QWidget *parent = nullptr);
    ~HDetailWidget2000() override;

public:
    QString typeName() override;

public:
    void refreshWidget() override;

private:
    Ui::HDetailWidget2000 *ui;
};

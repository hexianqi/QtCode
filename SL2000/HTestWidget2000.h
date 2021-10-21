#pragma once

#include "HeGui/HSpecTestWidget.h"

HE_GUI_USE_NAMESPACE

class HTestWidget2000Private;

class HTestWidget2000 : public HSpecTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget2000)

public:
    explicit HTestWidget2000(QWidget *parent = nullptr);
    ~HTestWidget2000() override;

public:
    QString typeName() override;

protected:
    void createWidget() override;
};

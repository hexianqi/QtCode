/***************************************************************************************************
**      2021-04-08  HTestWidget2000AC
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecTestWidget.h"

HE_GUI_USE_NAMESPACE

class HTestWidget2000ACPrivate;

class HTestWidget2000AC : public HSpecTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget2000AC)

public:
    explicit HTestWidget2000AC(QWidget *parent = nullptr);
    ~HTestWidget2000AC() override;

public:
    QString typeName() override;

protected:
    void createWidget() override;
};




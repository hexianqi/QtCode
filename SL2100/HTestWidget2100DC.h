/***************************************************************************************************
**      2021-01-27  HTestWidget2100DC
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecTestWidget.h"

HE_USE_NAMESPACE

class HTestWidget2100DCPrivate;

class HTestWidget2100DC : public HSpecTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget2100DC)

public:
    explicit HTestWidget2100DC(QWidget *parent = nullptr);
    ~HTestWidget2100DC() override;

public:
    QString typeName() override;

protected:
    void createWidget() override;
};




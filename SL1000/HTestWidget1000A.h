/***************************************************************************************************
**      2022-04-12  HTestWidget1000A
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecTestWidget.h"

HE_USE_NAMESPACE

class HTestWidget1000APrivate;

class HTestWidget1000A : public HSpecTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget1000A)

public:
    explicit HTestWidget1000A(QWidget *parent = nullptr);
    ~HTestWidget1000A() override;

public:
    QString typeName() override;

protected:
    void init() override;
    void createWidget() override;
};




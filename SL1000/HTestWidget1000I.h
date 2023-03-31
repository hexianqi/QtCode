/***************************************************************************************************
**      2023-03-29  HTestWidget1000I
***************************************************************************************************/

#pragma once

#include "HeGui/HTestWidget.h"

HE_USE_NAMESPACE

class HTestWidget1000IPrivate;

class HTestWidget1000I : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget1000I)

public:
    explicit HTestWidget1000I(QWidget *parent = nullptr);
    ~HTestWidget1000I() override;

public:
    QString typeName() override;

protected:
    void createWidget() override;
};

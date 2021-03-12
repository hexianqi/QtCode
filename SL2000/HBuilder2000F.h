/***************************************************************************************************
**      2021-03-11  HBuilder2000F
***************************************************************************************************/

#pragma once

#include "HBuilder2000DC.h"

class HBuilder2000FPrivate;

class HBuilder2000F : public HBuilder2000DC
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBuilder2000F)

public:
    explicit HBuilder2000F(QObject *parent = nullptr);
    ~HBuilder2000F() override;

public:
    QString typeName() override;

protected:
    void buildConfigManage() override;
    void buildMenu() override;
};




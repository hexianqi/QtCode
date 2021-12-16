/***************************************************************************************************
**      2021-03-11  HMainWindow2000F
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow2000FPrivate;

class HMainWindow2000F : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2000F)

public:
    explicit HMainWindow2000F(QWidget *parent = nullptr, const HConstructionCallHelper &helper = HConstructionCallHelper());
    ~HMainWindow2000F() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
    void initWindow() override;
};




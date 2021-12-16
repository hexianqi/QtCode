/***************************************************************************************************
**      2021-02-02  HMainWindow2000AC
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow2000ACPrivate;

class HMainWindow2000AC : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2000AC)

public:
    explicit HMainWindow2000AC(QWidget *parent = nullptr, const HConstructionCallHelper &helper = HConstructionCallHelper());
    ~HMainWindow2000AC() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};

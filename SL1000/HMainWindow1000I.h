/***************************************************************************************************
**      2023-03-27  HMainWindow1000I
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow1000IPrivate;

class HMainWindow1000I : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow1000I)

public:
    explicit HMainWindow1000I(QWidget *parent = nullptr, const HConstructionCallHelper &helper = HConstructionCallHelper());
    ~HMainWindow1000I() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};




/***************************************************************************************************
**      2022-12-06  HMainWindow1000RGB
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow1000RGBPrivate;

class HMainWindow1000RGB : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow1000RGB)

public:
    HMainWindow1000RGB(QWidget *parent = nullptr);
    ~HMainWindow1000RGB() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};

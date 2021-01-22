/***************************************************************************************************
**      2021-01-18  HMainWindow2000DC
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_GUI_USE_NAMESPACE

class HMainWindow2100DCPrivate;

class HMainWindow2100DC : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2100DC)

public:
    explicit HMainWindow2100DC(QWidget *parent = nullptr, const HCallorHelper &helper = HCallorHelper());
    ~HMainWindow2100DC() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};

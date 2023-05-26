/***************************************************************************************************
**      2019-10-23  HMainWindow2000DC
***************************************************************************************************/

#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow2000DCPrivate;

class HMainWindow2000DC : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2000DC)

public:
    explicit HMainWindow2000DC(QWidget *parent = nullptr);
    ~HMainWindow2000DC() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
    void initWindow() override;
};

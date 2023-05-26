#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow7000Private;

class HMainWindow7000 : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow7000)

public:
    HMainWindow7000(QWidget *parent = nullptr);
    ~HMainWindow7000() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
    void initWindow() override;
};

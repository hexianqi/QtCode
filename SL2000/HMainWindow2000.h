#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow2000Private;

class HMainWindow2000 : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2000)

public:
    explicit HMainWindow2000(QWidget *parent = nullptr, const HConstructionCallHelper &helper = HConstructionCallHelper());
    ~HMainWindow2000() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};


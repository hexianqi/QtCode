#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindowSpecPrivate;

class HMainWindowSpec : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindowSpec)

public:
    HMainWindowSpec(QWidget *parent = nullptr);
    ~HMainWindowSpec() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};

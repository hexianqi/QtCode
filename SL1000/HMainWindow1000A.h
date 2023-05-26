#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_USE_NAMESPACE

class HMainWindow1000APrivate;

class HMainWindow1000A : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow1000A)

public:
    HMainWindow1000A(QWidget *parent = nullptr);
    ~HMainWindow1000A() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
    void initWindow() override;
};

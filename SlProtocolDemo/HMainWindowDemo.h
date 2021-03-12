#pragma once

#include "HeGui/HAbstractMainWindow.h"

HE_GUI_USE_NAMESPACE

class HMainWindowDemoPrivate;

class HMainWindowDemo : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindowDemo)

public:
    HMainWindowDemo(QWidget *parent = nullptr, const HCallorHelper &helper = HCallorHelper());
    ~HMainWindowDemo() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};

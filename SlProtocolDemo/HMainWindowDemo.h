#ifndef HMAINWINDOWDEMO_H
#define HMAINWINDOWDEMO_H

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

#endif // HMAINWINDOWDEMO_H

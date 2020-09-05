#ifndef HMAINWINDOWSPEC_H
#define HMAINWINDOWSPEC_H

#include "HeGui/HAbstractMainWindow.h"

HE_GUI_USE_NAMESPACE

class HMainWindowSpecPrivate;

class HMainWindowSpec : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindowSpec)

public:
    HMainWindowSpec(QWidget *parent = nullptr, const HCallorHelper &helper = HCallorHelper());
    ~HMainWindowSpec() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
    void importCurve();
    void exportCurve();
};

#endif // HMAINWINDOWSPEC_H

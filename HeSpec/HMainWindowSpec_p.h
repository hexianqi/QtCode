#ifndef HMAINWINDOWSPEC_P_H
#define HMAINWINDOWSPEC_P_H

#include "HMainWindowSpec.h"
#include "HeGui/HAbstractMainWindow_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

class HMainWindowSpecPrivate : public HAbstractMainWindowPrivate
{
public:
    using HAbstractMainWindowPrivate::HAbstractMainWindowPrivate;

public:
    IConfigManage *configManage = nullptr;
    QAction *actionSetRam = nullptr;
    QAction *actionGetRam = nullptr;
    QAction *actionImportCurve = nullptr;
    QAction *actionExportCurve = nullptr;
};

#endif // HMAINWINDOWSPEC_P_H

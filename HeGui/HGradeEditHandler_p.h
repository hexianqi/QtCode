#ifndef HGRADEEDITHANDLER_P_H
#define HGRADEEDITHANDLER_P_H

#include "HGradeEditHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HGradeEditHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HGradeEditHandlerPrivate();

public:
    IConfigManage *configManage;
    QStringList gradeOptionals;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEEDITHANDLER_P_H

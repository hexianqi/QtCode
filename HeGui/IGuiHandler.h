/***************************************************************************************************
**      2019-03-01  IGuiHandler Gui处理者接口。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IHandler.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IGuiHandler : public QObject, public IHandler
{
    Q_OBJECT

public:
    using QObject::QObject;
};

HE_GUI_END_NAMESPACE

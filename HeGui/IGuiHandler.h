#ifndef IGUIHANDLER_H
#define IGUIHANDLER_H

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

#endif // IGUIHANDLER_H

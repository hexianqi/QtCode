/***************************************************************************************************
**      2020-03-26  HAbstractConfigHandler
***************************************************************************************************/

#ifndef HABSTRACTCONFIGHANDLER_H
#define HABSTRACTCONFIGHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HAbstractConfigHandlerPrivate;

class HAbstractConfigHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractConfigHandler)

public:
    explicit HAbstractConfigHandler(QObject *parent = nullptr);
    ~HAbstractConfigHandler() override;

protected:
    HAbstractConfigHandler(HAbstractConfigHandlerPrivate &p, QObject *parent = nullptr);
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTCONFIGHANDLER_H
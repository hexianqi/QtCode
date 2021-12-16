/***************************************************************************************************
**      2020-03-26  HAbstractConfigHandler
***************************************************************************************************/

#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class HAbstractConfigHandlerPrivate;

class HAbstractConfigHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractConfigHandler)

public:
    explicit HAbstractConfigHandler(QObject *parent = nullptr);

protected:
    HAbstractConfigHandler(HAbstractConfigHandlerPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

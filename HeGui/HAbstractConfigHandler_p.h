#pragma once

#include "HAbstractConfigHandler.h"
#include "HAbstractGuiHandler_p.h"

HE_BEGIN_NAMESPACE

class IConfigManage;
class IModel;

class HAbstractConfigHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HAbstractConfigHandlerPrivate();

public:
    IConfigManage *configManage;
    IModel *model;
};

HE_END_NAMESPACE

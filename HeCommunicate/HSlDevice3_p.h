#pragma once

#include "HSlDevice1_p.h"
#include "HSlDevice3.h"
#include <QtCore/QSharedPointer>

HE_BEGIN_NAMESPACE

class ICodec;

class HSlDevice3Private : public HSlDevice1Private
{
public:
    ICodec *codec;
};

HE_END_NAMESPACE

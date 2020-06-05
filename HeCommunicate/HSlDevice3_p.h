#pragma once

#include "HSlDevice1_p.h"
#include "HSlDevice3.h"
#include <QtCore/QSharedPointer>

HE_COMMUNICATE_BEGIN_NAMESPACE

class ICodec;

class HSlDevice3Private : public HSlDevice1Private
{
public:
    HSlDevice3Private();

public:
    QSharedPointer<ICodec> codec;
};

HE_COMMUNICATE_END_NAMESPACE

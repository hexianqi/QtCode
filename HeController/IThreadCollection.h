/***************************************************************************************************
**      2018-06-19  IThreadCollection 线程集合接口。
***************************************************************************************************/

#pragma once

#include "HeCore/HCollection.h"

HE_BEGIN_NAMESPACE

class IThread;

class IThreadCollection : public HCollection<IThread>
{
public:
    using HCollection::HCollection;
};

HE_END_NAMESPACE

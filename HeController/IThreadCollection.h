/***************************************************************************************************
**      2018-06-19  IThreadCollection 线程集合接口。
***************************************************************************************************/

#pragma once

#include "HControllerGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThread;

class IThreadCollection : public HCollection<IThread>
{
public:
    using HCollection::HCollection;
};

HE_CONTROLLER_END_NAMESPACE

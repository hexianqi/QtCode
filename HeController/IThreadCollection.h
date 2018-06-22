/***************************************************************************************************
**      2018-06-19  IThreadCollection 线程集合接口。
***************************************************************************************************/

#ifndef ITHREADCOLLECTION_H
#define ITHREADCOLLECTION_H

#include "HControllerGlobal.h"
#include "HeCore/ICollection.h"

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThread;

class IThreadCollection : virtual public ICollection<IThread>
{
};

HE_CONTROLLER_END_NAMESPACE

#endif // ITHREADCOLLECTION_H

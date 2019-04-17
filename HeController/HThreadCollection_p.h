#ifndef HTHREADCOLLECTION_P_H
#define HTHREADCOLLECTION_P_H

#include "HThreadCollection.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HThreadCollectionPrivate : public HCollectionPrivate<IThread>
{
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTHREADCOLLECTION_P_H

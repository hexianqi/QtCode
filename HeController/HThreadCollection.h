#ifndef HTHREADCOLLECTION_H
#define HTHREADCOLLECTION_H

#include "IThreadCollection.h"
#include "HeCore/HCollection.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HThreadCollectionPrivate;

class HThreadCollection : public HCollection<IThread>, public IThreadCollection
{
public:
    explicit HThreadCollection();
    ~HThreadCollection();

protected:
    HThreadCollection(HThreadCollectionPrivate &p);

protected:
    QScopedPointer<HThreadCollectionPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTHREADCOLLECTION_H

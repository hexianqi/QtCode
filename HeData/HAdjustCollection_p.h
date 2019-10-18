#ifndef HADJUSTCOLLECTION_P_H
#define HADJUSTCOLLECTION_P_H

#include "HAdjustCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustCollectionPrivate : public HDataCollectionPrivate<IAdjust>
{
public:
    HAdjustCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_DATA_END_NAMESPACE

#endif // HADJUSTCOLLECTION_P_H

#ifndef HADJUSTCOLLECTION_P_H
#define HADJUSTCOLLECTION_P_H

#include "HAdjustCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustCollectionPrivate : public HCollectionPrivate<IAdjust>
{
public:
    HAdjustCollectionPrivate(IDataFactory *);

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory;
    IFileStream *fileStream;
    QString useIndex;
};

HE_DATA_END_NAMESPACE

#endif // HADJUSTCOLLECTION_P_H

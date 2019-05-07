#ifndef HQUALITYCOLLECTION_P_H
#define HQUALITYCOLLECTION_P_H

#include "HQualityCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HQualityCollectionPrivate : public HCollectionPrivate<IQuality>
{
public:
    HQualityCollectionPrivate(IDataFactory *);

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory;
    IFileStream *fileStream;
    QString useIndex;
};

HE_DATA_END_NAMESPACE

#endif // HQUALITYCOLLECTION_P_H

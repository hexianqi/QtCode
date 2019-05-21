#ifndef HCHROMATISMCOLLECTION_P_H
#define HCHROMATISMCOLLECTION_P_H

#include "HChromatismCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HChromatismCollectionPrivate : public HCollectionPrivate<IChromatism>
{
public:
    HChromatismCollectionPrivate(IDataFactory *);

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory;
    IFileStream *fileStream;
    QString useIndex;
};

HE_DATA_END_NAMESPACE

#endif // HCHROMATISMCOLLECTION_P_H

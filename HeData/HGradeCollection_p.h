#ifndef HGRADECOLLECTION_P_H
#define HGRADECOLLECTION_P_H

#include "HGradeCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeCollectionPrivate : public HCollectionPrivate<IGrade>
{
public:
    HGradeCollectionPrivate(IDataFactory *);

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

public:
    IDataFactory *factory;
    IFileStream *fileStream;
    QString useIndex;
};

HE_DATA_END_NAMESPACE

#endif // HGRADECOLLECTION_P_H

#ifndef HQUALITYCOLLECTION_P_H
#define HQUALITYCOLLECTION_P_H

#include "HQualityCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HQualityCollectionPrivate : public HDataCollectionPrivate<IQuality>
{
public:
    HQualityCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_DATA_END_NAMESPACE

#endif // HQUALITYCOLLECTION_P_H

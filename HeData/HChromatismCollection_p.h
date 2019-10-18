#ifndef HCHROMATISMCOLLECTION_P_H
#define HCHROMATISMCOLLECTION_P_H

#include "HChromatismCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HChromatismCollectionPrivate : public HDataCollectionPrivate<IChromatism>
{
public:
    HChromatismCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_DATA_END_NAMESPACE

#endif // HCHROMATISMCOLLECTION_P_H

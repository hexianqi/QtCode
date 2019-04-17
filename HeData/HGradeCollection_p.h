#ifndef HGRADECOLLECTION_P_H
#define HGRADECOLLECTION_P_H

#include "HGradeCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeCollectionPrivate
{
public:
    HGradeCollectionPrivate(HGradeCollection *, IDataFactory *);

public:
    HGradeCollection *q_ptr;
    IDataFactory *factory;
    IFileStream *fileStream;
};

HE_DATA_END_NAMESPACE

#endif // HGRADECOLLECTION_P_H

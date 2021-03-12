#pragma once

#include "HGradeCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeCollectionPrivate : public HDataCollectionPrivate<IGrade>
{
public:
    HGradeCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_DATA_END_NAMESPACE

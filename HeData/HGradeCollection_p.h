#pragma once

#include "HGradeCollection.h"

HE_BEGIN_NAMESPACE

class HGradeCollectionPrivate : public HDataCollectionPrivate<IGrade>
{
public:
    HGradeCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_END_NAMESPACE

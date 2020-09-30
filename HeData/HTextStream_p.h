#pragma once

#include "HTextStream.h"
#include "HAbstractStream_p.h"

HE_DATA_BEGIN_NAMESPACE

class HTextStreamPrivate : public HAbstractStreamPrivate
{
public:
    HTextStreamPrivate();

public:
    std::function<void(QTextStream &)> readContent;
    std::function<void(QTextStream &)> writeContent;
    QString content;
};

HE_DATA_END_NAMESPACE


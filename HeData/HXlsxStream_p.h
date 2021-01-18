#pragma once

#include "HXlsxStream.h"
#include "HAbstractStream_p.h"

HE_DATA_BEGIN_NAMESPACE

class HXlsxStreamPrivate : public HAbstractStreamPrivate
{
public:
    HXlsxStreamPrivate();

public:
    std::function<void(Document *)> readContent = nullptr;
    std::function<void(Document *)> writeContent = nullptr;
};

HE_DATA_END_NAMESPACE


#ifndef HEXCELSTREAM_P_H
#define HEXCELSTREAM_P_H

#include "HExcelStream.h"

HE_DATA_BEGIN_NAMESPACE

class HExcelStreamPrivate
{
public:
    HExcelStreamPrivate();

public:
    QString fileFilter;

public:
    std::function<void(QTextStream &)> writeContent;
};

HE_DATA_END_NAMESPACE

#endif // HEXCELSTREAM_P_H

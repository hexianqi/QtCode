#ifndef HFILESTREAM_P_H
#define HFILESTREAM_P_H

#include "HFileStream.h"

HE_DATA_BEGIN_NAMESPACE

class HFileStreamPrivate
{
public:
    HFileStreamPrivate();

public:
    quint32 magicNumber;
    quint32 fileVersion;
    QString fileFilter;

public:
    std::function<void(QDataStream &)> readContent;
    std::function<void(QDataStream &)> writeContent;
};

HE_DATA_END_NAMESPACE

#endif // HFILESTREAM_P_H

#ifndef HABSTRACTFILESTREAM_P_H
#define HABSTRACTFILESTREAM_P_H

#include "HAbstractFileStream.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HAbstractFileStreamPrivate
{
public:
    HAbstractFileStreamPrivate(IDataFactory *);

public:
    IDataFactory *factory;
    QString fileName;
    quint32 magicNumber;
    quint32 fileVersion;
    QString fileFilter;
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTFILESTREAM_P_H

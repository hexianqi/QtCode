#ifndef IFILESTREAM_H
#define IFILESTREAM_H

#include "HDataGlobal.h"
#include <QString>

HE_DATA_BEGIN_NAMESPACE

class IFileStream
{
public:
    virtual void setFileVersion(quint32 value) = 0;
    virtual void setFileFilter(QString value) = 0;
    virtual quint32 fileVersion() = 0;
    virtual QString fileFilter() = 0;

public:
    virtual bool openFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = 0) = 0;
    virtual bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = 0) = 0;
    virtual bool readFile(QString fileName) = 0;
    virtual bool writeFile(QString fileName) = 0;
    virtual void readContent(QDataStream &) = 0;
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE

#endif // IFILESTREAM_H

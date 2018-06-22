/***************************************************************************************************
**      2018-06-19  HAbstractFileStream 抽象文件流类。
***************************************************************************************************/

#ifndef HABSTRACTFILESTREAM_H
#define HABSTRACTFILESTREAM_H

#include "IFileStream.h"
#include <QScopedPointer>

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;
class HAbstractFileStreamPrivate;

class HAbstractFileStream : virtual public IFileStream
{
public:
    explicit HAbstractFileStream(IDataFactory *);
    ~HAbstractFileStream();

public:
    virtual void setFileVersion(quint32 value) override;
    virtual void setFileFilter(QString value) override;
    virtual quint32 fileVersion() override;
    virtual QString fileFilter() override;

public:
    virtual bool openFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = 0) override;
    virtual bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = 0) override;
    virtual bool readFile(QString fileName) override;
    virtual bool writeFile(QString fileName) override;

protected:
    HAbstractFileStream(HAbstractFileStreamPrivate &p);

protected:
    QScopedPointer<HAbstractFileStreamPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTFILESTREAM_H

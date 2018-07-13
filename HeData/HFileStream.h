/***************************************************************************************************
**      2018-07-09  HFileStream 文件流类。
***************************************************************************************************/

#ifndef HFILESTREAM_H
#define HFILESTREAM_H

#include "IFileStream.h"
#include <QObject>

HE_DATA_BEGIN_NAMESPACE

class HFileStreamPrivate;

class HFileStream : public QObject, public IFileStream
{
    Q_OBJECT

public:
    explicit HFileStream(QObject *parent = nullptr);
    ~HFileStream();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual void setMagicNumber(quint32 value) override;
    virtual void setFileVersion(quint32 value) override;
    virtual void setFileFilter(QString value) override;
    virtual void setReadContent(std::function<void(QDataStream &)> func) override;
    virtual void setWriteContent(std::function<void(QDataStream &)> func) override;
    virtual quint32 fileVersion() override;
    virtual QString fileFilter() override;

public:
    virtual bool openFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = 0) override;
    virtual bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = 0) override;
    virtual bool readFile(QString fileName) override;
    virtual bool writeFile(QString fileName) override;
    virtual bool readContent(QDataStream &) override;
    virtual bool writeContent(QDataStream &) override;

protected:
    HFileStream(HFileStreamPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HFileStreamPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HFILESTREAM_H

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
    ~HFileStream() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setMagicNumber(quint32 value) override;
    void setFileVersion(quint32 value) override;
    void setFileFilter(QString value) override;
    void setReadContent(std::function<void(QDataStream &)> func) override;
    void setWriteContent(std::function<void(QDataStream &)> func) override;
    quint32 fileVersion() override;
    QString fileFilter() override;

public:
    bool openFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) override;
    bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) override;
    bool readFile(QString fileName) override;
    bool writeFile(QString fileName) override;
    bool readContent(QDataStream &) override;
    bool writeContent(QDataStream &) override;

protected:
    HFileStream(HFileStreamPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HFileStreamPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HFILESTREAM_H

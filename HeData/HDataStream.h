/***************************************************************************************************
**      2020-09-29  HDataStream
***************************************************************************************************/

#pragma once

#include "IDataStream.h"

HE_DATA_BEGIN_NAMESPACE

class HDataStreamPrivate;

class HDataStream : public IDataStream
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDataStream)

public:
    explicit HDataStream(QObject *parent = nullptr);
    ~HDataStream() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setMagicNumber(quint32 value) override;
    void setFileVersion(quint32 value) override;
    void setReadContent(std::function<void(QDataStream &)> func) override;
    void setWriteContent(std::function<void(QDataStream &)> func) override;

public:
    bool readFile(QString fileName) override;
    bool writeFile(QString fileName) override;
    bool readContent(QDataStream &) override;
    bool writeContent(QDataStream &) override;

protected:
    HDataStream(HDataStreamPrivate &p, QObject *parent = nullptr);
};

HE_DATA_END_NAMESPACE


/***************************************************************************************************
**      2020-09-29  HTextStream
***************************************************************************************************/

#pragma once

#include "ITextStream.h"

HE_DATA_BEGIN_NAMESPACE

class HTextStreamPrivate;

class HTextStream : public ITextStream
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTextStream)

public:
    explicit HTextStream(QObject *parent = nullptr);
    ~HTextStream() override;

public:
    QString typeName() override;

public:
    QString content() override;

public:
    void setContent(QString value) override;
    void setReadContent(std::function<void(QTextStream &)> func) override;
    void setWriteContent(std::function<void(QTextStream &)> func) override;

public:
    bool readFile(QString fileName) override;
    bool writeFile(QString fileName) override;
    bool readContent(QTextStream &) override;
    bool writeContent(QTextStream &) override;
    bool appendFile(QString fileName) override;

protected:
    HTextStream(HTextStreamPrivate &p, QObject *parent = nullptr);
};

HE_DATA_END_NAMESPACE


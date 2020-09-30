/***************************************************************************************************
**      2020-09-30  HXlsxStream
***************************************************************************************************/

#pragma once

#include "IXlsxStream.h"

HE_DATA_BEGIN_NAMESPACE

class HXlsxStreamPrivate;

class HXlsxStream : public IXlsxStream
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HXlsxStream)

public:
    explicit HXlsxStream(QObject *parent = nullptr);
    ~HXlsxStream() override;

public:
    QString typeName() override;

public:
    void setReadContent(std::function<void(Document *)> func) override;
    void setWriteContent(std::function<void(Document *)> func) override;

public:
    bool readFile(QString fileName) override;
    bool writeFile(QString fileName) override;
    bool readContent(Document *) override;
    bool writeContent(Document *) override;

protected:
    HXlsxStream(HXlsxStreamPrivate &p, QObject *parent = nullptr);
};

HE_DATA_END_NAMESPACE


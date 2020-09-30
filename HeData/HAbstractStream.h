/***************************************************************************************************
**      2020-09-30  HAbstractStream
***************************************************************************************************/

#pragma once

#include "IStream.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractStreamPrivate;

class HAbstractStream : public QObject, public IStream
{
    Q_OBJECT

public:
    explicit HAbstractStream(QObject *parent = nullptr);
    ~HAbstractStream() override;

public:
    void initialize(QVariantMap param) override;

public:
    QString fileFilter() override;

public:
    void setFileFilter(QString value) override;
    bool openFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) override;
    bool saveAsFile(QString caption = QString(), QString dir = ".", QString *selectedFileName = nullptr) override;

protected:
    HAbstractStream(HAbstractStreamPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractStreamPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE


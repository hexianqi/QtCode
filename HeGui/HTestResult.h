/***************************************************************************************************
**      2021-01-26  HTestResult
***************************************************************************************************/

#pragma once

#include "ITestResult.h"

HE_BEGIN_NAMESPACE

class HTestResultPrivate;

class HTestResult : public QObject, public ITestResult
{
    Q_OBJECT

public:
    explicit HTestResult(QObject *parent = nullptr);
    ~HTestResult() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    ITestData *at(int i) override;
    ITestData *last() override;
    bool isEmpty() override;
    int size() override;
    void clear() override;
    void save(bool append) override;
    void remove(int index, int count) override;
    void setModified(bool b = true) override;
    void setSyncType(QStringList) override;
    void setSyncFile(const QString &) override;
    void syncFile() override;

protected:
    HTestResult(HTestResultPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HTestResultPrivate> d_ptr;
};

HE_END_NAMESPACE


/***************************************************************************************************
**      2021-01-26  HTestResult
***************************************************************************************************/

#pragma once

#include "ISyncTestResult.h"

HE_BEGIN_NAMESPACE

class HSyncTestResultPrivate;

class HSyncTestResult : public QObject, public ISyncTestResult
{
    Q_OBJECT

public:
    explicit HSyncTestResult(QObject *parent = nullptr);
    ~HSyncTestResult() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    ITestData *at(int i) override;
    ITestData *last() override;
    bool isEmpty() override;
    int size() override;
    void clear() override;
    void update(bool append) override;
    void remove(int index, int count) override;
    void setModified(bool b = true) override;
    void setSyncType(QStringList) override;
    void setSyncFile(const QString &) override;
    void syncFile() override;

protected:
    HSyncTestResult(HSyncTestResultPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HSyncTestResultPrivate> d_ptr;
};

HE_END_NAMESPACE


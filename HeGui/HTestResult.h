/***************************************************************************************************
**      2021-01-26  HTestResult
***************************************************************************************************/

#pragma once

#include "ITestResult.h"

HE_GUI_BEGIN_NAMESPACE

class HTestResultPrivate;

class HTestResult : public QObject, public ITestResult
{
    Q_OBJECT

public:
    explicit HTestResult(QObject *parent = nullptr);
    ~HTestResult() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    ITestData *at(int i) override;
    bool isEmpty() override;
    int size() override;
    void clear() override;
    void save(bool append = true) override;
    void remove(int index, int count) override;
    void setModified(bool b = true) override;
    void setExportTypes(QStringList) override;
    void setExportPathName(const QString &) override;
    void setSyncFileName(const QString &) override;
    void printPreviewLast() override;
    void exportDatabase(int index, int count) override;
    void exportDatabaseLast() override;
    void exportDatabaseAll() override;
    void exportExcel(int index, int count) override;
    void exportExcelLast() override;
    void exportExcelAppend() override;
    void syncFile() override;

protected:
    HTestResult(HTestResultPrivate &p, QObject *parent = nullptr);

protected:
    QVariantMap toRecord(int index);

protected:
    QScopedPointer<HTestResultPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE


/***************************************************************************************************
**      2018-06-19  HTestData 测试数据类。
***************************************************************************************************/

#pragma once

#include "ITestData.h"

HE_BEGIN_NAMESPACE

class HTestDataPrivate;

class HTestData : public virtual ITestData
{
public:
    explicit HTestData();
    virtual ~HTestData();

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    ITestData *setSuccessor(ITestData *) override;
    bool setCalibrate(void *) override;
    void setData(QString type, QVariant value) override;
    void setData(QVariantMap value) override;
    void addData(QString type, QVariant value) override;
    void addData(QVariantMap value) override;
    QVariant data(QString type) override;
    QVariantMap select(QStringList type) override;
    QVariantMap cloneData() override;
    ITestData *clone() override;
    QString toString(QString type) override;
    QStringList toString(QStringList type) override;
    QString toHtmlTable(QStringList type, QColor bgcolor) override;
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;

protected:
    HTestData(HTestDataPrivate &p);

protected:
    QScopedPointer<HTestDataPrivate> d_ptr;
};

HE_END_NAMESPACE

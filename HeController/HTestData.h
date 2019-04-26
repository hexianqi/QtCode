/***************************************************************************************************
**      2018-06-19  HTestData 测试数据类。
***************************************************************************************************/

#ifndef HTESTDATA_H
#define HTESTDATA_H

#include "ITestData.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HTestDataPrivate;

class HTestData : public ITestData
{
public:
    explicit HTestData();
    virtual ~HTestData();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setSuccessor(ITestData *) override;
    void setData(QString type, QVariant value) override;
    void addData(QString type, QVariant value) override;
    void addData(QVariantMap value) override;
    QVariant data(QString type) override;
    QVariantMap select(QStringList type) override;
    QString toString(QString type) override;
    QStringList toString(QStringList type) override;
    QString toHtmlTable(QStringList type, QColor bgcolor) override;

protected:
    HTestData(HTestDataPrivate &p);

protected:
    QScopedPointer<HTestDataPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTESTDATA_H

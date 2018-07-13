/***************************************************************************************************
**      2018-06-19  HTestData 测试数据类。
***************************************************************************************************/

#ifndef HTESTDATA_H
#define HTESTDATA_H

#include "ITestData.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HTestDataPrivate;

class HTestData : virtual public ITestData
{
public:
    explicit HTestData();
    ~HTestData();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual void setSuccessor(ITestData *) override;
    virtual void setData(QString type, QVariant value) override;

public:
    virtual QVariant data(QString type) override;

protected:
    HTestData(HTestDataPrivate &p);

protected:
    QScopedPointer<HTestDataPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTESTDATA_H

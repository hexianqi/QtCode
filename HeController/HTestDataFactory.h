#ifndef HTESTDATAFACTORY_H
#define HTESTDATAFACTORY_H

#include "ITestDataFactory.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HTestDataFactoryPrivate;

class HE_CONTROLLER_EXPORT HTestDataFactory : public ITestDataFactory
{
public:
    explicit HTestDataFactory();

public:
    virtual void initialize(QVariantMap param) override;
    virtual ITestData *createTestData(QString type, QVariantMap param = QVariantMap()) override;
    virtual ITestSpec *createTestSpec(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HTestDataFactory(HTestDataFactoryPrivate &p);

protected:
    QScopedPointer<HTestDataFactoryPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTESTDATAFACTORY_H

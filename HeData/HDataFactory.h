/***************************************************************************************************
**      2018-06-19  HDataFactory 数据工厂类。
***************************************************************************************************/

#ifndef HDATAFACTORY_H
#define HDATAFACTORY_H

#include "IDataFactory.h"

HE_DATA_BEGIN_NAMESPACE

class HDataFactoryPrivate;

class HE_DATA_EXPORT HDataFactory : public IDataFactory
{
public:
    explicit HDataFactory();
    ~HDataFactory();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;
    virtual IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) override;
    virtual ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) override;
    virtual ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HDataFactory(HDataFactoryPrivate &p);

protected:
    QScopedPointer<HDataFactoryPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HDATAFACTORY_H

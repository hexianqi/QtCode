/***************************************************************************************************
**      2018-06-19  HConfigManage 配置管理类。
***************************************************************************************************/

#ifndef HCONFIGMANAGE_H
#define HCONFIGMANAGE_H

#include "IConfigManage.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;
class HConfigManagePrivate;

class HConfigManage : public IConfigManage
{
public:
    explicit HConfigManage(IDataFactory *);
    ~HConfigManage();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual void setContain(quint32 value) override;
    virtual void setSpecCalibrateCollection(ISpecCalibrateCollection *) override;

public:
    virtual IFileStream *fileStream() override;
    virtual quint32 contain() override;
    virtual ISpecCalibrate *specCalibrate(QString name) override;

public:
    virtual bool importPart(quint32 value) override;
    virtual bool exportPart(quint32 value) override;

protected:
    HConfigManage(HConfigManagePrivate &p);

protected:
    QScopedPointer<HConfigManagePrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_H

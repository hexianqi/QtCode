/***************************************************************************************************
**      2018-06-19  HConfigManage 配置管理类。
***************************************************************************************************/

#ifndef HCONFIGMANAGE_H
#define HCONFIGMANAGE_H

#include "IConfigManage.h"
#include "HAbstractFileStream.h"

HE_DATA_BEGIN_NAMESPACE

class HConfigManagePrivate;

class HConfigManage : public HAbstractFileStream, public IConfigManage
{
    Q_DECLARE_PRIVATE(HConfigManage)

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
    virtual quint32 contain() override;
    virtual ISpecCalibrate *specCalibrate(QString name) override;

public:
    virtual bool importPart(quint32 value) override;
    virtual bool exportPart(quint32 value) override;


protected:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

protected:
    HConfigManage(HConfigManagePrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_H

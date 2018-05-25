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
    virtual void setContain(ConfigContainType value) override;
    virtual void setSpecCalibrateCollection(ISpecCalibrateCollection *) override;
    virtual ISpecCalibrate *getSpecCalibrate(QString name) override;

public:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

protected:
    HConfigManage(HConfigManagePrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_H

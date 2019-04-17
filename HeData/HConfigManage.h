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
    virtual ~HConfigManage();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setContain(quint32 value) override;
    void setSpecCalibrateCollection(ISpecCalibrateCollection *) override;
    void setGradeCollection(IGradeCollection *) override;

public:
    IFileStream *fileStream() override;
    quint32 contain() override;
    ISpecCalibrate *specCalibrate(QString name) override;
    IGradeCollection *gradeCollection() override;

public:
    bool importPart(quint32 value) override;
    bool exportPart(quint32 value) override;

protected:
    HConfigManage(HConfigManagePrivate &);

protected:
    QScopedPointer<HConfigManagePrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_H

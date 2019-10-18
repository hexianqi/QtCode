/***************************************************************************************************
**      2018-06-19  HConfigManage 配置管理类。
***************************************************************************************************/

#ifndef HCONFIGMANAGE_H
#define HCONFIGMANAGE_H

#include "IConfigManage.h"

HE_DATA_BEGIN_NAMESPACE

class HConfigManagePrivate;

class HConfigManage : public IConfigManage
{
public:
    explicit HConfigManage();
    virtual ~HConfigManage();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IFileStream *fileStream() override;
    void setContain(quint32 value) override;
    quint32 contain() override;
    void setSpecCalibrateCollection(ISpecCalibrateCollection *) override;
    ISpecCalibrate *specCalibrate(QString name) override;
    void setElecCalibrateCollection(IElecCalibrateCollection *) override;
    IElecCalibrateCollection *elecCalibrateCollection() override;
    IElecCalibrate *elecCalibrate(QString name) override;
    void setChromatismCollection(IChromatismCollection *) override;
    IChromatismCollection *chromatismCollection() override;
    void setGradeCollection(IGradeCollection *) override;
    IGradeCollection *gradeCollection() override;
    void setAdjustCollection(IAdjustCollection *) override;
    IAdjustCollection *adjustCollection() override;
    void setQualityCollection(IQualityCollection *) override;
    IQualityCollection *qualityCollection() override;

public:
    bool importPart(quint32 value) override;
    bool exportPart(quint32 value) override;

public:
    void postProcess(ITestData *, QStringList optional) override;

protected:
    HConfigManage(HConfigManagePrivate &);

protected:
    QScopedPointer<HConfigManagePrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HCONFIGMANAGE_H

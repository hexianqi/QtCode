/***************************************************************************************************
**      2018-06-19  HConfigManage 配置管理类。
***************************************************************************************************/

#pragma once

#include "IConfigManage.h"

HE_DATA_BEGIN_NAMESPACE

class HConfigManagePrivate;

class HConfigManage : public QObject, public IConfigManage
{
    Q_OBJECT

public:
    explicit HConfigManage(QObject *parent = nullptr);
    ~HConfigManage() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IStream *stream() override;
    void setContain(quint32 value) override;
    quint32 contain() override;
    void setSpecCalibrateCollection(ISpecCalibrateCollection *) override;
    ISpecCalibrate *specCalibrate(QString name) override;
    void setElecCalibrateCollection(IElecCalibrateCollection *) override;
    IElecCalibrateCollection *elecCalibrateCollection() override;
    void setLuminousCalibrateCollection(ILuminousCalibrateCollection *) override;
    ILuminousCalibrateCollection *luminousCalibrateCollection() override;
    void setChromatismCollection(IChromatismCollection *) override;
    IChromatismCollection *chromatismCollection() override;
    void setGradeCollection(IGradeCollection *) override;
    IGradeCollection *gradeCollection() override;
    void setAdjustCollection(IAdjustCollection *) override;
    IAdjustCollection *adjustCollection() override;
    void setAdjust2Collection(IAdjust2Collection *) override;
    IAdjust2Collection *adjust2Collection() override;
    void setQualityCollection(IQualityCollection *) override;
    IQualityCollection *qualityCollection() override;

public:
    bool importPart(quint32 value) override;
    bool exportPart(quint32 value) override;

public:
    void postProcess(ITestData *, QStringList optional) override;

protected:
    HConfigManage(HConfigManagePrivate &p, QObject *parent = nullptr);

protected:
    QVariantMap unify(ITestData *test, QVariantMap value, QStringList optional);

protected:
    QScopedPointer<HConfigManagePrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

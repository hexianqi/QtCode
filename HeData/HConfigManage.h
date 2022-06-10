/***************************************************************************************************
**      2018-06-19  HConfigManage 配置管理类。
***************************************************************************************************/

#pragma once

#include "IConfigManage.h"

HE_BEGIN_NAMESPACE

class HConfigManagePrivate;

class HConfigManage : public QObject, public IConfigManage
{
    Q_OBJECT

public:
    explicit HConfigManage(QObject *parent = nullptr);
    ~HConfigManage() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
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
    void addQualityCollection(QString key, IQualityCollection *) override;
    IQualityCollection *qualityCollection(QString key) override;
    void setLocationCollection(ILocationCollection *) override;
    ILocationCollection *locationCollection() override;
    void setAdjustCollection(IAdjustCollection *) override;
    IAdjustCollection *adjustCollection() override;
    void setAdjust2Collection(IAdjust2Collection *) override;
    IAdjust2Collection *adjust2Collection() override;

public:
    bool importPart(quint32 value) override;
    bool exportPart(quint32 value) override;

public:
    QStringList supplement(QStringList) override;
    void processAll(ITestData *, QStringList optional, QString keyQuality) override;
    bool processChromatism(ITestData *) override;
    bool processAdjust(ITestData *, QStringList optional) override;
    bool processGrade(ITestData *, QStringList optional) override;
    bool processQuality(ITestData *, QStringList optional, QString key = QString()) override;

protected:
    HConfigManage(HConfigManagePrivate &p, QObject *parent = nullptr);

protected:
    void unify(ITestData *test, QVariantMap value, QStringList optional);

protected:
    QScopedPointer<HConfigManagePrivate> d_ptr;
};

HE_END_NAMESPACE

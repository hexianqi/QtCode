/***************************************************************************************************
**      2018-06-19  HDataFactory 数据工厂类。
***************************************************************************************************/

#pragma once

#include "IDataFactory.h"

HE_DATA_BEGIN_NAMESPACE

class HDataFactoryPrivate;

class HE_DATA_EXPORT HDataFactory : public QObject, public IDataFactory
{
    Q_OBJECT

public:
    explicit HDataFactory(QObject *parent = nullptr);
    ~HDataFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IPrint *createPrint(QString type, QVariantMap param = QVariantMap()) override;

public:
    IDataStream *createDataStream(QString type, QVariantMap param = QVariantMap()) override;
    ITextStream *createTextStream(QString type, QVariantMap param = QVariantMap()) override;
    IXlsxStream *createXlsxStream(QString type, QVariantMap param = QVariantMap()) override;
    IMultStream *createMultStream(QString type, QVariantMap param = QVariantMap()) override;

public:
    ITestData *createTestData(QString type, QVariantMap param = QVariantMap()) override;
    ITestSpec *createTestSpec(QString type, QVariantMap param = QVariantMap()) override;

public:
    IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) override;
    ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) override;
    ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) override;
    IElecCalibrateCollection *createElecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) override;
    IElecCalibrate *createElecCalibrate(QString type, QVariantMap param = QVariantMap()) override;
    IElecCalibrateItemCollection *createElecCalibrateItemCollection(QString type, QVariantMap param = QVariantMap()) override;
    IElecCalibrateItem *createElecCalibrateItem(QString type, QVariantMap param = QVariantMap()) override;
    ILuminousCalibrateCollection *createLuminousCalibrateCollection(QString type, QVariantMap param = QVariantMap()) override;
    ILuminousCalibrate *createLuminousCalibrate(QString type, QVariantMap param = QVariantMap()) override;
    ILuminousCalibrateItem *createLuminousCalibrateItem(QString type, QVariantMap param = QVariantMap()) override;
    IChromatismCollection *createChromatismCollection(QString type, QVariantMap param = QVariantMap()) override;
    IChromatism *createChromatism(QString type, QVariantMap param = QVariantMap()) override;
    IChromatismItem *createChromatismItem(QString type, QVariantMap param = QVariantMap()) override;
    IGradeCollection *createGradeCollection(QString type, QVariantMap param = QVariantMap()) override;
    IGrade *createGrade(QString type, QVariantMap param = QVariantMap()) override;
    IGradeItem *createGradeItem(QString type, QVariantMap param = QVariantMap()) override;
    IAdjustCollection *createAdjustCollection(QString type, QVariantMap param = QVariantMap()) override;
    IAdjust2Collection *createAdjust2Collection(QString type, QVariantMap param = QVariantMap()) override;
    IAdjust *createAdjust(QString type, QVariantMap param = QVariantMap()) override;
    IAdjust2 *createAdjust2(QString type, QVariantMap param = QVariantMap()) override;
    IAdjustItemCollection *createAdjustItemCollection(QString type, QVariantMap param = QVariantMap()) override;
    IAdjustItem *createAdjustItem(QString type, QVariantMap param = QVariantMap()) override;
    IQualityCollection *createQualityCollection(QString type, QVariantMap param = QVariantMap()) override;
    IQuality *createQuality(QString type, QVariantMap param = QVariantMap()) override;
    IQualityItem *createQualityItem(QString type, QVariantMap param = QVariantMap()) override;
    HSpecFitting *createSpecFitting(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HDataFactory(HDataFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HDataFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_DATA_END_NAMESPACE

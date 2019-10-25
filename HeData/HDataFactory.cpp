#include "HDataFactory_p.h"
#include "HExcelStream.h"
#include "HFileStream.h"
#include "HTestSpec.h"
#include "HTestElec.h"
#include "HConfigManage.h"
#include "HSpecCalibrate.h"
#include "HSpecCalibrateCollection.h"
#include "HElecCalibrate.h"
#include "HElecCalibrateCollection.h"
#include "HElecCalibrateItem.h"
#include "HElecCalibrateItemCollection.h"
#include "HChromatism.h"
#include "HChromatismCollection.h"
#include "HChromatismItem.h"
#include "HGradeCollection.h"
#include "HSequentialGrade.h"
#include "HParallelGrade.h"
#include "HGradeItem.h"
#include "HGradeItem2D.h"
#include "HAdjust.h"
#include "HAdjustCollection.h"
#include "HAdjustItem.h"
#include "HQuality.h"
#include "HQualityCollection.h"
#include "HQualityItem.h"
#include "HSpecFittingLinear.h"
#include "HSpecFittingPolynom.h"
#include "HeCore/HFactory.h"
#include <QtCore/QDebug>

HE_DATA_BEGIN_NAMESPACE

HDataFactory::HDataFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HDataFactoryPrivate)
{
    registerClass();
}

HDataFactory::HDataFactory(HDataFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HDataFactory::~HDataFactory()
{
    qDebug() << __func__;
}

void HDataFactory::initialize(QVariantMap /*param*/)
{
}

QString HDataFactory::typeName()
{
    return "HDataFactory";
}

IFileStream *HDataFactory::createFileStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HFileStream(this);
    p->initialize(param);
    return p;
}

IExcelStream *HDataFactory::createExcelStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HExcelStream(this);
    p->initialize(param);
    return p;
}

ITestData *HDataFactory::createTestData(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HTestData;
    p->initialize(param);
    return p;
}

ITestSpec *HDataFactory::createTestSpec(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HTestSpec;
    p->initialize(param);
    return p;
}

ITestElec *HDataFactory::createTestElec(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HTestElec;
    p->initialize(param);
    return p;
}

IConfigManage *HDataFactory::createConfigManage(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HConfigManage;
    p->initialize(param);
    return p;
}

ISpecCalibrateCollection *HDataFactory::createSpecCalibrateCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSpecCalibrateCollection;
    p->initialize(param);
    return p;
}

ISpecCalibrate *HDataFactory::createSpecCalibrate(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSpecCalibrate;
    p->initialize(param);
    return p;
}

IElecCalibrateCollection *HDataFactory::createElecCalibrateCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HElecCalibrateCollection;
    p->initialize(param);
    return p;
}

IElecCalibrate *HDataFactory::createElecCalibrate(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HElecCalibrate;
    p->initialize(param);
    return p;
}

IElecCalibrateItemCollection *HDataFactory::createElecCalibrateItemCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HElecCalibrateItemCollection;
    p->initialize(param);
    return p;
}

IElecCalibrateItem *HDataFactory::createElecCalibrateItem(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HElecCalibrateItem;
    p->initialize(param);
    return p;
}

IChromatismCollection *HDataFactory::createChromatismCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HChromatismCollection;
    p->initialize(param);
    return p;
}

IChromatism *HDataFactory::createChromatism(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HChromatism;
    p->initialize(param);
    return p;
}

IChromatismItem *HDataFactory::createChromatismItem(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HChromatismItem;
    p->initialize(param);
    return p;
}

IGradeCollection *HDataFactory::createGradeCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HGradeCollection;
    p->initialize(param);
    return p;
}

IGrade *HDataFactory::createGrade(QString type, QVariantMap param)
{
    return HFactory::createObject<IGrade>(type, param);
}

IGradeItem *HDataFactory::createGradeItem(QString type, QVariantMap param)
{
    return HFactory::createObject<IGradeItem>(type, param);
}

IAdjustCollection *HDataFactory::createAdjustCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HAdjustCollection;
    p->initialize(param);
    return p;
}

IAdjust *HDataFactory::createAdjust(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HAdjust;
    p->initialize(param);
    return p;
}

IAdjustItem *HDataFactory::createAdjustItem(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HAdjustItem;
    p->initialize(param);
    return p;
}

IQualityCollection *HDataFactory::createQualityCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HQualityCollection;
    p->initialize(param);
    return p;
}

IQuality *HDataFactory::createQuality(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HQuality;
    p->initialize(param);
    return p;
}

IQualityItem *HDataFactory::createQualityItem(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HQualityItem;
    p->initialize(param);
    return p;
}

HSpecFitting *HDataFactory::createSpecFitting(QString type, QVariantMap param)
{
    return HFactory::createObject<HSpecFitting>(type, param);
}

void HDataFactory::registerClass()
{
    HFactory::registerClass<HParallelGrade>("HParallelGrade");
    HFactory::registerClass<HSequentialGrade>("HSequentialGrade");
    HFactory::registerClass<HGradeItem>("HGradeItem");
    HFactory::registerClass<HGradeItem2D>("HGradeItem2D");
    HFactory::registerClass<HSpecFittingLinear>("HSpecFittingLinear");
    HFactory::registerClass<HSpecFittingPolynom>("HSpecFittingPolynom");
}

HE_DATA_END_NAMESPACE

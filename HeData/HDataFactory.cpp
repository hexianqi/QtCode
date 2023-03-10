#include "HDataFactory_p.h"
#include "HPrint.h"
#include "HTextExport.h"
#include "HDataStream.h"
#include "HTextStream.h"
#include "HXlsxStream.h"
#include "HMultStream.h"
#include "HTestSpec.h"
#include "HTestElec.h"
#include "HTestProduct.h"
#include "HTestLuminous.h"
#include "HConfigManage.h"
#include "HSpecCalibrate.h"
#include "HSpecCalibrateCollection.h"
#include "HElecCalibrate.h"
#include "HElecCalibrateCollection.h"
#include "HElecCalibrateItem.h"
#include "HElecCalibrateItemCollection.h"
#include "HLuminousCalibrate.h"
#include "HLuminousCalibrateCollection.h"
#include "HLuminousCalibrateItem.h"
#include "HChromatism.h"
#include "HChromatismCollection.h"
#include "HChromatismItem.h"
#include "HGradeCollection.h"
#include "HSequentialGrade.h"
#include "HParallelGrade.h"
#include "HGradeItem.h"
#include "HGradeItem2D.h"
#include "HQuality.h"
#include "HQualityCollection.h"
#include "HQualityItem.h"
#include "HLocation.h"
#include "HLocationCollection.h"
#include "HAdjust.h"
#include "HAdjust2.h"
#include "HAdjustItemCollection.h"
#include "HAdjustCollection.h"
#include "HAdjust2Collection.h"
#include "HAdjustItem.h"
#include "HPlineStrategy.h"
#include "HPolynomStrategy.h"
#include "HeCore/HFactory.h"

HE_BEGIN_NAMESPACE

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

HDataFactory::~HDataFactory() = default;

void HDataFactory::initialize(QVariantMap /*param*/)
{
}

QString HDataFactory::typeName()
{
    return "HDataFactory";
}

IPrint *HDataFactory::createPrint(QString type, QVariantMap param)
{
    Q_UNUSED(type);
    auto p = new HPrint(this);
    p->initialize(param);
    return p;
}

ITextExport *HDataFactory::createTextExport(QString type, QVariantMap param)
{
    Q_UNUSED(type);
    auto p = new HTextExport(this);
    p->initialize(param);
    return p;
}

IDataStream *HDataFactory::createDataStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HDataStream(this);
    p->initialize(param);
    return p;
}

ITextStream *HDataFactory::createTextStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HTextStream(this);
    p->initialize(param);
    return p;
}

IXlsxStream *HDataFactory::createXlsxStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HXlsxStream(this);
    p->initialize(param);
    return p;
}

IMultStream *HDataFactory::createMultStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HMultStream(this);
    p->initialize(param);
    return p;
}

ITestData *HDataFactory::createTestData(QString type, QVariantMap param)
{
    return HFactory::createObject<ITestData>(type, param);
}

ITestSpec *HDataFactory::createTestSpec(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HTestSpec;
    p->initialize(param);
    return p;
}

IConfigManage *HDataFactory::createConfigManage(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HConfigManage(this);
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

ILuminousCalibrateCollection *HDataFactory::createLuminousCalibrateCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HLuminousCalibrateCollection;
    p->initialize(param);
    return p;
}

ILuminousCalibrate *HDataFactory::createLuminousCalibrate(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HLuminousCalibrate;
    p->initialize(param);
    return p;
}

ILuminousCalibrateItem *HDataFactory::createLuminousCalibrateItem(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HLuminousCalibrateItem;
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

ILocationCollection *HDataFactory::createLocationCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HLocationCollection;
    p->initialize(param);
    return p;
}

ILocation *HDataFactory::createLocation(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HLocation;
    p->initialize(param);
    return p;
}

IAdjustCollection *HDataFactory::createAdjustCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HAdjustCollection;
    p->initialize(param);
    return p;
}

IAdjust2Collection *HDataFactory::createAdjust2Collection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HAdjust2Collection;
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

IAdjust2 *HDataFactory::createAdjust2(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HAdjust2;
    p->initialize(param);
    return p;
}

IAdjustItemCollection *HDataFactory::createAdjustItemCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HAdjustItemCollection;
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

ILinearStrategy *HDataFactory::createLinearStrategy(QString type, QVariantMap param)
{
    return HFactory::createObject<ILinearStrategy>(type, param);
}

void HDataFactory::registerClass()
{
    HFactory::registerClass<HParallelGrade>("HParallelGrade");
    HFactory::registerClass<HSequentialGrade>("HSequentialGrade");

    HFactory::registerClass<HGradeItem>("HGradeItem");
    HFactory::registerClass<HGradeItem2D>("HGradeItem2D");

    HFactory::registerClass<HPlineStrategy>("HPlineStrategy");
    HFactory::registerClass<HPolynomStrategy>("HPolynomStrategy");

    HFactory::registerClass<HTestData>("HTestData");
    HFactory::registerClass<HTestProduct>("HTestProduct");
    HFactory::registerClass<HTestElec>("HTestElec");
    HFactory::registerClass<HTestLuminous>("HTestLuminous");
}

HE_END_NAMESPACE

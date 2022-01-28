#include "HConfigManage_p.h"
#include "IDataFactory.h"
#include "IDataStream.h"
#include "ITestData.h"
#include "ISpecCalibrateCollection.h"
#include "IElecCalibrateCollection.h"
#include "ILuminousCalibrateCollection.h"
#include "IChromatismCollection.h"
#include "IGradeCollection.h"
#include "IQualityCollection.h"
#include "ILocationCollection.h"
#include "IAdjustCollection.h"
#include "IAdjust2Collection.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDataStream>
#include <QtCore/QPointF>
#include <QtCore/QSet>
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

HConfigManagePrivate::HConfigManagePrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    stream = factory->createDataStream("HDataStream");
    stream->setMagicNumber(0x00010001);
    stream->setFileVersion(0x01010101);
    stream->setFileFilter("Config files (*.cfg)");
    stream->setReadContent([=](QDataStream &s) { readContent(s); });
    stream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HConfigManagePrivate::readContent(QDataStream &s)
{
    quint32 version;
    QString type;

    s >> version;
    s >> contain;
    if (contain & IConfigManage::ContainSpec)
    {
        s >> type;
        specCalibrate = factory->createSpecCalibrateCollection(type);
        specCalibrate->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainElec)
    {
        s >> type;
        elecCalibrate = factory->createElecCalibrateCollection(type);
        elecCalibrate->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainLuminous)
    {
        s >> type;
        luminousCalibrate = factory->createLuminousCalibrateCollection(type);
        luminousCalibrate->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainChromatism)
    {
        s >> type;
        chromatism = factory->createChromatismCollection(type);
        chromatism->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainGrade)
    {
        s >> type;
        grade = factory->createGradeCollection(type);
        grade->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainQuality)
    {
        s >> type;
        quality = factory->createQualityCollection(type);
        quality->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainLocation)
    {
        s >> type;
        location = factory->createLocationCollection(type);
        location->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainAdjust)
    {
        s >> type;
        adjust = factory->createAdjustCollection(type);
        adjust->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainAdjust2)
    {
        s >> type;
        adjust2 = factory->createAdjust2Collection(type);
        adjust2->dataStream()->readContent(s);
    }
}

void HConfigManagePrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << contain;
    if (contain & IConfigManage::ContainSpec)
    {
        s << specCalibrate->typeName();
        specCalibrate->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainElec)
    {
        s << elecCalibrate->typeName();
        elecCalibrate->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainLuminous)
    {
        s << luminousCalibrate->typeName();
        luminousCalibrate->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainChromatism)
    {
        s << chromatism->typeName();
        chromatism->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainGrade)
    {
        s << grade->typeName();
        grade->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainQuality)
    {
        s << quality->typeName();
        quality->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainLocation)
    {
        s << location->typeName();
        location->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainAdjust)
    {
        s << adjust->typeName();
        adjust->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainAdjust2)
    {
        s << adjust2->typeName();
        adjust2->dataStream()->writeContent(s);
    }
}

HConfigManage::HConfigManage(QObject *parent) :
    QObject(parent),
    d_ptr(new HConfigManagePrivate)
{
}

HConfigManage::HConfigManage(HConfigManagePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HConfigManage::~HConfigManage() = default;

void HConfigManage::initialize(QVariantMap /*param*/)
{
}

QString HConfigManage::typeName()
{
    return "HConfigManage";
}

IStream *HConfigManage::stream()
{
    return d_ptr->stream;
}

void HConfigManage::setContain(quint32 value)
{
    if (d_ptr->contain == value)
        return;
    d_ptr->contain = value;
}

quint32 HConfigManage::contain()
{
    return d_ptr->contain;
}

void HConfigManage::setSpecCalibrateCollection(ISpecCalibrateCollection *p)
{
    d_ptr->specCalibrate = p;
}

ISpecCalibrate *HConfigManage::specCalibrate(QString name)
{
    Q_ASSERT(d_ptr->specCalibrate != nullptr);
    if (d_ptr->specCalibrate->contains(name))
        return d_ptr->specCalibrate->value(name);
    return d_ptr->specCalibrate->first();
}

void HConfigManage::setElecCalibrateCollection(IElecCalibrateCollection *p)
{
    d_ptr->elecCalibrate = p;
}

IElecCalibrateCollection *HConfigManage::elecCalibrateCollection()
{
    return d_ptr->elecCalibrate;
}

void HConfigManage::setLuminousCalibrateCollection(ILuminousCalibrateCollection *p)
{
    d_ptr->luminousCalibrate = p;
}

ILuminousCalibrateCollection *HConfigManage::luminousCalibrateCollection()
{
    return d_ptr->luminousCalibrate;
}

void HConfigManage::setChromatismCollection(IChromatismCollection *p)
{
    d_ptr->chromatism = p;
}

IChromatismCollection *HConfigManage::chromatismCollection()
{
    return d_ptr->chromatism;
}

void HConfigManage::setGradeCollection(IGradeCollection *p)
{
    d_ptr->grade = p;
}

IGradeCollection *HConfigManage::gradeCollection()
{
    return d_ptr->grade;
}

void HConfigManage::setQualityCollection(IQualityCollection *p)
{
    d_ptr->quality = p;
}

IQualityCollection *HConfigManage::qualityCollection()
{
    return d_ptr->quality;
}

void HConfigManage::setLocationCollection(ILocationCollection *p)
{
    d_ptr->location = p;
}

ILocationCollection *HConfigManage::locationCollection()
{
    return d_ptr->location;
}

void HConfigManage::setAdjustCollection(IAdjustCollection *p)
{
    d_ptr->adjust = p;
}

IAdjustCollection *HConfigManage::adjustCollection()
{
    return d_ptr->adjust;
}

void HConfigManage::setAdjust2Collection(IAdjust2Collection *p)
{
    d_ptr->adjust2 = p;
}

IAdjust2Collection *HConfigManage::adjust2Collection()
{
    return d_ptr->adjust2;
}

bool HConfigManage::importPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ContainSpec)
        return d_ptr->specCalibrate->dataStream()->openFile();
    if (value & ContainElec)
        return d_ptr->elecCalibrate->dataStream()->openFile();
    if (value & ContainLuminous)
        return d_ptr->luminousCalibrate->dataStream()->openFile();
    if (value & ContainChromatism)
        return d_ptr->chromatism->dataStream()->openFile();
    if (value & ContainGrade)
        return d_ptr->grade->dataStream()->openFile();
    if (value & ContainQuality)
        return d_ptr->quality->dataStream()->openFile();
    if (value & ContainLocation)
        return d_ptr->location->dataStream()->openFile();
    if (value & ContainAdjust)
        return d_ptr->adjust->dataStream()->openFile();
    if (value & ContainAdjust2)
        return d_ptr->adjust2->dataStream()->openFile();

    return false;
}

bool HConfigManage::exportPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ContainSpec)
        return d_ptr->specCalibrate->dataStream()->saveAsFile();
    if (value & ContainElec)
        return d_ptr->elecCalibrate->dataStream()->saveAsFile();
    if (value & ContainLuminous)
        return d_ptr->luminousCalibrate->dataStream()->saveAsFile();
    if (value & ContainChromatism)
        return d_ptr->chromatism->dataStream()->saveAsFile();
    if (value & ContainGrade)
        return d_ptr->grade->dataStream()->saveAsFile();
    if (value & ContainQuality)
        return d_ptr->quality->dataStream()->saveAsFile();
    if (value & ContainLocation)
        return d_ptr->location->dataStream()->saveAsFile();
    if (value & ContainAdjust)
        return d_ptr->adjust->dataStream()->saveAsFile();
    if (value & ContainAdjust2)
        return d_ptr->adjust2->dataStream()->saveAsFile();
    return false;
}

void HConfigManage::postProcess(ITestData *test, QStringList optional)
{
    auto set = optional.toSet();
    set = HDataHelper::supplement(set, QSet<QString>() << "[色坐标]" << "[色坐标x]" << "[色坐标y]");
    set = HDataHelper::supplement(set, QSet<QString>() << "[色坐标uv]" << "[色坐标u]" << "[色坐标v]");
    set = HDataHelper::supplement(set, QSet<QString>() << "[色坐标uvp]" << "[色坐标up]" << "[色坐标vp]");
    optional = set.toList();
    auto data = test->select(optional);

    test->setData("[调整组]", "-");
    if (test->data("[使用调整]").toBool())
    {
        QVariantMap value;
        if (d_ptr->adjust != nullptr)
        {
            value = d_ptr->adjust->correct(data);
            test->setData("[调整组]", d_ptr->adjust->useIndex());
        }
        else if (d_ptr->adjust2 != nullptr)
        {
            value = d_ptr->adjust2->correct(test->data("[色温]").toDouble(), data);
            test->setData("[调整组]", d_ptr->adjust2->useIndex());
        }
        if (!value.isEmpty())
            data = unify(test, value, optional);
    }
    if (d_ptr->chromatism != nullptr)
    {
        test->setData("[色容差]", d_ptr->chromatism->calcSdcm(test->data("[色温]").toDouble(), test->data("[色坐标]").toPointF()));
        test->setData("[色容差标准]", d_ptr->chromatism->toMap());
//        auto std = d_ptr->chromatisms->toMap();
//        test->setData("[色容差标准Json]", QString(QJsonDocument(QJsonObject::fromVariantMap(std)).toJson(QJsonDocument::Compact)));
    }

    if (d_ptr->grade != nullptr)
    {
        QString text;
        auto level = d_ptr->grade->calcLevel(data, &text);
        test->setData("[分级]", level);
        test->setData("[分级别名]", text);
    }

    if (d_ptr->quality != nullptr)
    {
        QVariantMap colors;
        auto report = d_ptr->quality->check(data, &colors);
        auto color = d_ptr->quality->color(report);
        test->setData("[品质]", report);
        test->setData("[品质颜色]", color);
        test->setData("[品质不符合颜色]", colors);
    }
}

// 关联数据统一
QVariantMap HConfigManage::unify(ITestData *test, QVariantMap value, QStringList optional)
{
    test->setData(value);
    if (optional.contains("[色坐标]") && (value.contains("[色坐标x]") || value.contains("[色坐标y]")))
        test->setData("[色坐标]", QPointF(test->data("[色坐标x]").toDouble(), test->data("[色坐标y]").toDouble()));
    if (optional.contains("[色坐标uv]") && (value.contains("[色坐标u]") || value.contains("[色坐标v]")))
        test->setData("[色坐标uv]", QPointF(test->data("[色坐标u]").toDouble(), test->data("[色坐标v]").toDouble()));
    if (optional.contains("[色坐标uvp]") && (value.contains("[色坐标up]") || value.contains("[色坐标vp]")))
        test->setData("[色坐标uvp]", QPointF(test->data("[色坐标up]").toDouble(), test->data("[色坐标vp]").toDouble()));
    if (optional.contains("[电功率]") && (value.contains("[实测电压]") || value.contains("[实测电流]")))
    {
        auto p = test->data("[实测电压]").toDouble() * test->data("[实测电流]").toDouble() / 1000.0;
        auto f = test->data("[光通量]").toDouble();
        auto e = test->data("[明视觉光效率]").toDouble();
        test->setData("[电功率]" , p);
        if (optional.contains("[光效率]"))
            test->setData("[光效率]", p < 0.00001 ? 0.0 :  f / p);
        if (optional.contains("[光功率]"))
            test->setData("[光功率]", e < 0.00001 ? 0.0 : 1000 * f / e);
    }
    return test->select(optional);
}

HE_END_NAMESPACE

#include "HConfigManage_p.h"
#include "IDataFactory.h"
#include "IDataStream.h"
#include "ITestData.h"
#include "ISpecCalibrateCollection.h"
#include "IElecCalibrateCollection.h"
#include "ILuminousCalibrateCollection.h"
#include "IChromatismCollection.h"
#include "IGradeCollection.h"
#include "IAdjustCollection.h"
#include "IAdjust2Collection.h"
#include "IQualityCollection.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDataStream>
#include <QtCore/QPointF>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtGui/QColor>
#include <QtCore/QDebug>

HE_DATA_BEGIN_NAMESPACE

QSet<QString> supplement(QSet<QString> set, QSet<QString> other)
{
    for (const auto &s : other)
    {
        if (set.contains(s))
            return set.unite(other);
    }
    return set;
}

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
        specCalibrates = factory->createSpecCalibrateCollection(type);
        specCalibrates->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainElec)
    {
        s >> type;
        elecCalibrates = factory->createElecCalibrateCollection(type);
        elecCalibrates->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainLuminous)
    {
        s >> type;
        luminousCalibrates = factory->createLuminousCalibrateCollection(type);
        luminousCalibrates->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainChromatism)
    {
        s >> type;
        chromatisms = factory->createChromatismCollection(type);
        chromatisms->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainGrade)
    {
        s >> type;
        grades = factory->createGradeCollection(type);
        grades->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainAdjust)
    {
        s >> type;
        adjusts = factory->createAdjustCollection(type);
        adjusts->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainAdjust2)
    {
        s >> type;
        adjusts2 = factory->createAdjust2Collection(type);
        adjusts2->dataStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainQuality)
    {
        s >> type;
        qualitys = factory->createQualityCollection(type);
        qualitys->dataStream()->readContent(s);
    }
}

void HConfigManagePrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << contain;
    if (contain & IConfigManage::ContainSpec)
    {
        s << specCalibrates->typeName();
        specCalibrates->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainElec)
    {
        s << elecCalibrates->typeName();
        elecCalibrates->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainLuminous)
    {
        s << luminousCalibrates->typeName();
        luminousCalibrates->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainChromatism)
    {
        s << chromatisms->typeName();
        chromatisms->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainGrade)
    {
        s << grades->typeName();
        grades->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainAdjust)
    {
        s << adjusts->typeName();
        adjusts->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainAdjust2)
    {
        s << adjusts2->typeName();
        adjusts2->dataStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainQuality)
    {
        s << qualitys->typeName();
        qualitys->dataStream()->writeContent(s);
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

HConfigManage::~HConfigManage()
{
    qDebug() << __func__;
}

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
    d_ptr->specCalibrates = p;
}

ISpecCalibrate *HConfigManage::specCalibrate(QString name)
{
    Q_ASSERT(d_ptr->specCalibrates != nullptr);
    if (d_ptr->specCalibrates->contains(name))
        return d_ptr->specCalibrates->value(name);
    return d_ptr->specCalibrates->first();
}

void HConfigManage::setElecCalibrateCollection(IElecCalibrateCollection *p)
{
    d_ptr->elecCalibrates = p;
}

IElecCalibrateCollection *HConfigManage::elecCalibrateCollection()
{
    return d_ptr->elecCalibrates;
}

void HConfigManage::setLuminousCalibrateCollection(ILuminousCalibrateCollection *p)
{
    d_ptr->luminousCalibrates = p;
}

ILuminousCalibrateCollection *HConfigManage::luminousCalibrateCollection()
{
    return d_ptr->luminousCalibrates;
}

void HConfigManage::setChromatismCollection(IChromatismCollection *p)
{
    d_ptr->chromatisms = p;
}

IChromatismCollection *HConfigManage::chromatismCollection()
{
    return d_ptr->chromatisms;
}

void HConfigManage::setGradeCollection(IGradeCollection *p)
{
    d_ptr->grades = p;
}

IGradeCollection *HConfigManage::gradeCollection()
{
    return d_ptr->grades;
}

void HConfigManage::setAdjustCollection(IAdjustCollection *p)
{
    d_ptr->adjusts = p;
}

IAdjustCollection *HConfigManage::adjustCollection()
{
    return d_ptr->adjusts;
}

void HConfigManage::setAdjust2Collection(IAdjust2Collection *p)
{
    d_ptr->adjusts2 = p;
}

IAdjust2Collection *HConfigManage::adjust2Collection()
{
    return d_ptr->adjusts2;
}

void HConfigManage::setQualityCollection(IQualityCollection *p)
{
    d_ptr->qualitys = p;
}

IQualityCollection *HConfigManage::qualityCollection()
{
    return d_ptr->qualitys;
}

bool HConfigManage::importPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ContainSpec)
        return d_ptr->specCalibrates->dataStream()->openFile();
    if (value & ContainElec)
        return d_ptr->elecCalibrates->dataStream()->openFile();
    if (value & ContainLuminous)
        return d_ptr->luminousCalibrates->dataStream()->openFile();
    if (value & ContainChromatism)
        return d_ptr->chromatisms->dataStream()->openFile();
    if (value & ContainGrade)
        return d_ptr->grades->dataStream()->openFile();
    if (value & ContainAdjust)
        return d_ptr->adjusts->dataStream()->openFile();
    if (value & ContainAdjust2)
        return d_ptr->adjusts2->dataStream()->openFile();
    if (value & ContainQuality)
        return d_ptr->qualitys->dataStream()->openFile();
    return false;
}

bool HConfigManage::exportPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ContainSpec)
        return d_ptr->specCalibrates->dataStream()->saveAsFile();
    if (value & ContainElec)
        return d_ptr->elecCalibrates->dataStream()->saveAsFile();
    if (value & ContainLuminous)
        return d_ptr->luminousCalibrates->dataStream()->saveAsFile();
    if (value & ContainChromatism)
        return d_ptr->chromatisms->dataStream()->saveAsFile();
    if (value & ContainGrade)
        return d_ptr->grades->dataStream()->saveAsFile();
    if (value & ContainAdjust)
        return d_ptr->adjusts->dataStream()->saveAsFile();
    if (value & ContainAdjust2)
        return d_ptr->adjusts2->dataStream()->saveAsFile();
    if (value & ContainQuality)
        return d_ptr->qualitys->dataStream()->saveAsFile();
    return false;
}

void HConfigManage::postProcess(ITestData *test, QStringList optional)
{
    auto set = optional.toSet();
    set = supplement(set, QSet<QString>() << "[色坐标]" << "[色坐标x]" << "[色坐标y]");
    set = supplement(set, QSet<QString>() << "[色坐标uv]" << "[色坐标u]" << "[色坐标v]");
    set = supplement(set, QSet<QString>() << "[色坐标uvp]" << "[色坐标up]" << "[色坐标vp]");
    optional = set.toList();
    auto data = test->select(optional);

    test->setData("[调整组]", "-");
    if (test->data("[使用调整]").toBool())
    {
        QVariantMap value;
        if (d_ptr->adjusts != nullptr)
        {
            value = d_ptr->adjusts->correct(data);
            test->setData("[调整组]", d_ptr->adjusts->useIndex());
        }
        else if (d_ptr->adjusts2 != nullptr)
        {
            value = d_ptr->adjusts2->correct(test->data("[色温]").toDouble(), data);
            test->setData("[调整组]", d_ptr->adjusts2->useIndex());
        }
        if (!value.isEmpty())
            data = unify(test, value, optional);
    }
    if (d_ptr->chromatisms != nullptr)
    {
        test->setData("[色容差]", d_ptr->chromatisms->calcSdcm(test->data("[色温]").toDouble(), test->data("[色坐标]").toPointF()));
        test->setData("[色容差标准]", d_ptr->chromatisms->toMap());
//        auto std = d_ptr->chromatisms->toMap();
//        test->setData("[色容差标准Json]", QString(QJsonDocument(QJsonObject::fromVariantMap(std)).toJson(QJsonDocument::Compact)));
    }

    if (d_ptr->grades != nullptr)
    {
        QString text;
        auto level = d_ptr->grades->calcLevel(data, &text);
        test->setData("[分级]", level);
        test->setData("[分级别名]", text);
    }

    if (d_ptr->qualitys != nullptr)
    {
        QVariantMap colors;
        auto report = d_ptr->qualitys->check(data, &colors);
        auto color = d_ptr->qualitys->color(report);
        test->setData("[品质]", report);
        test->setData("[品质颜色]", color);
        test->setData("[品质不符合颜色]", colors);
    }
}

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

HE_DATA_END_NAMESPACE

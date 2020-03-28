#include "HConfigManage_p.h"
#include "IDataFactory.h"
#include "IFileStream.h"
#include "ITestData.h"
#include "ISpecCalibrateCollection.h"
#include "IElecCalibrateCollection.h"
#include "IChromatismCollection.h"
#include "IGradeCollection.h"
#include "IAdjustCollection.h"
#include "IQualityCollection.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDataStream>
#include <QtCore/QPointF>
#include <QtGui/QColor>
#include <QtCore/QDebug>

HE_DATA_BEGIN_NAMESPACE

QSet<QString> supplement(QSet<QString> set, QSet<QString> other)
{
    for (auto s : other)
    {
        if (set.contains(s))
            return set.unite(other);
    }
    return set;
}

HConfigManagePrivate::HConfigManagePrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    fileStream = factory->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00010001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Config files (*.cfg)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
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
        specCalibrates->fileStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainElec)
    {
        s >> type;
        elecCalibrates = factory->createElecCalibrateCollection(type);
        elecCalibrates->fileStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainChromatism)
    {
        s >> type;
        chromatisms = factory->createChromatismCollection(type);
        chromatisms->fileStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainGrade)
    {
        s >> type;
        grades = factory->createGradeCollection(type);
        grades->fileStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainAdjust)
    {
        s >> type;
        adjusts = factory->createAdjustCollection(type);
        adjusts->fileStream()->readContent(s);
    }
    if (contain & IConfigManage::ContainQuality)
    {
        s >> type;
        qualitys = factory->createQualityCollection(type);
        qualitys->fileStream()->readContent(s);
    }
}

void HConfigManagePrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << contain;
    if (contain & IConfigManage::ContainSpec)
    {
        s << specCalibrates->typeName();
        specCalibrates->fileStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainElec)
    {
        s << elecCalibrates->typeName();
        elecCalibrates->fileStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainChromatism)
    {
        s << chromatisms->typeName();
        chromatisms->fileStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainGrade)
    {
        s << grades->typeName();
        grades->fileStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainAdjust)
    {
        s << adjusts->typeName();
        adjusts->fileStream()->writeContent(s);
    }
    if (contain & IConfigManage::ContainQuality)
    {
        s << qualitys->typeName();
        qualitys->fileStream()->writeContent(s);
    }
}

HConfigManage::HConfigManage() :
    d_ptr(new HConfigManagePrivate)
{
}

HConfigManage::HConfigManage(HConfigManagePrivate &p) :
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

IFileStream *HConfigManage::fileStream()
{
    return d_ptr->fileStream;
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

IElecCalibrate *HConfigManage::elecCalibrate(QString name)
{
    Q_ASSERT(d_ptr->elecCalibrates != nullptr);
    if (d_ptr->elecCalibrates->contains(name))
        return d_ptr->elecCalibrates->value(name);
    return d_ptr->elecCalibrates->first();
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
    return  d_ptr->adjusts;
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
        return d_ptr->specCalibrates->fileStream()->openFile();
    if (value & ContainElec)
        return d_ptr->elecCalibrates->fileStream()->openFile();
    if (value & ContainChromatism)
        return d_ptr->chromatisms->fileStream()->openFile();
    if (value & ContainGrade)
        return d_ptr->grades->fileStream()->openFile();
    if (value & ContainAdjust)
        return d_ptr->adjusts->fileStream()->openFile();
    if (value & ContainQuality)
        return d_ptr->qualitys->fileStream()->openFile();
    return false;
}

bool HConfigManage::exportPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ContainSpec)
        return d_ptr->specCalibrates->fileStream()->saveAsFile();
    if (value & ContainElec)
        return d_ptr->elecCalibrates->fileStream()->saveAsFile();
    if (value & ContainChromatism)
        return d_ptr->chromatisms->fileStream()->saveAsFile();
    if (value & ContainGrade)
        return d_ptr->grades->fileStream()->saveAsFile();
    if (value & ContainAdjust)
        return d_ptr->adjusts->fileStream()->saveAsFile();
    if (value & ContainQuality)
        return d_ptr->qualitys->fileStream()->saveAsFile();
    return false;
}

void HConfigManage::postProcess(ITestData *test, QStringList optional)
{
    auto set = optional.toSet();
    set = supplement(set, QSet<QString>() << "[色坐标]" << "[色坐标x]" << "[色坐标y]");
    set = supplement(set, QSet<QString>() << "[色坐标uv]" << "[色坐标u]" << "[色坐标v]");
    set = supplement(set, QSet<QString>() << "[色坐标uvp]" << "[色坐标up]" << "[色坐标vp]");
    auto data = test->select(set.toList());
    if (d_ptr->adjusts != nullptr && test->data("[使用调整]").toBool())
    {
        data = d_ptr->adjusts->correct(data);
        test->setData(data);
    }
    if (d_ptr->chromatisms != nullptr)
    {
        test->setData("[色容差]", d_ptr->chromatisms->calcSdcm(test->data("[色温]").toDouble(), test->data("[色坐标]").toPointF()));
        test->setData("[色容差标准]", d_ptr->chromatisms->toMap());
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

HE_DATA_END_NAMESPACE

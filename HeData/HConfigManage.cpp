#include "HConfigManage_p.h"
#include "IDataFactory.h"
#include "IFileStream.h"
#include "ISpecCalibrateCollection.h"
#include "IGradeCollection.h"
#include <QtCore/QDataStream>
#include <QtCore/QDebug>

HE_DATA_BEGIN_NAMESPACE

HConfigManagePrivate::HConfigManagePrivate(IDataFactory *f)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
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
    if (contain & ConfigContainType::CCT_Spec)
    {
        s >> type;
        specCalibrates = factory->createSpecCalibrateCollection(type);
        specCalibrates->fileStream()->readContent(s);
    }
    if (contain & ConfigContainType::CCT_Grade)
    {
        s >> type;
        grades = factory->createGradeCollection(type);
        grades->fileStream()->readContent(s);
    }
}

void HConfigManagePrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << contain;
    if (contain & ConfigContainType::CCT_Spec)
    {
        s << specCalibrates->typeName();
        specCalibrates->fileStream()->writeContent(s);
    }
    if (contain & ConfigContainType::CCT_Grade)
    {
        s << grades->typeName();
        grades->fileStream()->writeContent(s);
    }
}

HConfigManage::HConfigManage(IDataFactory *f) :
    d_ptr(new HConfigManagePrivate(f))
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

void HConfigManage::setContain(quint32 value)
{
    d_ptr->contain = value;
}

void HConfigManage::setSpecCalibrateCollection(ISpecCalibrateCollection *p)
{
    d_ptr->specCalibrates = p;
}

void HConfigManage::setGradeCollection(IGradeCollection *p)
{
    d_ptr->grades = p;
}

IFileStream *HConfigManage::fileStream()
{
    return d_ptr->fileStream;
}

quint32 HConfigManage::contain()
{
    return d_ptr->contain;
}

ISpecCalibrate *HConfigManage::specCalibrate(QString name)
{
    Q_ASSERT(d_ptr->specCalibrates != nullptr);
    if (d_ptr->specCalibrates->contains(name))
        return d_ptr->specCalibrates->value(name);
    return d_ptr->specCalibrates->first();
}

IGradeCollection *HConfigManage::gradeCollection()
{
    return  d_ptr->grades;
}

bool HConfigManage::importPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ConfigContainType::CCT_Spec)
        return d_ptr->specCalibrates->fileStream()->openFile();
    if (value & ConfigContainType::CCT_Grade)
        return d_ptr->grades->fileStream()->openFile();
    return false;
}

bool HConfigManage::exportPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ConfigContainType::CCT_Spec)
        return d_ptr->specCalibrates->fileStream()->saveAsFile();
    if (value & ConfigContainType::CCT_Grade)
        return d_ptr->grades->fileStream()->saveAsFile();
    return false;
}

HE_DATA_END_NAMESPACE

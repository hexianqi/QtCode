#include "HConfigManage_p.h"
#include "IDataFactory.h"
#include "IFileStream.h"
#include "ISpecCalibrateCollection.h"
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HConfigManagePrivate::HConfigManagePrivate(IDataFactory *f)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00010001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter(QObject::tr("Config files (*.cfg)"));
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
}

HConfigManage::HConfigManage(IDataFactory *f)
    : d_ptr(new HConfigManagePrivate(f))
{
}

HConfigManage::HConfigManage(HConfigManagePrivate &p)
    : d_ptr(&p)
{
}

HConfigManage::~HConfigManage()
{
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

bool HConfigManage::importPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ConfigContainType::CCT_Spec)
        return d_ptr->specCalibrates->fileStream()->openFile();
    return false;
}

bool HConfigManage::exportPart(quint32 value)
{
    if ((d_ptr->contain & value) == 0)
        return false;
    if (value & ConfigContainType::CCT_Spec)
        return d_ptr->specCalibrates->fileStream()->saveAsFile();
    return false;
}

HE_DATA_END_NAMESPACE

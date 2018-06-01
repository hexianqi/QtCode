#include "HConfigManage_p.h"
#include "IDataFactory.h"
#include "ISpecCalibrateCollection.h"
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HConfigManagePrivate::HConfigManagePrivate(IDataFactory *f)
    : HAbstractFileStreamPrivate(f)
{
    magicNumber = 0x00010001;
    fileVersion = 0x01010101;
    fileFilter = QObject::tr("Config files (*.cfg)");
}

HConfigManage::HConfigManage(IDataFactory *f)
    : HAbstractFileStream(*new HConfigManagePrivate(f))
{
}

HConfigManage::HConfigManage(HConfigManagePrivate &p)
    : HAbstractFileStream(p)
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
    Q_D(HConfigManage);
    d->contain = value;
}

void HConfigManage::setSpecCalibrateCollection(ISpecCalibrateCollection *p)
{
    Q_D(HConfigManage);
    d->specCalibrates = p;
}

quint32 HConfigManage::contain()
{
    Q_D(HConfigManage);
    return d->contain;
}

ISpecCalibrate *HConfigManage::specCalibrate(QString name)
{
    Q_D(HConfigManage);
    Q_ASSERT(d->specCalibrates != nullptr);
    if (d->specCalibrates->contains(name))
        return d->specCalibrates->value(name);
    return d->specCalibrates->first();
}

bool HConfigManage::importPart(quint32 value)
{
    Q_D(HConfigManage);
    if ((d->contain & value) == 0)
        return false;
    if (value & ConfigContainType::CCT_Spec)
        return d->specCalibrates->openFile();
    return false;
}

bool HConfigManage::exportPart(quint32 value)
{
    Q_D(HConfigManage);
    if ((d->contain & value) == 0)
        return false;
    if (value & ConfigContainType::CCT_Spec)
        return d->specCalibrates->saveAsFile();
    return false;
}

void HConfigManage::readContent(QDataStream &s)
{
    Q_D(HConfigManage);
    quint32 version;
    QString type;

    s >> version;
    s >> d->contain;
    if (d->contain & ConfigContainType::CCT_Spec)
    {
        s >> type;
        d->specCalibrates = d->factory->createSpecCalibrateCollection(type);
        d->specCalibrates->readContent(s);
    }
}

void HConfigManage::writeContent(QDataStream &s)
{
    Q_D(HConfigManage);
    s << quint32(1);
    s << d->contain;
    if (d->contain & ConfigContainType::CCT_Spec)
        d->specCalibrates->writeContent(s);
}

HE_DATA_END_NAMESPACE

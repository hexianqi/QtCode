#include "HDataFactory_p.h"
#include "HExcelStream.h"
#include "HFileStream.h"
#include "HConfigManage.h"
#include "HSpecCalibrate.h"
#include "HSpecCalibrateCollection.h"
#include "HGradeCollection.h"
#include "HSequentialGrade.h"
#include "HParallelGrade.h"
#include "HGradeItem.h"
#include "HGradeItem2D.h"
#include "HAdjustCollection.h"
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
    IFileStream *p = new HFileStream(this);
    p->initialize(param);
    return p;
}

IExcelStream *HDataFactory::createExcelStream(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IExcelStream *p = new HExcelStream(this);
    p->initialize(param);
    return p;
}

IConfigManage *HDataFactory::createConfigManage(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IConfigManage *p = new HConfigManage(this);
    p->initialize(param);
    return p;
}

ISpecCalibrateCollection *HDataFactory::createSpecCalibrateCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ISpecCalibrateCollection *p = new HSpecCalibrateCollection(this);
    p->initialize(param);
    return p;
}

ISpecCalibrate *HDataFactory::createSpecCalibrate(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    ISpecCalibrate *p = new HSpecCalibrate;
    p->initialize(param);
    return p;
}

IGradeCollection *HDataFactory::createGradeCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IGradeCollection *p = new HGradeCollection(this);
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
    IAdjustCollection *p = new HAdjustCollection(this);
    p->initialize(param);
    return p;
}

IAdjust *HDataFactory::createAdjust(QString type, QVariantMap param)
{

}

IAdjustItem *HDataFactory::createAdjustItem(QString type, QVariantMap param)
{

}

void HDataFactory::registerClass()
{
    HFactory::registerClass<HParallelGrade>("HParallelGrade");
    HFactory::registerClass<HSequentialGrade>("HSequentialGrade");
    HFactory::registerClass<HGradeItem>("HGradeItem");
    HFactory::registerClass<HGradeItem2D>("HGradeItem2D");
}

HE_DATA_END_NAMESPACE

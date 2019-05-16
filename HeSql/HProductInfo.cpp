#include "HProductInfo_p.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>

HE_SQL_BEGIN_NAMESPACE

HProductInfoPrivate::HProductInfoPrivate()
{
    datas.insert("Manufacturer", "Manufacturer");
    datas.insert("ProductName", "Name");
    datas.insert("ProductModel", "Model");
    datas.insert("TestInstitute", "");
    datas.insert("Tester", "");
    datas.insert("SampleNumber", 1);
    datas.insert("Temperature", 25.0);
    datas.insert("Humidity", 60.0);
    datas.insert("Editable", true);
    datas.insert("Increase", true);
}

HProductInfo::HProductInfo(QObject *parent) :
    QObject(parent),
    d_ptr(new HProductInfoPrivate)
{
}

HProductInfo::HProductInfo(HProductInfoPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HProductInfo::~HProductInfo()
{
    writeSettings();
}

void HProductInfo::initialize(QVariantMap param)
{
    if (param.contains("relationTableName"))
        d_ptr->relationTableName = param.value("relationTableName").toString();
    if (param.contains("datas"))
        setData(param.value("datas").toMap());
    readSettings();
}

QString HProductInfo::typeName()
{
    return "HProductInfo";
}

void HProductInfo::setRelationTableName(QString value)
{
    d_ptr->relationTableName = value;
    readSettings();
}

void HProductInfo::setData(QString type, QVariant value)
{
    d_ptr->datas.insert(type, value);
}

void HProductInfo::setData(QVariantMap value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        setData(i.key(), i.value());
}

QVariant HProductInfo::data(QString type)
{
    return d_ptr->datas.value(type);
}

bool HProductInfo::contains(QString type)
{
    return d_ptr->datas.contains(type);
}

bool HProductInfo::increase()
{
    return data("Increase").toBool();
}

bool HProductInfo::editable()
{
    return data("Editable").toBool();
}

void HProductInfo::saveOnce()
{
    if (increase())
        setData("SampleNumber", data("SampleNumber").toInt() + 1);
}

void HProductInfo::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d_ptr->relationTableName + "Product");
    for (auto k : settings->allKeys())
        setData(k, settings->value(k));
    settings->endGroup();
}

void HProductInfo::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d_ptr->relationTableName + "Product");
    for (auto i = d_ptr->datas.begin(); i != d_ptr->datas.end(); i++)
        settings->setValue(i.key(), i.value());
    settings->endGroup();
}

HE_SQL_END_NAMESPACE

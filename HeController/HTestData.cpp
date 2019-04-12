#include "HTestData_p.h"
#include "HeCore/HCore.h"
#include <QColor>
#include <QDateTime>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

void HTestDataPrivate::setData(QString type, QVariant value)
{
    if (datas.contains(type))
    {
        datas[type] = value;
        return;
    }
    if (successor != nullptr)
        return successor->setData(type, value);
    addData(type, value);
}

void HTestDataPrivate::addData(QString type, QVariant value)
{
    datas.insert(type, value);
}

QVariant HTestDataPrivate::data(QString type)
{
    if (datas.contains(type))
        return datas.value(type);
    if (successor != nullptr)
        return successor->data(type);
    if (type == "[测量日期时间]")
        return QDateTime::currentDateTime();
    if (type == "[测量日期]")
        return data("[测量日期时间]").toDate();
    if (type == "[测量时间]")
        return data("[测量日期时间]").toTime();
    return QVariant();
}

HTestData::HTestData()
    : d_ptr(new HTestDataPrivate)
{
}

HTestData::~HTestData()
{
}

HTestData::HTestData(HTestDataPrivate &p)
    : d_ptr(&p)
{
}

void HTestData::initialize(QVariantMap param)
{
    if (param.contains("successor"))
        setSuccessor(FromVariant(ITestData, param.value("successor")));
    if (param.contains("datas"))
    {
        QMapIterator<QString, QVariant> i(param.value("datas").toMap());
        while (i.hasNext())
        {
            i.next();
            addData(i.key(), i.value());
        }
    }
}

QString HTestData::typeName()
{
    return "HTestData";
}

void HTestData::setSuccessor(ITestData *p)
{
    d_ptr->successor = p;
}

void HTestData::setData(QString type, QVariant value)
{
    d_ptr->setData(type, value);
}

void HTestData::addData(QString type, QVariant value)
{
    d_ptr->addData(type, value);
}

QVariant HTestData::data(QString type)
{
    return d_ptr->data(type);
}

QString HTestData::toString(QString type)
{
    return HeCore::toString(type, data(type));
}

QStringList HTestData::toString(QStringList types)
{
    QStringList list;
    for (auto type : types)
        list << toString(type);
    return list;
}

QString HTestData::toHtmlTable(QStringList types, QColor bgcolor)
{
    QString text;
    QString caption,value,unit;

    text = QString("<table align = center border = 0 width = 300 cellspacing = 5 cellpadding = 5 bgcolor = %1 style = table-layout:fixed;>").arg(bgcolor.name());
    for (auto type : types)
    {
        caption = toCaption(type);
        value = toString(type);
        unit = toUnit(type);
        text += QString("<tr>"
                        "<td><p align = right>%1</p></td>"
                        "<td><p align = center>%2</p></td>"
                        "<td><p align = left>%3</p></td>"
                        "</tr>").arg(caption).arg(value).arg(unit);
    }
    text += "</table>";
    return text;
}

HE_CONTROLLER_END_NAMESPACE

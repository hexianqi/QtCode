#include "HTestData.h"
#include <QtCore/QPoint>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QDebug>
#include <cxxabi.h>

template <typename T>
class NameTemplate
{
public:
    QString name()
    {
        return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
//        return typeid(T).name();
    }
};

template <typename T>
QString name()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

void HTestData::testVector()
{
    QVector<int> v;
    for (int i = 0; i < 10; i++)
        v << i+1;

    int pos = 0;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
}

void HTestData::testJson()
{
    QVariantMap map;
    map.insert("px", 0.1);
    map.insert("py", 5.1);
    auto json = QJsonObject::fromVariantMap(map);
    auto doc = QJsonDocument(json);
    auto text = QString(doc.toJson());
    auto byte = doc.toBinaryData();
    qDebug() << map;
    qDebug() << json;
    qDebug() << doc;
    qDebug() << text;
    qDebug() << byte;
}

void HTestData::testTemplateName()
{
    NameTemplate<int> i;
    NameTemplate<double> d;
    NameTemplate<QString> s;
    NameTemplate<QPoint> p;
    NameTemplate<HTestData> c;
    qDebug() << i.name();
    qDebug() << d.name();
    qDebug() << s.name();
    qDebug() << p.name();
    qDebug() << c.name();
    qDebug() << name<int>();
    qDebug() << name<QString>();
    qDebug() << name<HTestData>();
}

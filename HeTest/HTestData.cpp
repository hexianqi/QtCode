#include "HTestData.h"
#include <QtCore/QPoint>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QFile>
#include <QtCore/QDataStream>
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

void HTestData::testByteArray()
{
    auto voltage = 5.0;
    auto current = 1.02500;
    auto text = QString("U:%1:%2/").arg(voltage, 0, 'f', 4).arg(current, 0, 'f', 5);
    auto ba = text.toLatin1();
    auto da = ba.data();
    qDebug() << "===================================";
    qDebug() << text;
    qDebug() << ba;
    qDebug() << da;
    for (int i = 0; i < ba.size(); i++)
        qDebug() << QString("0x%1").arg(int(ba[i]), 2, 16);
    qDebug() << "-----------------------------------";
    auto text2 = QString("21.0200V3.00000A");
    auto ba2 = text2.toLatin1();
    auto str = QString::fromLatin1(ba2);
    auto list = str.split('V');
    qDebug() << text2;
    qDebug() << ba2;
    qDebug() << str;
    for (int i = 0; i < list.size(); i++)
        qDebug() << list[i].left(list[i].size() - 1).toDouble();
    qDebug() << "===================================";
}

void HTestData::testWriteMode()
{
    int num = 0x12345678;

    // C方式
    FILE *fp = nullptr;
    fp = fopen("data_c.txt", "wb+");
    printf("num_1 = %d\n", num);
    fwrite((void *)&num, 1,sizeof(int), fp);
    fflush(fp);
    fseek(fp, 0, SEEK_SET);
    fread((void *)&num, 1, 4, fp);
    printf("num_2 = %d\n", num);
    fclose(fp);

    // QDataStream方式1
    QFile file1("data_qt1.txt");
    file1.open(QIODevice::ReadWrite);
    QDataStream s1(&file1);
    qDebug() << "num_1 = " << num;
    s1 << num;
    file1.seek(0);
    s1 >> num;
    qDebug() << "num_2 = " << num;
    file1.close();

    // QDataStream方式2
    QFile file2("data_qt2.txt");
    file2.open(QIODevice::ReadWrite);
    QDataStream s2(&file2);
    qDebug() << "num_1 = " << num;
    s2.writeRawData((char *)(&num), sizeof(int));
    file2.seek(0);
    s2.readRawData((char *)(&num), sizeof(int));
    qDebug() << "num_2 = " << num;
    file2.close();
}

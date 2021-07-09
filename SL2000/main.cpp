#include "HMainWindow2000.h"
#include "HMainWindow2000AC.h"
#include "HMainWindow2000DC.h"
#include "HMainWindow2000F.h"
#include "HeCore/HCoreGlobalInstance.h"
#include "HeSql/HSqlGlobalInstance.h"
#include <QtCore/QTranslator>
#include <QtWidgets/QApplication>

// 翻译时需要取消掉对应的命名空间
//#define HE_ENGLISH

#include <QJsonObject>
#include <QJsonDocument>
#include <QtDebug>
#include <QVariantMap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");


    // QPointF 无法转化成QJson
    QVariantMap datas;
    datas.insert("[项类型]", "Undefined");
    datas.insert("[标题]", "");
    datas.insert("[使用]", true);
    datas.insert("[相关色温]", 0.0);
    datas.insert("[标准Sdcm]", 5.0);
    datas.insert("[中心点]", QVariantList() << 0.0 << 0.0);
    datas.insert("[参数G]", QVariantList() << 3.1 << 3.2 << 3.3);
    datas.insert("[旋转角]", 0.0);
    datas.insert("[轴A]", 0.0);
    datas.insert("[轴B]", 0.0);
    datas.insert("[测试点]", QVariantList() << 1.0 << 2.0);
    datas.insert("[测试Sdcm]", 3.0);

    auto json = QJsonObject::fromVariantMap(datas);
    auto str = QString(QJsonDocument(json).toJson(QJsonDocument::Compact));
    auto doc = QJsonDocument::fromJson(str.toUtf8());
    auto json2 = doc.object();
    auto datas2 = json2.toVariantMap();
    auto b1 = datas == datas2;
    auto b2 = json == json2;
    qDebug() << " data         " << datas;
    qDebug() << " data2        " << datas2;
    qDebug() << " data = data2 " << b1;
    qDebug() << " json         " << json;
    qDebug() << " json2        " << json2;
    qDebug() << " json = json2 " << b2;
    qDebug() << " string " << str;











//#ifdef HE_ENGLISH
//    QTranslator t1, t2, t3, t4, t5, t6;
//    if (t1.load("Translations\\HeCore_en"))
//        a.installTranslator(&t1);
//    if (t2.load("Translations\\HeController_en"))
//        a.installTranslator(&t2);
//    if (t3.load("Translations\\HePlugin_en"))
//        a.installTranslator(&t3);
//    if (t4.load("Translations\\HeSql_en"))
//        a.installTranslator(&t4);
//    if (t5.load("Translations\\HeGui_en"))
//        a.installTranslator(&t5);
//    if (t6.load("Translations\\SL2000_en"))
//        a.installTranslator(&t6);
//#endif

//    HCoreGlobalInstance::instance()->init();
//    HSqlGlobalInstance::instance()->init();

//#ifdef SL2000
//    QApplication::setApplicationName("SL2000");
//    HMainWindow2000 w;
//#elif SL2000AC
//    QApplication::setApplicationName("SL2000AC");
//    HMainWindow2000AC w;
//#elif SL2000DC
//    QApplication::setApplicationName("SL2000DC");
//    HMainWindow2000DC w;
//#elif SL2000F
//    QApplication::setApplicationName("SL2000F");
//    HMainWindow2000F w;
//#endif
//    w.show();
    return QApplication::exec();
}

#include "HMainWindow2000.h"
#include "HMainWindow2000AC.h"
#include "HMainWindow2000DC.h"
#include "HMainWindow2000F.h"
#include "HeCore/HCoreGlobalInstance.h"
#include "HeSql/HSqlGlobalInstance.h"
#include <QtCore/QTranslator>
#include <QtWidgets/QApplication>

// 翻译时需要取消掉对应的命名空间
// #define HE_ENGLISH

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);

#ifdef HE_ENGLISH
    QTranslator t1, t2, t3, t4, t5, t6;
    if (t1.load("Translations\\HeCore_en"))
        a.installTranslator(&t1);
    if (t2.load("Translations\\HeController_en"))
        a.installTranslator(&t2);
    if (t3.load("Translations\\HePlugin_en"))
        a.installTranslator(&t3);
    if (t4.load("Translations\\HeSql_en"))
        a.installTranslator(&t4);
    if (t5.load("Translations\\HeGui_en"))
        a.installTranslator(&t5);
    if (t6.load("Translations\\SL2000_en"))
        a.installTranslator(&t6);
#endif

    HCoreGlobalInstance::instance()->initialize();
    HSqlGlobalInstance::instance()->initialize();

#ifdef SL2000
    QApplication::setApplicationName("SL2000");
    HMainWindow2000 w;
#elif SL2000AC
    QApplication::setApplicationName("SL2000AC");
    HMainWindow2000AC w;
#elif SL2000DC
    QApplication::setApplicationName("SL2000DC");
    HMainWindow2000DC w;
#elif SL2000F
    QApplication::setApplicationName("SL2000F");
    HMainWindow2000F w;
#endif

    w.showMaximized();
    return a.exec();
}

#include "HMainWindow2100DC.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTranslator>

// 翻译时需要取消掉对应的命名空间
#define HE_ENGLISH  1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");

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
    if (t6.load("Translations\\SL2100_en"))
        a.installTranslator(&t6);
#endif

#ifdef SL2100DC
    QApplication::setApplicationName("SL2100DC");
    HMainWindow2100DC w;
    w.show();
#endif

    return a.exec();
}

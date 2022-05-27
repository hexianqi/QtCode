#include "HMainWindow2100DC.h"
#include "HeCore/HCoreHelper.h"
#include "HeCore/HCoreGlobalInstance.h"
#include "HeSql/HSqlGlobalInstance.h"
#include <QtCore/QTextCodec>
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
    HCoreHelper::installTranslator("Translations\\HeCore_en.qm");
    HCoreHelper::installTranslator("Translations\\HeController_en.qm");
    HCoreHelper::installTranslator("Translations\\HePlugin_en.qm");
    HCoreHelper::installTranslator("Translations\\HeSql_en.qm");
    HCoreHelper::installTranslator("Translations\\HeGui_en.qm");
    HCoreHelper::installTranslator("Translations\\SL2100_en.qm");
#endif

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    HCoreGlobalInstance::instance()->initialize();
    HSqlGlobalInstance::instance()->initialize();

#ifdef SL2100DC
    QApplication::setApplicationName("SL2100DC");
    HMainWindow2100DC w;
#endif

    w.showMaximized();
    return a.exec();
}
